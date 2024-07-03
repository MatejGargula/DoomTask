#include "RMesh.h"
#include "Vertex.h"
#include "BVertexBuffer.h"
#include "BVertexShader.h"
#include "BPixelShader.h"
#include "BInputLayout.h"
#include "BTopology.h"

RMesh::RMesh(DTGraphics& gfx, std::string path)
{

	Assimp::Importer imp;

	const auto model = imp.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);

	//TODO: Handle for multiple meshes
	const auto mesh = model->mMeshes[0]; 

	std::vector<VertexPosNorm> vertices;
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(
			{
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mVertices[i]),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i]),
			}
		);
	}

	std::vector<unsigned short> indices(mesh->mNumFaces * 3);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const auto& face = mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	// Geometry buffers
	AddIndexBuffer(std::make_unique<BIndexBuffer>(gfx, indices));
	AddBind(std::make_unique<BVertexBuffer>(gfx, vertices));

	// Shaders
	auto pvs = std::make_unique<BVertexShader>(gfx, L"SimplePhongVS.cso");
	auto pvsbc = pvs->GetBytecode();
	AddBind(std::move(pvs));
	//AddBind(std::make_unique<BPixelShader>(gfx, L"SimplePhongPS.cso"));
	AddBind(std::make_unique<BPixelShader>(gfx, L"PhongPS.cso"));

	//Input layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddBind(std::make_unique<BInputLayout>(gfx, ied, pvsbc));

	//Topology
	AddBind(std::make_unique<BTopology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
}
