#include "RMultiMesh.h"

RMultiMesh::RMultiMesh(DTGraphics& gfx, std::string path)
{
	// Shaders
	//ID3DBlob* pvsbc = pvs->GetBytecode();
	//AddBind(std::move(pvs));
	VS = std::make_unique<BVertexShader>(gfx, L"DefferedCollectionVS.cso");
	PS = std::make_unique<BPixelShader>(gfx, L"DefferedCollectionPS.cso");

	Assimp::Importer imp;

	const aiScene* model = imp.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);

	for (unsigned int i = 0; i < model->mNumMeshes; i++)
	{		
		meshes.push_back(std::make_unique<RMesh>(gfx, *model->mMeshes[i], model->mMaterials, VS->GetBytecode()));
	}

}

void RMultiMesh::Render(DTGraphics& gfx) const noexcept
{
	//if (VS != nullptr && shadersEnabled)
	//	VS->Bind(gfx);
	//
	//if (PS != nullptr && shadersEnabled)
	//	PS->Bind(gfx);
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render(gfx);
	}
}

void RMultiMesh::SetPS(DTGraphics& gfx, const std::wstring& path)
{
	//PS = std::make_unique<BPixelShader>(gfx, path);
}
void RMultiMesh::SetVS(DTGraphics& gfx, const std::wstring& path)
{
	//VS = std::make_unique<BVertexShader>(gfx, path);
}
