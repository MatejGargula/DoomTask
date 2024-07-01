#pragma once

#include "DTBindObjectBase.h"

class BInputLayout : public DTBindObjectBase
{
public:
	BInputLayout(DTGraphics& gfx,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		ID3DBlob* pVertexShaderBytecode);
	void Bind(DTGraphics& gfx) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

