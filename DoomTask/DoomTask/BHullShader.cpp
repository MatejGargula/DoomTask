#include "BHullShader.h"
#include "DTThrowMacros.h"

BHullShader::BHullShader(DTGraphics& gfx, const std::wstring& path)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreateHullShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		nullptr,
		&pHullShader));
}

void BHullShader::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->HSSetShader(pHullShader.Get(), nullptr, 0u);
}
