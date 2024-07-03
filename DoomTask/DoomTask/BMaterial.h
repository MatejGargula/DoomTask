#pragma once
#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"

class BMaterial : public DTBindObjectBase
{
private: 
	//TODO: Add textures
	struct CbuffMaterialData 
	{
		DirectX::XMFLOAT3 ambient;
		float pad1;
		DirectX::XMFLOAT3 diffuse;
		float pad2;
		DirectX::XMFLOAT4 spec; // shinniness is last coord
	};

	CbuffMaterialData data;

	std::unique_ptr<BPixelConstantBuffer<CbuffMaterialData>> pPcbuf;

public:
	BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec);
	void Bind(DTGraphics& gfx) noexcept override;
	void Set(DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec);
};

