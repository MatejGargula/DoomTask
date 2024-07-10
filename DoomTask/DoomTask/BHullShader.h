#pragma once
#include "DTBindObjectBase.h"
class BHullShader : public DTBindObjectBase
{
public:
	BHullShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11HullShader> pHullShader;
};

