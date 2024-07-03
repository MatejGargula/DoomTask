#pragma once

#include <DirectXMath.h>

class DTCamera
{
private: 
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 up;

	DirectX::XMMATRIX projection;

	float yaw = 0.0f;
	float pitch = 0.0f;
	float mouseSensitivity = 1.0f; 
	float moveSpeed = 5.0f; 

public:
	DTCamera();
	DTCamera(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 fwd, DirectX::XMFLOAT3 up);
	DTCamera(
		DirectX::XMFLOAT3 pos,
		DirectX::XMFLOAT3 fwd,
		DirectX::XMFLOAT3 up,
		const float& fov,
		const float& aspectRatio,
		const float& nearZ,
		const float& farZ
	);

	void UpdateCamera(float deltaTime, float mouseX, float mouseY, bool moveForward, bool moveBackward, bool moveLeft, bool moveRight);

	void SetProjectionMatrix(const float& fov, const float& aspectRatio, const float& nearZ, const float& farZ);
	DirectX::XMMATRIX GetProjectionMatrix();
	DirectX::XMMATRIX GetViewMatrix();

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetForward();
	DirectX::XMFLOAT3 GetUp();


	void SetPosition(float x, float y, float z);
	void SetForward(float x, float y, float z);
	void SetUp(float x, float y, float z);

};

