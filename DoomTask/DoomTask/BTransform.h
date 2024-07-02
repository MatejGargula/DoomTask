#pragma once

#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"

#include <DirectXMath.h>

class BTransform : public DTBindObjectBase
{	
private:
	struct Transforms
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelViewProj;
	};

	float x;
	float y;
	float z;

	float rotX;
	float rotY;
	float rotZ;

	std::unique_ptr<BVertexConstantBuffer<Transforms>> pVcbuf;

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

