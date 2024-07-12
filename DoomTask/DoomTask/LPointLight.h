#pragma once

#include "DTRenderObjectBase.h"

/// <summary>
/// Class for storing the data about a single point light
/// </summary>
class LPointLight
{
	friend class LLightGroup;
private:
	struct PointLightCBuf
	{
		DirectX::XMFLOAT3 position;
		float pad1;
		DirectX::XMFLOAT3 ambient;
		float pad2;
		DirectX::XMFLOAT3 diffuse;
		float pad3;
		DirectX::XMFLOAT3 specular;
		float pad4;
		DirectX::XMFLOAT3 att;
		float pad5;
	};

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 ambient;
	DirectX::XMFLOAT3 diffuse;
	DirectX::XMFLOAT3 specular;

	float constant;
	float linear;
	float quadratic;

	BTransform transf;
	std::unique_ptr<BPixelConstantBuffer<PointLightCBuf>> pPcbuf;

public:
	LPointLight(DTGraphics& gfx,
		DirectX::XMFLOAT3 pos = {0.0f, 0.0f ,0.0f },
		DirectX::XMFLOAT3 amb = { 0.2f, 0.2f ,0.2f },
		DirectX::XMFLOAT3 diff = { 1.0f, 1.0f ,1.0f },
		DirectX::XMFLOAT3 spec = { 1.0f, 1.0f ,1.0f },
		float constant = 1.0f,
		float linear = 0.045f,
		float quadratic = 0.0075f
	);

	/// <summary>
	/// Renders the render object (ro) to visualize the position of the light.
	/// </summary>
	/// <param name="gfx">Main graphics class </param>
	/// <param name="ro"> Mesh (Render Object) to render </param>
	void Render(DTGraphics& gfx, DTRenderObjectBase* ro);

	/// <summary>
	/// Sets the position of the point light.
	/// </summary>
	/// <param name="pos"> The new position of the point light </param>
	void SetPosition(DirectX::XMFLOAT3 pos);
};

