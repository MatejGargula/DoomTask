#pragma once

#include "LPointLight.h"

class LLightGroup
{
private: 
	struct LightGroupCbuf
	{
		//std::vector<LPointLight> lights;
		LPointLight::PointLightCBuf lights[MAX_LIGHTS];
		int nLights;
		float pad[3];
	};

	LightGroupCbuf data;
	std::unique_ptr<BPixelConstantBuffer<LightGroupCbuf>> pPcbuf;

	void updateData();
public: 
	std::vector<std::unique_ptr<LPointLight>> lights;

	LLightGroup(DTGraphics& gfx);
	void BindGroup(DTGraphics& gfx);
	void AddLight(std::unique_ptr<LPointLight> light);
	void RenderLightsRO(DTGraphics& gfx);
};

