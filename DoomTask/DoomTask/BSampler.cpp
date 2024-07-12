#include "BSampler.h"
#include "DTThrowMacros.h"

BSampler::BSampler(DTGraphics& gfx, D3D11_FILTER filter , D3D11_TEXTURE_ADDRESS_MODE addressMode)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = filter;
	sd.AddressU = addressMode;
	sd.AddressV = addressMode;
	sd.AddressW = addressMode;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	GFX_THROW_INFO(GetDevice(gfx)->CreateSamplerState(&sd, &pSampler));
}

void BSampler::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}
