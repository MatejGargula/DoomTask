#include "BShader.h"
#include "DTThrowMacros.h"

BShader::BShader(DTGraphics& gfx, const std::wstring& path, ShaderType type)
{
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob));

	switch (type)
	{
	case ShaderType::Vertex:
		GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pVertexShader
		));

		break;
	case ShaderType::Pixel:
		GFX_THROW_INFO(GetDevice(gfx)->CreatePixelShader(
			pBytecodeBlob->GetBufferPointer(),
			pBytecodeBlob->GetBufferSize(),
			nullptr,
			&pPixelShader));
		break;
	default:
		break;
	}

	
}

void BShader::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* BShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}
