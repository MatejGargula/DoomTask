#pragma once

#include "DTRenderObjectBase.h"

class LPointLight
{
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

	bool showLightRO;
	std::shared_ptr<DTRenderObjectBase> lightRO;
	std::unique_ptr<BPixelConstantBuffer<PointLightCBuf>> pPcbuf;

public:
	LPointLight(DTGraphics& gfx,
		DirectX::XMFLOAT3 pos = {0.0f, 0.0f ,0.0f }, 
		DirectX::XMFLOAT3 amb = { 0.2f, 0.2f ,0.2f },
		DirectX::XMFLOAT3 diff = { 1.0f, 1.0f ,1.0f },
		DirectX::XMFLOAT3 spec = { 0.4f, 0.1f ,0.1f },
		float constant = 1.0f,
		float linear = 0.35f,
		float quadratic = 0.44f
	);
	void Bind(DTGraphics& gfx) noexcept;
	void EnableLightRenderObject(std::shared_ptr<DTRenderObjectBase> mesh);
	void Render(DTGraphics& gfx);
	void DisableLightRenderObject();
	void SetPosition(DirectX::XMFLOAT3 pos);
};

