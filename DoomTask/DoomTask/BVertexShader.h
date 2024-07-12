#pragma once

#include "DTBindObjectBase.h"

/// <summary>
/// Class for storing and binding a vertex shader in the pipeline
/// </summary>
class BVertexShader : public DTBindObjectBase
{
public:
	BVertexShader(DTGraphics& gfx, const std::wstring& path);
	void Bind(DTGraphics& gfx) noexcept override;
	void Unbind(DTGraphics& gfx) noexcept override;
	ID3DBlob* GetBytecode() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};