#pragma once

#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"

#include <DirectXMath.h>

class BTransform : public DTBindObjectBase
{	
private:
	struct CbuffCameraData
	{
		DirectX::XMFLOAT3 pos;
		float pad;
	};

	struct Transforms
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelViewProj;
	};

	struct HullShaderConstData
	{
		DirectX::XMFLOAT3 CameraPosition;
		float pad1;

		float TessellationRange;
		float MinTessFactor;
		float MaxTessFactor;
		float pad2;
	};

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	std::unique_ptr<BVertexConstantBuffer<Transforms>> pVcbuf;
	std::unique_ptr<BHullConstantBuffer<HullShaderConstData>> pHcbuf;
	std::unique_ptr<BPixelConstantBuffer<CbuffCameraData>> pPcbuf;

	DirectX::XMMATRIX modelMat;
	
	void updateTransformMatrix();
	Transforms getTransformMatrices(DTGraphics& gfx);

public:

	BTransform(DTGraphics& gfx);
	BTransform(DTGraphics& gfx, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot);

	void Bind(DTGraphics& gfx) noexcept override;
	void Translate(float xPos, float yPos, float zPos) noexcept;
	void SetPosition(float xPos, float yPos, float zPos) noexcept;
	void SetRotation(float xRot, float yRot, float zRot) noexcept;

	DirectX::XMMATRIX GetTransormMat() noexcept;

};

