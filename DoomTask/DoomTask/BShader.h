#pragma once

#include "DTBindObjectBase.h"

enum class ShaderType
{
	Vertex,
	Pixel,
};

class BShader: DTBindObjectBase
{
public:
	BShader(DTGraphics& gfx, const std::wstring& path, ShaderType type);
	void Bind(DTGraphics& gfx) noexcept override;
	ID3DBlob* GetBytecode() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};

