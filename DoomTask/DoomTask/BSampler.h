#pragma once
#include "DTBindObjectBase.h"
/// <summary>
/// class for storing and binding sampler to the pipeline.
/// </summary>
class BSampler : public DTBindObjectBase
{
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
public:
	BSampler(DTGraphics& gfx, D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_MODE addressMode = D3D11_TEXTURE_ADDRESS_MIRROR);
	void Bind(DTGraphics& gfx) noexcept override;
};

