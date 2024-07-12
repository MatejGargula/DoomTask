#pragma once

#include "DTBindObjectBase.h"

/// <summary>
/// Class for storing and binding a domain shader in the pipeline
/// </summary>
class BDomainShader : public DTBindObjectBase
{
public:
	BDomainShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
	void Unbind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> pDomainShader;
};

