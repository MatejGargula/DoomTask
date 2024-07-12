#pragma once

#include "DTWindow.h"
#include "Timer.h"
#include "DTConfig.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"
#include "GBuffer.h"
#include "DTRenderQueue.h"

/// <summary>
/// Main class for the application control.
/// </summary>
class DTApp
{
private: 
	enum {
		LEVEL_MESH = 0,
		TESTING_SPHERE,
		LIGHT_MESH,
		NUM_RO
	};
	
	DTWindow window;
	Timer timer;

	std::vector<std::shared_ptr<DTRenderObjectBase>> renderObjects;
	
	DTRenderQueue renderQueue;
	DTScene scene;

	bool shouldCreateLight = false;

	/// <summary>
	/// Processes and renders the current frame.
	/// </summary>
	void runFrame();

	/// <summary>
	/// Initializes the scene with objects and lights.
	/// </summary>
	void initScene();

	/// <summary>
	/// Handles the user mouse input.
	/// </summary>
	/// <param name="dt"></param>
	void handleMouseInput(float dt);

	/// <summary>
	/// Handles the user keyboard input.
	/// </summary>
	/// <param name="dt"></param>
	void handleKeyboardInput(float dt);

public:
	DTApp();

	/// <summary>
	/// Runs the application.
	/// </summary>
	/// <returns></returns>
	int Run();

};