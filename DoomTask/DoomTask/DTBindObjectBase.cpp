#include "DTBindObjectBase.h"

void DTBindObjectBase::Unbind(DTGraphics& gfx) noexcept
{
}

ID3D11DeviceContext* DTBindObjectBase::GetContext(DTGraphics& gfx) noexcept
{
	return gfx.pContext.Get();
}

ID3D11Device* DTBindObjectBase::GetDevice(DTGraphics& gfx) noexcept
{
	return gfx.pDevice.Get();
}

DxgiInfoManager& DTBindObjectBase::GetInfoManager(DTGraphics& gfx) noexcept
{
	return gfx.infoManager;
}
