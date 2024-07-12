#pragma once

#include "DTBindObjectBase.h"

class DTGraphics;

/// <summary>
/// Class for storing and binding a pixel shader in the pipeline
/// </summary>
class BPixelShader : public DTBindObjectBase
{
public:
	BPixelShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
	void Unbind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};

