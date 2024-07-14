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
#include <fstream>

DTApp::DTApp()
	:
	window(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME),
	renderQueue(window.Gfx()),
	scene(window.Gfx())
{
	initScene();

	window.DisableCursor();
	window.ConfineCursor();

	std::shared_ptr<RenderTargetTexture> targetTex = std::make_shared<RenderTargetTexture>(window.Gfx(), SCREEN_WIDTH, SCREEN_HEIGHT);
}

void DTApp::initScene()
{
	renderObjects.resize(NUM_RO);
	renderObjects[LEVEL_MESH] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\DoomLevel.obj");;
	renderObjects[TESTING_SPHERE] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\Sphere.obj");;
	renderObjects[LIGHT_MESH] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\LightMesh.obj");;

	std::unique_ptr<DTSceneObject> level = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[LEVEL_MESH]);
	level->transform.SetPosition(0.0f, -3.0f, 0.0f);
	level->transform.SetRotation(0.0f, 0.0f, 0.0f);
	scene.AddSceneObject(std::move(level));

	std::unique_ptr<DTSceneObject> sphere1 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere1->transform.SetPosition(0.0f, 0.0f, 10.0f);
	sphere1->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sphere1->type = DTSceneObject::Type::TESSALATED;
	scene.AddSceneObject(std::move(sphere1));

	std::unique_ptr<DTSceneObject> sphere2 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere2->transform.SetPosition(-18.0f, 0.0f, 22.0f);
	sphere2->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sphere2->type = DTSceneObject::Type::TESSALATED;
	scene.AddSceneObject(std::move(sphere2));

	std::unique_ptr<DTSceneObject> sphere3 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere3->transform.SetPosition(59.4451f, 0.0f, 8.76196f);
	sphere3->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sphere3->type = DTSceneObject::Type::TESSALATED;
	scene.AddSceneObject(std::move(sphere3));

	std::unique_ptr<DTSceneObject> sphere4 = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[TESTING_SPHERE]);
	sphere4->transform.SetPosition(9.03527f, 0.0f, -35.3904f);
	sphere4->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sphere4->type = DTSceneObject::Type::TESSALATED;
	scene.AddSceneObject(std::move(sphere4));

	loadLights();
	scene.SetUpLightMesh(renderObjects[LIGHT_MESH]);
}

int DTApp::Run()
{
	while (true)
	{
		if (const std::optional<int> retCode = DTWindow::ProcessMessages())
			return *retCode;

		runFrame();
	}

	return 42;
}

void DTApp::runFrame()
{
	const float dt = timer.Mark();

	handleMouseInput(dt);
	handleKeyboardInput(dt);

	renderQueue.RenderObjects(window.Gfx(), scene, dt);

	window.Gfx().EndFrame();
	
}

void DTApp::handleMouseInput(float dt)
{
	while (const auto delta = window.mouse.ReadRawDelta())
	{
		window.Gfx().camera->Rotate(delta->x, delta->y);
	}
}

void DTApp::handleKeyboardInput(float dt)
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
			scene.AddLight(window.Gfx(), window.Gfx().camera->GetPosition().x, window.Gfx().camera->GetPosition().y, window.Gfx().camera->GetPosition().z);
		}
		shouldCreateLight = true;
	}
	else
	{
		shouldCreateLight = false;
	}
	
	if (window.keyboard.KeyIsPressed('I'))
	{
		renderQueue.SetWireframeMode(true);
	}
	if (window.keyboard.KeyIsPressed('K'))
	{
		renderQueue.SetWireframeMode(false);
	}
	if (window.keyboard.KeyIsPressed('O'))
	{
		renderQueue.SetPostProcessingEnabled(true);
	}
	if (window.keyboard.KeyIsPressed('L'))
	{
		renderQueue.SetPostProcessingEnabled(false);
	}
	if (window.keyboard.KeyIsPressed('M'))
	{
		window.DisableCursor();
		window.ConfineCursor();
	}
	if (window.keyboard.KeyIsPressed('N'))
	{
		window.EnableCursor();
		window.FreeCursor();
	}

	window.Gfx().camera->UpdateMovement(dt, movingForward, movingBackward, movingLeft, movingRight);
}

void DTApp::storeLights()
{
	std::ofstream fileIn("lights.txt");
	
	fileIn << scene.lightGroup.lights.size() << std::endl;

	for (unsigned int i = 0; i < scene.lightGroup.lights.size(); i++)
	{
		fileIn << scene.lightGroup.lights[i]->position.x << " " << scene.lightGroup.lights[i]->position.y << " " << scene.lightGroup.lights[i]->position.z << std::endl;
	}
	fileIn.close();
}

void DTApp::loadLights()
{
	std::ifstream fileOut("lights.txt");
	
	float x, y, z, size;

	fileOut >> size;

	for (unsigned int i = 0; i < size; i++)
	{
		fileOut >> x;
		fileOut >> y;
		fileOut >> z;

		y = 4.0f;
		scene.AddLight(window.Gfx(), x, y, z);
	}
	
}
