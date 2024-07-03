#include "DTApp.h"
#include "RBox.h"
#include "RTexPlane.h"
#include "RMesh.h"
#include "DTMath.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

float angle = 0;

DTApp::DTApp()
	:
	window(SCREEN_WIDTH,SCREEN_HEIGHT, WINDOW_NAME)
{

	InitScene();

	window.DisableCursor();
	window.ConfineCursor();
}

void DTApp::InitScene()
{
	std::shared_ptr<DTRenderObjectBase> box = std::make_shared<RBox>(window.Gfx());
	std::shared_ptr<DTRenderObjectBase> plane = std::make_shared<RTexPlane>(window.Gfx());
	std::shared_ptr<DTRenderObjectBase> suzanne = std::make_shared<RMesh>(window.Gfx(), "Models\\suzanne.obj");

	std::unique_ptr<DTSceneObject> so1 = std::make_unique<DTSceneObject>(window.Gfx(), suzanne);
	so1->transform.SetPosition(0.0f, 0.0f, 4.0f);
	sceneObjects.push_back(std::move(so1));

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
	//float x = window.mouse.GetPosX() / ((float)SCREEN_WIDTH) - 1.0f;
	//float y = -window.mouse.GetPosY() / ((float)SCREEN_HEIGHT) + 1.0f;
	
	angle += dt/1.2f;
	if (angle > (TWO_PI))
		angle -= (TWO_PI);

	sceneObjects[0]->transform.SetRotation(angle, 0.0f, angle);

	HandleMouseInput(dt);
	HandleKeyboardInput(dt);
	HandleRendering(dt);
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

	window.Gfx().camera->UpdateMovement(dt, movingForward, movingBackward, movingLeft, movingRight);
}

void DTApp::HandleRendering(float dt)
{
	window.Gfx().ClearBuffer(0.9f, 0.8f, 1.0f);

	for (auto& so : sceneObjects)
	{
		so->Update(dt);
		so->Render(window.Gfx());
	}
}
