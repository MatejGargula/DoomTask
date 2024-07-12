#pragma once

#include "DTBindObjectBase.h"

/// <summary>
/// Class for setting the desired topology of the pipeline.
/// </summary>
class BTopology : public DTBindObjectBase
{
public:
	BTopology(DTGraphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(DTGraphics& gfx) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};