#include "BDomainShader.h"
#include "DTThrowMacros.h"

BDomainShader::BDomainShader(DTGraphics& gfx, const std::wstring& path)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreateDomainShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&pDomainShader));
}

void BDomainShader::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->DSSetShader(pDomainShader.Get(), nullptr, 0u);
}

void BDomainShader::Unbind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->DSSetShader(nullptr, nullptr, 0u);
}
