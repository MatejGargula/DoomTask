#pragma once
#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"
#include "BTexture.h"
#include "BSampler.h"

/// <summary>
/// TODO: add docs
/// </summary>
class BMaterial : public DTBindObjectBase
{
private: 
	//TODO: Add textures
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
	void Bind(DTGraphics& gfx) noexcept override;
	
	void SetAmbient(DirectX::XMFLOAT3 amb);
	void SetDiffuse(DirectX::XMFLOAT3 diff);
	void SetDiffuse(std::unique_ptr<BTexture> diffTexture);
	void SetSpecular(DirectX::XMFLOAT4 spec);
	void SetSpecular(std::unique_ptr<BTexture> specTexture, float shinniness);
	void Set(DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec);
};

