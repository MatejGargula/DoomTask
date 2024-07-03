#include "BTransform.h"

void BTransform::updateTransformMatrix()
{
	modelMat = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * DirectX::XMMatrixTranslation(position.x, position.y, position.z);
}

BTransform::Transforms BTransform::getTransformMatrices(DTGraphics &gfx)
{
	//TODO: Add View matrix from camera 
	const DirectX::XMMATRIX modelViewMat = modelMat * gfx.camera->GetViewMatrix();
	const DirectX::XMMATRIX modelViewProjectionMat = modelViewMat * gfx.camera->GetProjectionMatrix();

	return {
		DirectX::XMMatrixTranspose(modelMat),
		DirectX::XMMatrixTranspose(modelViewMat),
		DirectX::XMMatrixTranspose(modelViewProjectionMat)
	};
}

BTransform::BTransform(DTGraphics& gfx)
	:
	position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<BVertexConstantBuffer<Transforms>>(gfx, 0u);
	}

	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffCameraData>>(gfx, 0u);
	}

	updateTransformMatrix();
}

BTransform::BTransform(DTGraphics& gfx, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot)
	:
	position(xPos, yPos, zPos),
	rotation(xRot, yRot, zRot)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<BVertexConstantBuffer<BTransform::Transforms>>(gfx, 0u);
	}

	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffCameraData>>(gfx, 0u);
	}

	updateTransformMatrix();
}

void BTransform::Bind(DTGraphics& gfx) noexcept
{
	Transforms dataVert = getTransformMatrices(gfx);

	pVcbuf->Update(gfx, dataVert);
	pVcbuf->Bind(gfx);

	CbuffCameraData dataPix = {};
//	dataPix.pos = 
	DirectX::XMFLOAT3 camPos = gfx.camera->GetPosition();
	DirectX::XMStoreFloat3(&dataPix.pos, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&camPos), dataVert.modelView));

	pPcbuf->Update(gfx, dataPix);
	pPcbuf->Bind(gfx);
}

void BTransform::Translate(float xPos, float yPos, float zPos) noexcept
{
	position.x += xPos;
	position.y += yPos;
	position.z += zPos;

	updateTransformMatrix();
}

void BTransform::SetPosition(float xPos, float yPos, float zPos) noexcept
{
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;

	updateTransformMatrix();
}

void BTransform::SetRotation(float xRot, float yRot, float zRot) noexcept
{
	rotation.x = xRot;
	rotation.y = yRot;
	rotation.z = zRot;

	updateTransformMatrix();
}

DirectX::XMMATRIX BTransform::GetTransormMat() noexcept
{
	return modelMat;
}

