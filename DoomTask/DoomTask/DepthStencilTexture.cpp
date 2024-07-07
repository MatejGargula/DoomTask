#include "DepthStencilTexture.h"
#include "DTThrowMacros.h"

DepthStencilTexture::DepthStencilTexture(DTGraphics& gfx, UINT width, UINT height)
{
    // Needed for macro throws
    DxgiInfoManager& infoManager = GetInfoManager(gfx);
    HRESULT hr = {};

	// create depth stensil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = SCREEN_WIDTH;
	descDepth.Height = SCREEN_HEIGHT;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	GFX_THROW_INFO(GetDevice(gfx)->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	GFX_THROW_INFO(GetDevice(gfx)->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pDepthStencilView
	));
}

void DepthStencilTexture::BindAsDepthBuffer(DTGraphics& gfx) const noexcept
{
	GetContext(gfx)->OMSetRenderTargets(1u, nullptr, pDepthStencilView.Get());
}

void DepthStencilTexture::Clear(DTGraphics& gfx) const noexcept
{
    GetContext(gfx)->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

ID3D11DeviceContext* DepthStencilTexture::GetContext(DTGraphics& gfx) noexcept
{
    return gfx.pContext.Get();
}

ID3D11Device* DepthStencilTexture::GetDevice(DTGraphics& gfx) noexcept
{
    return gfx.pDevice.Get();
}

DxgiInfoManager& DepthStencilTexture::GetInfoManager(DTGraphics& gfx) noexcept
{
    return gfx.infoManager;
}
