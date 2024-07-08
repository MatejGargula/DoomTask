#include "RMultiMesh.h"

RMultiMesh::RMultiMesh(DTGraphics& gfx, std::string path)
{
	Assimp::Importer imp;

	const aiScene* model = imp.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);

	for (unsigned int i = 0; i < model->mNumMeshes; i++)
	{		
		meshes.push_back(std::make_unique<RMesh>(gfx, *model->mMeshes[i], model->mMaterials));
	}

}

void RMultiMesh::Render(DTGraphics& gfx) const noexcept
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render(gfx);
	}
}

void RMultiMesh::Render(DTGraphics& gfx, BTransform& transform) const noexcept
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Render(gfx, transform);
	}
}
