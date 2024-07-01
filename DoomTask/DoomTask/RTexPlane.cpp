#include "RTexPlane.h"
#include "Plane.h"
#include "BVertexBuffer.h"
#include "BVertexShader.h"
#include "BPixelShader.h"
#include "BInputLayout.h"
#include "BTopology.h"
#include "BTexture.h"
#include "BSampler.h"
#include "Vertex.h"

RTexPlane::RTexPlane(DTGraphics& gfx)
{
	IndexedTriangleList<VertexPosTex> model = Plane::Make<VertexPosTex>();
	model.vertices[0].tex = { 0.0f, 0.0f };
	model.vertices[1].tex = { 1.0f, 0.0f };
	model.vertices[2].tex = { 0.0f, 1.0f };
	model.vertices[3].tex = { 1.0f, 1.0f };

	// Geometry buffers
	AddIndexBuffer(std::make_unique<BIndexBuffer>(gfx, model.indices));
	AddBind(std::make_unique<BVertexBuffer>(gfx, model.vertices));

	// Shaders
	auto pvs = std::make_unique<BVertexShader>(gfx, L"PlaneTexVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));
	AddBind(std::make_unique<BPixelShader>(gfx, L"PlaneTexPS.cso"));

	//Input layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddBind(std::make_unique<BInputLayout>(gfx, ied, pvsbc));

	// Topology
	AddBind(std::make_unique<BTopology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	// Texture  stuff
	AddBind(std::make_unique<BTexture>(gfx, "doggo.jpg"));
	AddBind(std::make_unique<BSampler>(gfx));
}
