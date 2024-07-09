#pragma once

#include "DTWindow.h"
#include "Timer.h"
#include "DTConfig.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"

//TODO: Add docs
class DTApp
{
private: 
	enum {
		BOX = 0,
		LEVEL_MESH,
		NUM_RO
	};

	std::vector<std::shared_ptr<DTRenderObjectBase>> renderObjects;

	DTWindow window;
	Timer timer;
	std::vector<std::unique_ptr<class DTSceneObject>> sceneObjects;
	LLightGroup lightGroup;
	
	std::vector<PostProcessPass> postProcesses;

	static constexpr size_t nDrawables = 180;

	bool shouldCreateLight = false;

	void AddLight(float x, float y, float z);

	void RunFrame();
	void PostProcessFrame();

	void InitScene();

	void HandleMouseInput(float dt);
	void HandleKeyboardInput(float dt);
	void HandleRendering(float dt);	
public:
	DTApp();
	int Run();

	
};

