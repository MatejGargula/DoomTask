#include "DTApp.h"
#include "RBox.h"
#include "RTexPlane.h"
#include "RMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

DTApp::DTApp()
	:
	window(SCREEN_WIDTH,SCREEN_HEIGHT, WINDOW_NAME)
{
	std::shared_ptr<DTRenderObjectBase> box = std::make_shared<RBox>(window.Gfx());
	std::shared_ptr<DTRenderObjectBase> plane = std::make_shared<RTexPlane>(window.Gfx());
	std::shared_ptr<DTRenderObjectBase> suzanne = std::make_shared<RMesh>(window.Gfx(), "Models\\suzanne.obj");

	std::unique_ptr<DTSceneObject> so1 = std::make_unique<DTSceneObject>(window.Gfx(),plane);
	so1->transform.SetPosition(0.0f, 0.0f,0.0f);
	sceneObjects.push_back(std::move(so1));

	std::unique_ptr<DTSceneObject> so2 = std::make_unique<DTSceneObject>(window.Gfx(), plane);
	so2->transform.SetPosition(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(so2));

	std::unique_ptr<DTSceneObject> so3 = std::make_unique<DTSceneObject>(window.Gfx(), suzanne);
	so3->transform.SetPosition(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(so3));

	std::unique_ptr<DTSceneObject> so4 = std::make_unique<DTSceneObject>(window.Gfx(), suzanne);
	so4->transform.SetPosition(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(so4));

	window.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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

	//window.SetTitle("Time: " + std::to_string(dt));	
	window.Gfx().ClearBuffer(dt, dt, 1.0f);
	
	float angle = window.mouse.GetPosX() / 300.0f;
	float x = window.mouse.GetPosX() / 400.0f - 1.0f;
	float y = -window.mouse.GetPosY() / 300.0f + 1.0f;

	sceneObjects[0]->transform.SetPosition(x, y, 4.0f);
	sceneObjects[0]->transform.SetRotation(angle, 0.0f, angle);
	
	sceneObjects[1]->transform.SetPosition(-x, -y, 4.0f);
	sceneObjects[1]->transform.SetRotation(-angle, 0.0f, -angle);

	sceneObjects[2]->transform.SetPosition(x, -y, 4.0f);
	sceneObjects[2]->transform.SetRotation(angle, 0.0f, -angle);

	sceneObjects[3]->transform.SetPosition(-x, y, 4.0f);
	sceneObjects[3]->transform.SetRotation(-angle, 0.0f, angle);

	for (auto& so : sceneObjects)
	{
		so->Update(dt);
		so->Render(window.Gfx());
	}

	window.Gfx().EndFrame();
}