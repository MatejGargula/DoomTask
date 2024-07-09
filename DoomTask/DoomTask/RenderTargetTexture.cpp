#include "RenderTargetTexture.h"
#include "DTThrowMacros.h"

RenderTargetTexture::RenderTargetTexture(DTGraphics& gfx, UINT width, UINT height)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	// Create texture resource
	D3D11_TEXTURE2D_DESC td = {};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;//DXGI_FORMAT_B8G8R8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;

	// null pointer here means we are not filling the texture with any data 
	GFX_THROW_INFO(GetDevice(gfx)->CreateTexture2D(&td, nullptr, &pTexture)); 

	// Create texture resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;

	GFX_THROW_INFO(GetDevice(gfx)->CreateShaderResourceView(pTexture.Get(), &srvd, &pTextureView));

	// Create texture render target view
	D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
	rtvd.Format = td.Format;
	rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvd.Texture2D = D3D11_TEX2D_RTV{ 0 };

	GFX_THROW_INFO(GetDevice(gfx)->CreateRenderTargetView(pTexture.Get(), &rtvd, &pRenderTargetView));

}

void RenderTargetTexture::BindAsTexture(DTGraphics& gfx, UINT slot) const noexcept
{
	GetContext(gfx)->PSSetShaderResources(slot, 1, pTextureView.GetAddressOf());
}

void RenderTargetTexture::BindAsRenderTarget(DTGraphics& gfx) const noexcept
{
	GetContext(gfx)->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);
}

void RenderTargetTexture::BindAsRenderTarget(DTGraphics& gfx, const DepthStencilTexture& depthStencilTex) const noexcept
{
	GetContext(gfx)->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), depthStencilTex.pDepthStencilView.Get());
}

void RenderTargetTexture::ClearRenderTarget(DTGraphics& gfx, const float color[3]) noexcept
{
	GetContext(gfx)->ClearRenderTargetView(pRenderTargetView.Get(), color);
}

ID3D11DeviceContext* RenderTargetTexture::GetContext(DTGraphics& gfx) noexcept
{
	return gfx.pContext.Get();
}

ID3D11Device* RenderTargetTexture::GetDevice(DTGraphics& gfx) noexcept
{
	return gfx.pDevice.Get();
}

DxgiInfoManager& RenderTargetTexture::GetInfoManager(DTGraphics& gfx) noexcept
{
	return gfx.infoManager;
}
