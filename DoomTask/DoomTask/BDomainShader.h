#pragma once

#include "DTBindObjectBase.h"

class BDomainShader : public DTBindObjectBase
{
public:
	BDomainShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
	void Unbind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> pDomainShader;
};

