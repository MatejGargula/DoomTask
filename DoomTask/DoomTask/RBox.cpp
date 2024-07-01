#include "RBox.h"
#include "Cube.h"
#include "BVertexBuffer.h"
#include "BVertexShader.h"
#include "BPixelShader.h"
#include "BInputLayout.h"
#include "BTopology.h"
#include "Vertex.h"

RBox::RBox(DTGraphics& gfx)
{
	const IndexedTriangleList<VertexPos> model = Cube::Make<VertexPos>();

	// Geometry buffers
	AddIndexBuffer(std::make_unique<BIndexBuffer>(gfx, model.indices));
	AddBind(std::make_unique<BVertexBuffer>(gfx, model.vertices));

	// Shaders
	auto pvs = std::make_unique<BVertexShader>(gfx, L"SimpleVertexShader.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));
	AddBind(std::make_unique<BPixelShader>(gfx, L"SimplePixelShader.cso"));

	//Input layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddBind(std::make_unique<BInputLayout>(gfx, ied, pvsbc));
	
	//Topology
	AddBind(std::make_unique<BTopology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	
}
