#include "DTApp.h"
#include "RBox.h"
#include "RTexPlane.h"
#include "RMesh.h"
#include "RMultiMesh.h"
#include "DTMath.h"
#include "BMaterial.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

float angle = 0;
float pos = 0;

DTApp::DTApp()
	:
	window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME),
	renderQueue(window.Gfx())
{
	InitScene();

	window.DisableCursor();
	window.ConfineCursor();

	std::shared_ptr<RenderTargetTexture> targetTex = std::make_shared<RenderTargetTexture>(window.Gfx(), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void DTApp::InitScene()
{
	renderObjects.resize(NUM_RO);
	renderObjects[BOX] = std::make_shared<RBox>(window.Gfx());
	renderObjects[LEVEL_MESH] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\DoomLevel.obj");;
	renderObjects[TESTING_SPHERE] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\Sphere.obj");;

	renderObjects[LEVEL_MESH]->DisableShaders();
	renderObjects[TESTING_SPHERE]->DisableShaders();

	//std::shared_ptr<DTRenderObjectBase> plane = std::make_shared<RTexPlane>(window.Gfx());
	//std::shared_ptr<DTRenderObjectBase> suzanne = std::make_shared<RMesh>(window.Gfx(), "Models\\suzanne.obj");
	//std::shared_ptr<DTRenderObjectBase> teapot = std::make_shared<RMesh>(window.Gfx(), "Models\\teapot.obj");
	
	std::unique_ptr<DTSceneObject> level = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[LEVEL_MESH]);
	level->transform.SetPosition(0.0f, -3.0f, 0.0f);
	level->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(level));

	std::unique_ptr<DTSceneObject> sphere1 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere1->transform.SetPosition(20.0f, 0.0f, 5.0f);
	sphere1->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(sphere1));

	std::unique_ptr<DTSceneObject> sphere2 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere2->transform.SetPosition(5.0f, 0.0f, 15.0f);
	sphere2->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(sphere2));

	std::unique_ptr<DTSceneObject> sphere3 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere3->transform.SetPosition(3.0f, 0.0f, 35.0f);
	sphere3->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(sphere3));

	renderQueue.AddLight(0.0f, 0.0f, 0.0f);
	renderQueue.AddLight(20.0f, 0.0f, 42.0f);
}

int DTApp::Run()
{
	while (true)
	{
		if (const std::optional<int> retCode = DTWindow::ProcessMessages())
			return *retCode;

		RunFrame();
	}

	return 42;
}

void DTApp::RunFrame()
{
	const float dt = timer.Mark();
	
	angle += dt/2.2f * 180;
	if (angle > 360)
		angle -= 360;

	HandleMouseInput(dt);
	HandleKeyboardInput(dt);

	renderQueue.RenderObjects(window.Gfx(), sceneObjects, renderObjects, dt);

	window.Gfx().EndFrame();
	
}

void DTApp::HandleMouseInput(float dt)
{
	while (const auto delta = window.mouse.ReadRawDelta())
	{
		window.Gfx().camera->Rotate(delta->x, delta->y);
	}
}

void DTApp::HandleKeyboardInput(float dt)
{
	bool movingForward = false;
	bool movingBackward = false;
	bool movingRight = false;
	bool movingLeft = false;

	if (window.keyboard.KeyIsPressed('W'))
	{
		movingForward = true;
	}
	if (window.keyboard.KeyIsPressed('S'))
	{
		movingBackward = true;
	}
	if (window.keyboard.KeyIsPressed('A'))
	{
		movingLeft= true;
	}
	if (window.keyboard.KeyIsPressed('D'))
	{
		movingRight = true;
	}

	if (window.keyboard.KeyIsPressed('C'))
	{
		if (!shouldCreateLight)
		{
			renderQueue.AddLight(window.Gfx().camera->GetPosition().x, window.Gfx().camera->GetPosition().y, window.Gfx().camera->GetPosition().z);
		}
		shouldCreateLight = true;
	}
	else
	{
		shouldCreateLight = false;
	}
	

	window.Gfx().camera->UpdateMovement(dt, movingForward, movingBackward, movingLeft, movingRight);
	//std::ostringstream oss;
	//oss << "|Number of Lights: " << lightGroup.lights.size() << " |";
	//oss << "X: " << window.Gfx().camera->GetPosition().x
	//	<< " Y: " << window.Gfx().camera->GetPosition().y
	//	<< " Z: " << window.Gfx().camera->GetPosition().z;
	
	//std::string positionStr = oss.str();
	//window.SetTitle(positionStr);
}