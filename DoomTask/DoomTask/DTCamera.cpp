#include "DTCamera.h"
#include "DTMath.h"

DTCamera::DTCamera()
	:
	position(0.0f,0.0f,0.0f),
	forward(0.0f, 0.0f, 0.0f),
	up(0.0f, 0.0f, 0.0f)
{
	projection = DirectX::XMMatrixIdentity();
}

DTCamera::DTCamera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 fwd, DirectX::XMFLOAT3 up)
	:
	position(pos),
	forward(fwd),
	up(up)
{
	projection = DirectX::XMMatrixIdentity();
}

DTCamera::DTCamera(
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
	SetProjectionMatrix(fov, aspectRatio, nearZ, farZ);
}

void DTCamera::UpdateCamera(float deltaTime, float mouseX, float mouseY, bool moveForward, bool moveBackward, bool moveLeft, bool moveRight)
{
	// Update yaw and pitch based on mouse movement
	yaw += mouseX * mouseSensitivity;
	pitch += mouseY * mouseSensitivity;

	// Clamp pitch to prevent flipping
	if (pitch > PI_DIV_TWO)
		pitch = PI_DIV_TWO;
	if (pitch < -PI_DIV_TWO)
		pitch = -PI_DIV_TWO;

	// Calculate the new forward vector
	DirectX::XMVECTOR forwardVec = DirectX::XMVectorSet(
		cosf(pitch) * cosf(yaw),
		sinf(pitch),
		cosf(pitch) * sinf(yaw),
		0.0f
	);

	// Save new forward vector
	DirectX::XMStoreFloat3(&forward, forwardVec);

	DirectX::XMVECTOR upVec = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);

	// Calculate the new right vector
	DirectX::XMVECTOR rightVec = DirectX::XMVector3Cross(upVec, forwardVec);

	// Update the position
	DirectX::XMVECTOR positionVec = DirectX::XMVectorSet(position.x, position.y, position.z,0.0f);

	if (moveForward)
		positionVec = DirectX::XMVectorAdd(positionVec, DirectX::XMVectorScale(forwardVec, moveSpeed * deltaTime));
	
	if (moveBackward)
		positionVec = DirectX::XMVectorSubtract(positionVec, DirectX::XMVectorScale(forwardVec, moveSpeed * deltaTime));
	
	if (moveLeft)
		positionVec = DirectX::XMVectorSubtract(positionVec, DirectX::XMVectorScale(rightVec, moveSpeed * deltaTime));
	
	if (moveRight) 
		positionVec = DirectX::XMVectorAdd(positionVec, DirectX::XMVectorScale(rightVec, moveSpeed * deltaTime));

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
	
	DirectX::XMVECTOR positionVec = DirectX::XMVectorSet(position.x, position.y, position.z, 1.0f);
	DirectX::XMVECTOR forwardVec = DirectX::XMVectorSet(forward.x, forward.y, forward.z, 0.0f);
	DirectX::XMVECTOR upVec = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);
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

