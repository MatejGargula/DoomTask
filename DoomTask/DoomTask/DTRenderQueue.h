#pragma once

#include "DTGraphics.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"
#include "GBuffer.h"
#include "BHullShader.h"
#include "BDomainShader.h"
#include "DTScene.h"

class DTRenderQueue
{
private: 
	LLightGroup lightGroup;
	GBuffer gBuffer;
	std::vector<PostProcessPass> postProcesses;

	BHullShader HS;
	BDomainShader DS;

	bool wireframeMode = false;

	void enableTessalationShaders(DTGraphics& gfx);
	void disableTessalationShaders(DTGraphics& gfx);
	void renderScene(DTGraphics& gfx, DTScene& scene, float deltaTime);
	void renderPostProcesses(DTGraphics& gfx);
public:
	DTRenderQueue(DTGraphics& gfx);
	void RenderObjects(
		DTGraphics& gfx,
		DTScene& scene,
		float deltaTime);
	void Clear(DTGraphics& gfx);
	void AddLight(float x, float y, float z);
	void SetWireframeMode(bool enabled);
};

