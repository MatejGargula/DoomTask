#pragma once

#include "DTWindow.h"
#include "Timer.h"
#include "DTConfig.h"
#include "DTSceneObject.h"
#include "LPointLight.h"

//TODO: Add docs
class DTApp
{
private: 
	DTWindow window;
	Timer timer;
	std::vector<std::unique_ptr<class DTSceneObject>> sceneObjects;
	LPointLight light;
	
	static constexpr size_t nDrawables = 180;

	void RunFrame();

	void InitScene();

	void HandleMouseInput(float dt);
	void HandleKeyboardInput(float dt);
	void HandleRendering(float dt);

public:
	DTApp();
	int Run();
};

