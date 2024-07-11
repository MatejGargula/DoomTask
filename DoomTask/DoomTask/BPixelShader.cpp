#include "BPixelShader.h"
#include "DTThrowMacros.h"

BPixelShader::BPixelShader(DTGraphics& gfx, const std::wstring& path)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreatePixelShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&pPixelShader));
}

void BPixelShader::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}

void BPixelShader::Unbind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(nullptr, nullptr, 0u);
}
