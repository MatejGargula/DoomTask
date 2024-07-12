#pragma once

#include <DirectXMath.h>

/// <summary>
/// Class for controling and managing the camera. Also for retrieving the view and projection matrix.
/// </summary>
class DTCamera
{
private: 
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 up;

	DirectX::XMMATRIX projection;

	float yaw = 0.0f;
	float pitch = 0.0f;
	float mouseSensitivity = 0.001f; 
	float moveSpeed = 15.0f; 

public:
	DTCamera();
	DTCamera(
		DirectX::XMFLOAT3 pos,
		DirectX::XMFLOAT3 fwd,
		DirectX::XMFLOAT3 up,
		const float& fov,
		const float& aspectRatio,
		const float& nearZ,
		const float& farZ
	);

	/// <summary>
	/// Rotates the camera based on the raw mouse input.
	/// </summary>
	/// <param name="mouseX">Raw mouse input on the X axis</param>
	/// <param name="mouseY">Raw mouse input on the Y axis</param>
	void Rotate(float mouseX, float mouseY);

	/// <summary>
	/// Moves the camera in selected directions 
	/// </summary>
	/// <param name="deltaTime"> delta time of the frame </param>
	/// <param name="moveForward"> camera should move forward </param>
	/// <param name="moveBackward"> camera should move backward </param>
	/// <param name="moveLeft"> camera should move left </param>
	/// <param name="moveRight"> camera should move right </param>
	void UpdateMovement(float deltaTime, bool moveForward, bool moveBackward, bool moveLeft, bool moveRight);

	/// <summary>
	/// Sets up the required parameters for the perspective projection.
	/// </summary>
	/// <param name="fov"> Field of view </param>
	/// <param name="aspectRatio"> Aspect ratio of the view </param>
	/// <param name="nearZ">nearZ parameter of the camera projection</param>
	/// <param name="farZ">farZ parameter of the camera projection</param>
	void SetProjectionMatrix(const float& fov, const float& aspectRatio, const float& nearZ, const float& farZ);
	
	/// <summary>
	/// Returns the projection matrix.
	/// </summary>
	/// <returns></returns>
	DirectX::XMMATRIX GetProjectionMatrix();
	
	/// <summary>
	/// Returns the view matrix.
	/// </summary>
	/// <returns></returns>
	DirectX::XMMATRIX GetViewMatrix();

	/// <summary>
	/// Returns the current position of the mouse.
	/// </summary>
	/// <returns></returns>
	DirectX::XMFLOAT3 GetPosition();

	/// <summary>
	/// Returns the forward vector of the camera.
	/// </summary>
	/// <returns></returns>
	DirectX::XMFLOAT3 GetForward();

	/// <summary>
	/// Returns the up vector of the camera.
	/// </summary>
	/// <returns></returns>
	DirectX::XMFLOAT3 GetUp();

	/// <summary>
	/// Sets the position of the camera based on the input.
	/// </summary>
	/// <param name="x"> X position </param>
	/// <param name="y"> Y position </param>
	/// <param name="z"> Z position </param>
	void SetPosition(float x, float y, float z);
	
	/// <summary>
	/// Sets the forward vector of the camera
	/// </summary>
	/// <param name="x"> X component of the forward vector </param>
	/// <param name="y"> Y component of the forward vector </param>
	/// <param name="z"> Z component of the forward vector </param>
	void SetForward(float x, float y, float z);
	
	/// <summary>
	/// Sets the up vector of the camera
	/// </summary>
	/// <param name="x"> X component of the up vector </param>
	/// <param name="y"> Y component of the up vector </param>
	/// <param name="z"> Z component of the up vector </param>
	void SetUp(float x, float y, float z);

};

