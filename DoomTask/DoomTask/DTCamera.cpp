#include "DTCamera.h"
#include "DTMath.h"

DTCamera::DTCamera(/*DTGraphics& gfx*/)
	:
	position(0.0f,0.0f,0.0f),
	forward(0.0f, 0.0f, 0.0f),
	up(0.0f, 0.0f, 0.0f)
{
	//if (!pPcbuf)
	//{
	//	pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffCameraData>>(gfx, 0u);
	//}
	projection = DirectX::XMMatrixIdentity();
}

DTCamera::DTCamera(/*DTGraphics& gfx,*/
	DirectX::XMFLOAT3 pos,
	DirectX::XMFLOAT3 fwd,
	DirectX::XMFLOAT3 up,
	const float& fov,
	const float& aspectRatio, 
	const float& nearZ,
	const float& farZ)
	:
	position(pos),
	forward(fwd),
	up(up)
{
	//if (!pPcbuf)
	//{
	//	pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffCameraData>>(gfx, 0u);
	//}
	SetProjectionMatrix(fov, aspectRatio, nearZ, farZ);
}

void DTCamera::Rotate(float deltaX, float deltaY)
{
	// Update yaw and pitch based on mouse movement
	yaw += deltaX * mouseSensitivity;
	pitch += deltaY * mouseSensitivity;

	// Clamp pitch to prevent flipping
	if (pitch > PI_DIV_TWO)
		pitch = PI_DIV_TWO;
	if (pitch < -PI_DIV_TWO)
		pitch = -PI_DIV_TWO;

	// Calculate the new forward vector
	DirectX::XMVECTOR forwardVec = DirectX::XMVectorSet(0.0, 0.0, 1.0f, 0.0f);
	DirectX::XMVECTOR lookVec = DirectX::XMVector3Transform(forwardVec, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));

	// Save new forward vector
	DirectX::XMStoreFloat3(&forward, lookVec);
}

void DTCamera::UpdateMovement(float deltaTime, bool moveForward, bool moveBackward, bool moveLeft, bool moveRight)
{
	DirectX::XMVECTOR forwardVec = DirectX::XMLoadFloat3(&forward);
	DirectX::XMVECTOR upVec = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);

	// Calculate the new right vector
	DirectX::XMVECTOR rightVec = DirectX::XMVector3Cross(upVec, forwardVec);
	// Update the position
	DirectX::XMVECTOR positionVec = DirectX::XMLoadFloat3(&position);

	if (moveForward)
		positionVec = DirectX::XMVectorAdd(positionVec, DirectX::XMVectorScale(forwardVec, moveSpeed * deltaTime));
	
	if (moveBackward)
		positionVec = DirectX::XMVectorSubtract(positionVec, DirectX::XMVectorScale(forwardVec, moveSpeed * deltaTime));
	
	if (moveLeft)
		positionVec = DirectX::XMVectorSubtract(positionVec, DirectX::XMVectorScale(rightVec, moveSpeed * deltaTime));
	
	if (moveRight) 
		positionVec = DirectX::XMVectorAdd(positionVec, DirectX::XMVectorScale(rightVec, moveSpeed * deltaTime));

	// Save new position
	DirectX::XMStoreFloat3(&position, positionVec);
}

void DTCamera::SetProjectionMatrix(const float& fov, const float& aspectRatio, const float& nearZ, const float& farZ)
{
	float fovAngleRad = DirectX::XMConvertToRadians(fov); // Field of view in radians
	
	projection = DirectX::XMMatrixPerspectiveFovLH(fovAngleRad, aspectRatio, nearZ, farZ);
}

DirectX::XMMATRIX DTCamera::GetProjectionMatrix()
{
	return projection;
}

DirectX::XMMATRIX DTCamera::GetViewMatrix()
{
	DirectX::XMVECTOR positionVec = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR forwardVec = DirectX::XMVectorAdd(positionVec, DirectX::XMLoadFloat3(&forward)) ;
	DirectX::XMVECTOR upVec = DirectX::XMLoadFloat3(&up);
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(positionVec, forwardVec, upVec);

	return view;
}

DirectX::XMFLOAT3 DTCamera::GetPosition()
{
	return position;
}

DirectX::XMFLOAT3 DTCamera::GetForward()
{
	return forward;
}

DirectX::XMFLOAT3 DTCamera::GetUp()
{
	return up;
}

void DTCamera::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void DTCamera::SetForward(float x, float y, float z)
{
	forward.x = x;
	forward.y = y;
	forward.z = z;
}

void DTCamera::SetUp(float x, float y, float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

//void DTCamera::Bind(DTGraphics& gfx)
//{
//	CbuffCameraData data = {};
//	data.pos = position;
//
//	pPcbuf->Update(gfx, data);
//	pPcbuf->Bind(gfx);
//}

