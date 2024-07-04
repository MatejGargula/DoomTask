#include "DepthStencilTexture.h"

DepthStencilTexture::DepthStencilTexture(DTGraphics& gfx, UINT width, UINT height)
{
    // Needed for macro throws
    DxgiInfoManager& infoManager = GetInfoManager(gfx);
    HRESULT hr;
}

void DepthStencilTexture::BindAsDepthBuffer(DTGraphics& gfx) const noexcept
{

}

void DepthStencilTexture::Clear(DTGraphics& gfx) const noexcept
{

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
