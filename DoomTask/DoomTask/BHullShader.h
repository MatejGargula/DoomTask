#pragma once
#include "DTBindObjectBase.h"

/// <summary>
/// Class for storing and binding a hull shader in the pipeline
/// </summary>
class BHullShader : public DTBindObjectBase
{
public:
	BHullShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
	void Unbind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11HullShader> pHullShader;
};

