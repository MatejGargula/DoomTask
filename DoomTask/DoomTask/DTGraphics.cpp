#include "DTGraphics.h"
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
	return "DTGraphics HR Exception";
}

std::string DTGraphics::HrException::GetErrorDescription() const noexcept
{
	return "DTGraphics HR Exception Description";
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

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	GFX_THROW_FAILED( D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		&featureLevel,
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
	
	// Render target
	DisablePostProcessing();

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

	D3D11_RASTERIZER_DESC rdw = {};
	rdw.FillMode = D3D11_FILL_WIREFRAME;
	rdw.CullMode = D3D11_CULL_NONE;
	rdw.DepthClipEnable = true;

	D3D11_RASTERIZER_DESC rds = {};
	rds.FillMode = D3D11_FILL_SOLID;
	rds.CullMode = D3D11_CULL_BACK;

	pDevice->CreateRasterizerState(&rdw,&pWireRasterState);
	pDevice->CreateRasterizerState(&rds, &pSolidRasterState);
	
	DisableWireframe();
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

void DTGraphics::ClearBackBuffer(float r, float g, float b) noexcept
{
	const float color[] = { r,g,b,1.0f };

	mainSceneRenderTexture->ClearRenderTarget(*this, color);
	mainDepthRenderTexture->Clear(*this);
	
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

void DTGraphics::DrawIndexed(UINT count)
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

void DTGraphics::EnableWireframe()
{
	pContext->RSSetState(pWireRasterState.Get());
}

void DTGraphics::DisableWireframe()
{
	pContext->RSSetState(pSolidRasterState.Get());
}

bool DTGraphics::isPostprocessingEnabled()
{
	return postProcessingEnabled;
}



void DTGraphics::SetTopology(D3D11_PRIMITIVE_TOPOLOGY type)
{
	pContext->IASetPrimitiveTopology(type);
}
