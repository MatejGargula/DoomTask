#include "BVertexShader.h"
#include "DTThrowMacros.h"

BVertexShader::BVertexShader(DTGraphics& gfx, const std::wstring& path)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));
	GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	));
}

void BVertexShader::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

void BVertexShader::Unbind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(nullptr, nullptr, 0u);
}

ID3DBlob* BVertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}
