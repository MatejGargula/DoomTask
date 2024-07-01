#include "BTopology.h"

BTopology::BTopology(DTGraphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
	:
	type(type)
{}

void BTopology::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->IASetPrimitiveTopology(type);
}
