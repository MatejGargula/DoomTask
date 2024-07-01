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
	//sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	//sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	//sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	//sd.MipLODBias = 0.0f;
	//sd.MaxAnisotropy = 1;
	//sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//sd.BorderColor[0] = 1.0f;
	//sd.BorderColor[1] = 1.0f;
	//sd.BorderColor[2] = 1.0f;
	//sd.BorderColor[3] = 1.0f;
	//sd.MinLOD = -FLT_MAX;
	//sd.MaxLOD = FLT_MAX;


	GFX_THROW_INFO(GetDevice(gfx)->CreateSamplerState(&sd, &pSampler));
}

void BSampler::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->PSSetSamplers(0, 1, pSampler.GetAddressOf());
}
