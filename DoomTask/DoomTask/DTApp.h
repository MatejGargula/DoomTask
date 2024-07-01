#pragma once

#include "DTWindow.h"
#include "Timer.h"
#include "DTConfig.h"
#include "DTSceneObject.h"

//TODO: Add docs
class DTApp
{
private: 
	DTWindow window;
	Timer timer;
	std::vector<std::unique_ptr<class DTSceneObject>> sceneObjects;
	static constexpr size_t nDrawables = 180;

	void RunFrame();

public:
	DTApp();
	int Run();
};

