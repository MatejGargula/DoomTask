#pragma once

#include "DTWindow.h"
#include "Timer.h"
#include "DTConfig.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"
#include "GBuffer.h"
#include "DTRenderQueue.h"

//TODO: Add docs
class DTApp
{
private: 
	enum {
		BOX = 0,
		LEVEL_MESH,
		TESTING_SPHERE,
		NUM_RO
	};
	
	DTWindow window;
	Timer timer;

	std::vector<std::shared_ptr<DTRenderObjectBase>> renderObjects;
	std::vector<std::unique_ptr<DTSceneObject>> sceneObjects;
	
	DTRenderQueue renderQueue;

	bool shouldCreateLight = false;

	void RunFrame();
	void InitScene();
	void HandleMouseInput(float dt);
	void HandleKeyboardInput(float dt);

public:
	DTApp();
	int Run();

	
};

