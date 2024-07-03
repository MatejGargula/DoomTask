#include "BMaterial.h"

BMaterial::BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffMaterialData>>(gfx, 2u);
	}

	Set(amb, diff, spec);
}

void BMaterial::Bind(DTGraphics& gfx) noexcept
{
	pPcbuf->Update(gfx, data);
	pPcbuf->Bind(gfx);
}

void BMaterial::Set(DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec)
{
	data.ambient = amb;
	data.diffuse = diff;
	data.spec = spec;
}
