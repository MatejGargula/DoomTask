#include "BTransform.h"

void BTransform::updateTransformMatrix()
{
	transformMat = DirectX::XMMatrixRotationRollPitchYaw(rotX, rotY, rotZ) * DirectX::XMMatrixTranslation(x, y, z);
}

BTransform::BTransform(DTGraphics& gfx)
	:
	x(0.0f),
	y(0.0f),
	z(0.0f),
	rotX(0.0f),
	rotY(0.0f),
	rotZ(0.0f)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<BVertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}

	updateTransformMatrix();
}

BTransform::BTransform(DTGraphics& gfx, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot)
	:
	x(xPos),
	y(yPos),
	z(zPos),
	rotX(xRot),
	rotY(yRot),
	rotZ(zRot)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<BVertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}

	updateTransformMatrix();
}

void BTransform::Bind(DTGraphics& gfx) noexcept
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixTranspose(transformMat * gfx.GetProjection());

	pVcbuf->Update(gfx, mat);
	pVcbuf->Bind(gfx);
}

void BTransform::Translate(float xPos, float yPos, float zPos) noexcept
{
	x += xPos;
	y += yPos;
	z += zPos;

	updateTransformMatrix();
}

void BTransform::SetPosition(float xPos, float yPos, float zPos) noexcept
{
	x = xPos;
	y = yPos;
	z = zPos;

	updateTransformMatrix();
}

void BTransform::SetRotation(float xRot, float yRot, float zRot) noexcept
{
	rotX = yRot;
	rotY = xRot;
	rotZ = zRot;

	updateTransformMatrix();
}

DirectX::XMMATRIX BTransform::GetTransormMat() noexcept
{
	return transformMat;
}

