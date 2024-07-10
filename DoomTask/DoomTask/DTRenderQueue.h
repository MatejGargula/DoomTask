#pragma once

#include "DTGraphics.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"
#include "GBuffer.h"

class DTRenderQueue
{
private: 
	LLightGroup lightGroup;
	GBuffer gBuffer;
	std::vector<PostProcessPass> postProcesses;

	void renderScene(DTGraphics& gfx, std::vector<std::unique_ptr<DTSceneObject>>& sceneObjects, float deltaTime);
	void renderPostProcesses(DTGraphics& gfx);
public:
	DTRenderQueue(DTGraphics& gfx);
	void RenderObjects(
		DTGraphics& gfx,
		std::vector<std::unique_ptr<DTSceneObject>>& sceneObjects,
		std::vector<std::shared_ptr<DTRenderObjectBase>>& renderObjects,
		float deltaTime);
	void Clear(DTGraphics& gfx);
	void AddLight(float x, float y, float z);
};

