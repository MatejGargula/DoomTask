#include "DTRenderQueue.h"

void DTRenderQueue::renderScene(DTGraphics& gfx, std::vector<std::unique_ptr<DTSceneObject>>& sceneObjects, float deltaTime)
{
	lightGroup.BindGroup(gfx);
	
	// Bind the G-Buffer textures as multiple render targets
	gBuffer.BindAsRenderTarget(gfx);

	// Bind Vertex and Pixel shader 
	gBuffer.BindCollectionShaders(gfx);

	// Render the scene
	for (auto& so : sceneObjects)
	{
		so->Update(deltaTime);
		so->Render(gfx);
	}
}

void DTRenderQueue::renderPostProcesses(DTGraphics& gfx)
{
	for (unsigned int i = 0; i < postProcesses.size(); i++)
	{
		postProcesses[i].Render(gfx);
	}
}

DTRenderQueue::DTRenderQueue(DTGraphics& gfx)
	:
	lightGroup(gfx),
	gBuffer(gfx)
{
	std::shared_ptr<RenderTargetTexture> targetTex = std::make_shared<RenderTargetTexture>(gfx, SCREEN_WIDTH, SCREEN_HEIGHT);

	// TODO: Refactor post processes
	// Create post processes;
	postProcesses.emplace_back(
		gfx,
		L"DefferedFinalPS.cso",
		L"DefaultPostProcessVS.cso",
		gBuffer.GetRenderTextures(),
		targetTex);

	postProcesses.emplace_back(
		gfx,
		L"OldSchoolPS.cso",
		L"DefaultPostProcessVS.cso",
		targetTex);
}

void DTRenderQueue::RenderObjects(DTGraphics& gfx, std::vector<std::unique_ptr<DTSceneObject>>& sceneObjects, std::vector<std::shared_ptr<DTRenderObjectBase>>& renderObjects, float deltaTime)
{
	Clear(gfx);

	// Disable default mesh shaders for the deffered rendering
	for (int i = 0; i < renderObjects.size(); i++)
	{
		renderObjects[i]->DisableShaders();
	}

	renderScene(gfx, sceneObjects, deltaTime);
	renderPostProcesses(gfx);
}

void DTRenderQueue::Clear(DTGraphics& gfx)
{
	gfx.ClearBuffer(0.0f, 0.0f, 0.0f);
	gBuffer.Clear(gfx);
}

void DTRenderQueue::AddLight(float x, float y, float z)
{
	std::unique_ptr<LPointLight> light = std::make_unique<LPointLight>();
	light->SetPosition(DirectX::XMFLOAT3(x, y, z));

	lightGroup.AddLight(std::move(light));
}