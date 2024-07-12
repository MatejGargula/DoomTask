#pragma once
#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"
#include "BTexture.h"
#include "BSampler.h"

/// <summary>
/// Stores the data about the material of the objects along with the texture (textures are optional)
/// </summary>
class BMaterial : public DTBindObjectBase
{
private: 
	struct CbuffMaterialData 
	{
		DirectX::XMFLOAT3 ambient;
		bool useDiffTex;
		DirectX::XMFLOAT3 diffuse;
		bool useSpecTex;
		DirectX::XMFLOAT4 spec; // shinniness is stored as alpha
	};

	CbuffMaterialData data;

	std::unique_ptr<BTexture> diffTex;
	std::unique_ptr<BTexture> specTex;

	BSampler sampler;

	std::unique_ptr<BPixelConstantBuffer<CbuffMaterialData>> pPcbuf;

public:
	BMaterial(DTGraphics& gfx);
	BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec);
	BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, std::unique_ptr<BTexture> diffTexture, std::unique_ptr<BTexture> specTexture, float shinniness);
	
	/// <summary>
	/// Binds the material as a constatn buffer into the pixel shader.
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	void Bind(DTGraphics& gfx) noexcept override;
	
	/// <summary>
	/// Sets the ambient component of the material.
	/// </summary>
	/// <param name="amb"> ambient component </param>
	void SetAmbient(DirectX::XMFLOAT3 amb);
	
	/// <summary>
	/// Sets the diffuse component of the material.
	/// </summary>
	/// <param name="amb"> diffuse component </param>
	void SetDiffuse(DirectX::XMFLOAT3 diff);
	
	/// <summary>
	/// Sets the diffuse component of the material as texture.
	/// </summary>
	/// <param name="amb"> ambient component texture </param>
	void SetDiffuse(std::unique_ptr<BTexture> diffTexture);

	/// <summary>
	/// Sets the specular component of the material.
	/// </summary>
	/// <param name="spec"> specular component where the last coordinate is shinniness </param>
	void SetSpecular(DirectX::XMFLOAT4 spec);

	/// <summary>
	/// Sets the specular component of the material as a texture. 
	/// </summary>
	/// <param name="specTexture"> specular component texture </param>
	/// <param name="shinniness"> shinniness component </param>
	void SetSpecular(std::unique_ptr<BTexture> specTexture, float shinniness);

	/// <summary>
	/// Sets all of the main components.
	/// </summary>
	/// <param name="amb"> ambient </param>
	/// <param name="diff"> diffuse </param>
	/// <param name="spec"> specular </param>
	void Set(DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec);
};

