#include "DepthStencilTexture.h"

DepthStencilTexture::DepthStencilTexture(DTGraphics& gfx, UINT width, UINT height)
{
    // Needed for macro throws
    DxgiInfoManager& infoManager = GetInfoManager(gfx);
    HRESULT hr = {};

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
    D3D11_TEXTURE2D_DESC td = {};
    td.Width = width;
    td.Height = height;
    td.MipLevels = 1u;
    td.ArraySize = 1u;
    td.Width = width;
    td.Width = width;
    td.Width = width;
    td.Width = width;
}

void DepthStencilTexture::BindAsDepthBuffer(DTGraphics& gfx) const noexcept
{

}

void DepthStencilTexture::Clear(DTGraphics& gfx) const noexcept
{
    //GetContext(gfx)->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
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
