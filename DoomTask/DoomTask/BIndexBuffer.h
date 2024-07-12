#pragma once

#include "DTBindObjectBase.h"

/// <summary>
/// Class for storing and binding a index buffer in the pipeline
/// </summary>
class BIndexBuffer : public DTBindObjectBase
{
public:
	BIndexBuffer(DTGraphics& gfx, const std::vector<unsigned short>& indices);
	void Bind(DTGraphics& gfx) noexcept override;
	UINT GetCount() const noexcept;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};