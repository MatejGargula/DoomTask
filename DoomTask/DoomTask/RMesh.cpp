#include "RMesh.h"
#include "Vertex.h"
#include "BVertexBuffer.h"
#include "BVertexShader.h"
#include "BPixelShader.h"
#include "BInputLayout.h"
#include "BTopology.h"
#include "BMaterial.h"

RMesh::RMesh(DTGraphics& gfx, std::string path)
{
	Assimp::Importer imp;

	const auto model = imp.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);

	//TODO: Handle for multiple meshes
	//const aiMesh* mesh = model->mMeshes[0]; 
	//
	//std::vector<VertexPosNormTexCoord> vertices;
	//vertices.reserve(mesh->mNumVertices);
	//for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	//{
	//	vertices.push_back(
	//		{
	//		*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mVertices[i]),
	//		*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh->mNormals[i]),
	//		*reinterpret_cast<DirectX::XMFLOAT2*>(&mesh->mTextureCoords/[0]/[i]),
	//		}
	//	);
	//}
	//
	//std::vector<unsigned short> indices(mesh->mNumFaces * 3);
	//for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	//{
	//	const auto& face = mesh->mFaces[i];
	//	assert(face.mNumIndices == 3);
	//	indices.push_back(face.mIndices[0]);
	//	indices.push_back(face.mIndices[1]);
	//	indices.push_back(face.mIndices[2]);
	//}
	//
	//// Geometry buffers
	//AddIndexBuffer(std::make_unique<BIndexBuffer>(gfx, indices));
	//AddBind(std::make_unique<BVertexBuffer>(gfx, vertices));
	//
	////Input layout
	//const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	//{
	//	{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, //D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, //D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 20, //D3D11_INPUT_PER_VERTEX_DATA, 0},
	//};
}

RMesh::RMesh(DTGraphics& gfx, aiMesh& mesh, const aiMaterial* const* materials, ID3DBlob* pvsbc)
{
	std::vector<VertexPosNormTexCoord> vertices;
	vertices.reserve(mesh.mNumVertices);
	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		vertices.push_back(
			{
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mVertices[i]),
			*reinterpret_cast<DirectX::XMFLOAT3*>(&mesh.mNormals[i]),
			*reinterpret_cast<DirectX::XMFLOAT2*>(&mesh.mTextureCoords[0][i]),
			}
		);
	}

	std::vector<unsigned short> indices(mesh.mNumFaces * 3);
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	// Geometry buffers
	AddIndexBuffer(std::make_unique<BIndexBuffer>(gfx, indices));
	AddBind(std::make_unique<BVertexBuffer>(gfx, vertices));

	//Input layout
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	AddBind(std::make_unique<BInputLayout>(gfx, ied, pvsbc));

	// Material
	if (mesh.mMaterialIndex >= 0)
	{
		std::unique_ptr<BMaterial> materialBind = std::make_unique<BMaterial>(gfx);
		
		// copy the material info to MeshGeometry structure
		const aiMaterial* mat = materials[mesh.mMaterialIndex];
		aiColor4D color;
		aiString name;
		aiReturn retValue = AI_SUCCESS;

		// Get returns: aiReturn_SUCCESS 0 | aiReturn_FAILURE -1 | aiReturn_OUTOFMEMORY -3
		mat->Get(AI_MATKEY_NAME, name); // may be "" after the input mesh processing. Must be aiString type!

		// Ambient
		if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
			color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

		materialBind->SetAmbient(DirectX::XMFLOAT3(color.r, color.g, color.b));

		// Diffuse
		if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
			color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

		materialBind->SetDiffuse(DirectX::XMFLOAT3(color.r, color.g, color.b));

		// Specular
		if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
			color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
		
		ai_real shininess, strength;
		unsigned int max;

		max = 1;
		if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
			shininess = 1.0f;
		max = 1;
		if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
			strength = 1.0f;
	
		materialBind->SetSpecular(DirectX::XMFLOAT4(color.r, color.g, color.b, shininess * strength));
	
		if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			// get texture name 
			aiString path; // filename

			aiReturn texFound = mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			std::string textureName = std::string("Models\\") +  path.data;

			materialBind->SetDiffuse(std::make_unique<BTexture>(gfx, textureName, 0));
		}

		if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0) {
			// get texture name 
			aiString path; // filename

			aiReturn texFound = mat->GetTexture(aiTextureType_SPECULAR, 0, &path);
			std::string textureName = std::string("Models\\") + path.data;

			materialBind->SetSpecular(std::make_unique<BTexture>(gfx, textureName, 1), shininess * strength);
		}

		AddBind(std::move(materialBind));
	}

	
}
