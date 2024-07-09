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
	window(SCREEN_WIDTH,SCREEN_HEIGHT, WINDOW_NAME),
	lightGroup(window.Gfx())
{
	InitScene();

	window.DisableCursor();
	window.ConfineCursor();

	//// Create post processes;
	postProcesses.emplace_back( 
		window.Gfx(),
		L"GrayscalePS.cso",
		L"DefaultPostProcessVS.cso",
		window.Gfx().GetMainRenderTexture());
}

void DTApp::InitScene()
{
	renderObjects.resize(NUM_RO);
	renderObjects[BOX] = std::make_shared<RBox>(window.Gfx());
	renderObjects[LEVEL_MESH] = std::make_shared<RMultiMesh>(window.Gfx(), "Models\\DoomLevel.obj");;

	//std::shared_ptr<DTRenderObjectBase> plane = std::make_shared<RTexPlane>(window.Gfx());
	//std::shared_ptr<DTRenderObjectBase> suzanne = std::make_shared<RMesh>(window.Gfx(), "Models\\suzanne.obj");
	//std::shared_ptr<DTRenderObjectBase> teapot = std::make_shared<RMesh>(window.Gfx(), "Models\\teapot.obj");
	
	std::unique_ptr<DTSceneObject> level = std::make_unique<DTSceneObject>(window.Gfx(), renderObjects[LEVEL_MESH]);
	level->transform.SetPosition(0.0f, -3.0f, 0.0f);
	level->transform.SetRotation(0.0f, 0.0f, 0.0f);
	sceneObjects.push_back(std::move(level));

	std::unique_ptr<LPointLight> light1 = std::make_unique<LPointLight>();
	light1->EnableLightRenderObject(renderObjects[BOX]);

	std::unique_ptr<LPointLight> light2 = std::make_unique<LPointLight>();
	light2->SetPosition(DirectX::XMFLOAT3(20.0f, 0.0f, 42.0f));
	light2->EnableLightRenderObject(renderObjects[BOX]);

	lightGroup.AddLight(std::move(light1));
	lightGroup.AddLight(std::move(light2));
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

void DTApp::AddLight(float x, float y, float z)
{
	std::unique_ptr<LPointLight> light = std::make_unique<LPointLight>();
	light->SetPosition(DirectX::XMFLOAT3(x, y, z));
	light->EnableLightRenderObject(renderObjects[BOX]);

	lightGroup.AddLight(std::move(light));
}

void DTApp::RunFrame()
{
	const float dt = timer.Mark();
	//float x = window.mouse.GetPosX() / ((float)SCREEN_WIDTH) - 1.0f;
	//float y = -window.mouse.GetPosY() / ((float)SCREEN_HEIGHT) + 1.0f;
	
	angle += dt/2.2f * 180;
	if (angle > 360)
		angle -= 360;

	//sceneObjects[1]->transform.SetRotation(0.0f, angle, 0.0f);

	window.Gfx().ClearBuffer(0.9f, 0.8f, 1.0f);

	HandleMouseInput(dt);
	HandleKeyboardInput(dt);
	HandleRendering(dt);

	PostProcessFrame();

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
			AddLight(window.Gfx().camera->GetPosition().x, window.Gfx().camera->GetPosition().y, window.Gfx().camera->GetPosition().z);
		}
		shouldCreateLight = true;
	}
	else
	{
		shouldCreateLight = false;
	}
	

	window.Gfx().camera->UpdateMovement(dt, movingForward, movingBackward, movingLeft, movingRight);
	std::ostringstream oss;
	oss << "|Number of Lights: " << lightGroup.lights.size() << " |";
	//oss << "X: " << window.Gfx().camera->GetPosition().x
	//	<< " Y: " << window.Gfx().camera->GetPosition().y
	//	<< " Z: " << window.Gfx().camera->GetPosition().z;
	
	std::string positionStr = oss.str();
	window.SetTitle(positionStr);
}

void DTApp::HandleRendering(float dt)
{
	window.Gfx().EnablePostProcessing();
	
	
	pos += 1.0f * dt;
	if (pos > 30.0f)
		pos = 0.0f;

	lightGroup.lights[0]->SetPosition(DirectX::XMFLOAT3(pos,0.0f,pos * 0.3f));
	
	lightGroup.BindGroup(window.Gfx());
	
	lightGroup.RenderLightsRO(window.Gfx());

	for (auto& so : sceneObjects)
	{
		so->Update(dt);
		so->Render(window.Gfx());
	}
}

void DTApp::PostProcessFrame()
{
	window.Gfx().DisablePostProcessing();
	//TODO:: handle post processes;
	for (unsigned int i = 0; i < postProcesses.size(); i++)
	{
		postProcesses[i].Render(window.Gfx());
	}
}