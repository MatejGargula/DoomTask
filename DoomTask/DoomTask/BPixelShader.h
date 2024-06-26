#pragma once

#include "DTBindObjectBase.h"

class BPixelShader : public DTBindObjectBase
{
public:
	BPixelShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};

