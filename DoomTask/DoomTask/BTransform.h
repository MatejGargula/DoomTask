#pragma once

#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"

#include <DirectXMath.h>

class BTransform : public DTBindObjectBase
{
private:
	float x;
	float y;
	float z;

	float rotX;
	float rotY;
	float rotZ;

	std::unique_ptr<BVertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;

	DirectX::XMMATRIX transformMat;

	void updateTransformMatrix();

public:

	BTransform(DTGraphics& gfx);
	BTransform(DTGraphics& gfx, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot);

	void Bind(DTGraphics& gfx) noexcept override;
	void Translate(float xPos, float yPos, float zPos) noexcept;
	void SetPosition(float xPos, float yPos, float zPos) noexcept;
	void SetRotation(float xRot, float yRot, float zRot) noexcept;

	DirectX::XMMATRIX GetTransormMat() noexcept;

};

