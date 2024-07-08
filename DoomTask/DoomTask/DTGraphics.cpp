#include "DTGraphics.h"
#include "dxerr.h"
#include "DTWindow.h"
#include "DTThrowMacros.h"
#include "DTConfig.h"
#include "Vertex.h"

//TODO: Delete later
#include "BConstantBuffer.h"
#include "BIndexBuffer.h"
#include "BInputLayout.h"
#include "BPixelShader.h"
#include "BTopology.h"
#include "BVertexBuffer.h"
#include "BVertexShader.h"
#include "BTransform.h"

#include <d3dcompiler.h>
#include <cmath>
#include <DirectXMath.h>
#include <vector>

#pragma region Nested Classes

DTGraphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file),
	hr(hr)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* DTGraphics::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* DTGraphics::HrException::GetType() const noexcept
{
	return "Graphics Exception";
}

HRESULT DTGraphics::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string DTGraphics::HrException::GetErrorString() const noexcept
{
	return (char*)DXGetErrorString(hr);
}

std::string DTGraphics::HrException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return buf;
}

std::string DTGraphics::HrException::GetErrorInfo() const noexcept
{
	return info;
}

const char* DTGraphics::DeviceRemovedException::GetType() const noexcept
{
	return "Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}

DTGraphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		info += m;
		info.push_back('\n');
	}
	// remove final newline if exists
	if (!info.empty())
	{
		info.pop_back();
	}
}

const char* DTGraphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* DTGraphics::InfoException::GetType() const noexcept
{
	return "Graphics Info Exception";
}

std::string DTGraphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}

#pragma endregion

DTGraphics::DTGraphics(HWND hWnd)
	:
	postProcessingEnabled(false),
	mainDepthRenderTexture(nullptr),
	mainSceneRenderTexture(nullptr)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;

	GFX_THROW_FAILED( D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	));

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

	GFX_THROW_FAILED(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_THROW_FAILED(pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pTarget
	));

	mainDepthRenderTexture = std::make_shared<DepthStencilTexture>(*this, SCREEN_WIDTH, SCREEN_HEIGHT);
	mainSceneRenderTexture = std::make_shared<RenderTargetTexture>(*this, SCREEN_WIDTH, SCREEN_HEIGHT);

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	GFX_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));
	
	//// bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	
	//// create depth stensil texture
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	//D3D11_TEXTURE2D_DESC descDepth = {};
	//descDepth.Width = SCREEN_WIDTH;
	//descDepth.Height = SCREEN_HEIGHT;
	//descDepth.MipLevels = 1u;
	//descDepth.ArraySize = 1u;
	//descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	//descDepth.SampleDesc.Count = 1u;
	//descDepth.SampleDesc.Quality = 0u;
	//descDepth.Usage = D3D11_USAGE_DEFAULT;
	//descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//GFX_THROW_INFO(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	//// create view of depth stensil texture
	//D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	//descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	//descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//descDSV.Texture2D.MipSlice = 0u;
	//GFX_THROW_INFO(pDevice->CreateDepthStencilView(
	//	pDepthStencil.Get(), &descDSV, &pDSV
	//));
	
	// Render target
	DisablePostProcessing();
	//EnablePostProcessing();

	// configure viewport
	D3D11_VIEWPORT vp = {};
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);

	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f , 0.0f };
	DirectX::XMFLOAT3 forward = { 0.0f, 0.0f , 1.0f };
	DirectX::XMFLOAT3 up = { 0.0f, 1.0f , 0.0f };

	float fov = 60.0f;
	float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	float nearZ = 0.1f;
	float farZ = 1000.0f;

	camera = std::make_unique<DTCamera>(
		pos,
		forward,
		up,
		fov,
		aspectRatio,
		nearZ,
		farZ
	);
}

void DTGraphics::EndFrame()
{
	HRESULT hr;

	if (FAILED( hr = pSwap->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED) 
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			GFX_THROW_FAILED(hr);
		}
	}
}

void DTGraphics::ClearBuffer(float r, float g, float b) noexcept
{
	const float color[] = { r,g,b,1.0f };

	//if (postProcessingEnabled)
	//{
	mainSceneRenderTexture->ClearRenderTarget(*this, color);
	mainDepthRenderTexture->Clear(*this);
	//	return;
	//}
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	//pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void DTGraphics::DrawTestTriangle(float angle, float x, float z)
{
	//const std::vector<Vertex> vertices =
	//{
	//	{0.0f, 0.5f, 255,0,0,0},
	//	{0.5, -0.5f, 0,255,0,0},
	//	{-0.5f, -0.5f, 0,0,255,0}
	//};
	
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	const std::vector<Vertex> vertices =
	{
		{ -1.0f,-1.0f,-1.0f	 },
		{ 1.0f,-1.0f,-1.0f	 },
		{ -1.0f,1.0f,-1.0f	 },
		{ 1.0f,1.0f,-1.0f	  },
		{ -1.0f,-1.0f,1.0f	 },
		{ 1.0f,-1.0f,1.0f	  },
		{ -1.0f,1.0f,1.0f	 },
		{ 1.0f,1.0f,1.0f	 },
	};

	const std::vector<unsigned short> indicies =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	std::unique_ptr<BIndexBuffer> ibuff = std::make_unique<BIndexBuffer>(*this,indicies);
	ibuff->Bind(*this);

	std::unique_ptr<DTBindObjectBase> vb = std::make_unique<BVertexBuffer>(*this,vertices);
	vb->Bind(*this);

	HRESULT hr = {};

	auto pvs = std::make_unique<BVertexShader>(*this, L"SimpleVertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	pvs->Bind(*this);

	auto pps = std::make_unique<BPixelShader>(*this, L"SimplePixelShader.cso");
	pps->Bind(*this);

	//Input layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	std::unique_ptr<DTBindObjectBase> il = std::make_unique<BInputLayout>(*this, ied, pvsbc);
	il->Bind(*this);

	//CONSTANT BUFFERS

	std::unique_ptr<DTBindObjectBase> transBuf = std::make_unique<BTransform>(*this, x, z, 4.0f, angle, 0.0f, angle);
	transBuf->Bind(*this);
	// create constant buffer for transformation matrix
	//struct ConstantBuffer
	//{
	//	DirectX::XMMATRIX transform;
	//};
	//const ConstantBuffer cb =
	//{
	//	{
	//		DirectX::XMMatrixTranspose(
	//			DirectX::XMMatrixRotationZ(angle) *
	//			DirectX::XMMatrixRotationX(angle) *
	//			DirectX::XMMatrixTranslation(x,z,4.0f) *
	//			GetProjection()
	//			//DirectX::XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f)
	//		)
	//	}
	//};
	//Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	//D3D11_BUFFER_DESC cbd;
	//cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cbd.Usage = D3D11_USAGE_DYNAMIC;
	//cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbd.MiscFlags = 0u;
	//cbd.ByteWidth = sizeof(cb);
	//cbd.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	//GFX_THROW_INFO(pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer));
	//
	//// bind constant buffer to vertex shader
	//pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	
	std::unique_ptr<BTopology> topp = std::make_unique<BTopology>(*this,D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	topp->Bind(*this);
	
	//GFX_THROW_INFO_ONLY(pContext->Draw(std::size(vertices), 0u));
	GFX_THROW_INFO_ONLY(pContext->DrawIndexed(std::size(indicies), 0u, 0u));
}

void DTGraphics::DrawIndexed(UINT count) noexcept
{
	GFX_THROW_INFO_ONLY(pContext->DrawIndexed(count, 0u, 0u));
}

void DTGraphics::EnablePostProcessing()
{
	if (postProcessingEnabled)
		return;

	postProcessingEnabled = true;

	mainSceneRenderTexture->BindAsRenderTarget(*this);
	mainSceneRenderTexture->BindAsRenderTarget(*this, *mainDepthRenderTexture.get());

}

void DTGraphics::DisablePostProcessing()
{
	postProcessingEnabled = false;

	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());
}

std::shared_ptr<RenderTargetTexture> DTGraphics::GetMainRenderTexture()
{
	return mainSceneRenderTexture;
}

bool DTGraphics::isPostprocessingEnabled()
{
	return postProcessingEnabled;
}
