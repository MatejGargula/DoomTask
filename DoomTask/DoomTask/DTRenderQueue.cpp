#include "DTRenderQueue.h"

void DTRenderQueue::enableTessalationShaders(DTGraphics& gfx)
{
	HS.Bind(gfx);
	DS.Bind(gfx);
	gfx.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
}

void DTRenderQueue::disableTessalationShaders(DTGraphics& gfx)
{
	HS.Unbind(gfx);
	DS.Unbind(gfx);
	gfx.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DTRenderQueue::renderScene(DTGraphics& gfx, DTScene& scene, float deltaTime)
{
	scene.lightGroup.BindGroup(gfx);
	
	// Bind the G-Buffer textures as multiple render targets
	gBuffer.BindAsRenderTarget(gfx);

	// Bind Vertex and Pixel shader 
	gBuffer.BindCollectionShaders(gfx);

	std::vector<unsigned int> defaultObjects = scene.GetDefaultObjects();
	std::vector<unsigned int> tessalatedObjects = scene.GetTessalatedObjects();

	if (wireframeMode)
		gfx.EnableWireframe();

	scene.lightGroup.RenderLightsRO(gfx);

	// Render the default objects without tessalation
	for (unsigned int soIdx : defaultObjects)
	{
		scene.sceneObjects[soIdx]->Update(deltaTime);
		scene.sceneObjects[soIdx]->Render(gfx);
	}

	enableTessalationShaders(gfx);

	// Render the scene objects with tessalation
	for (unsigned int soIdx : tessalatedObjects)
	{
		scene.sceneObjects[soIdx]->Update(deltaTime);
		scene.sceneObjects[soIdx]->Render(gfx);
	}

	disableTessalationShaders(gfx);
	
	if (wireframeMode)
		gfx.DisableWireframe();
}

void DTRenderQueue::renderPostProcesses(DTGraphics& gfx)
{
	pPostProcessControlCbuf->Update(gfx, postProcessContol);
	pPostProcessControlCbuf->Bind(gfx);

	for (unsigned int i = 0; i < postProcesses.size(); i++)
	{
		postProcesses[i].Render(gfx);
	}
}

DTRenderQueue::DTRenderQueue(DTGraphics& gfx)
	:
	gBuffer(gfx),
	HS(gfx, L"DistanceTessHS.cso"),
	DS(gfx, L"DistanceTessDS.cso")
{
	postProcessContol = {};
	postProcessContol.enablePostProcess = false;

	std::shared_ptr<RenderTargetTexture> targetTex = std::make_shared<RenderTargetTexture>(gfx, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!pPostProcessControlCbuf)
		pPostProcessControlCbuf = std::make_unique<BPixelConstantBuffer<PostProcessControlCbuf>>(gfx, 0u);

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

void DTRenderQueue::RenderObjects(DTGraphics& gfx, DTScene& scene, float deltaTime)
{
	Clear(gfx);

	renderScene(gfx, scene, deltaTime);
	renderPostProcesses(gfx);
}

void DTRenderQueue::Clear(DTGraphics& gfx)
{
	gfx.ClearBackBuffer(0.0f, 0.0f, 0.0f);
	gBuffer.Clear(gfx);
}

void DTRenderQueue::SetWireframeMode(bool enabled)
{
	wireframeMode = enabled;
}

void DTRenderQueue::SetPostProcessingEnabled(bool enabled)
{
	postProcessContol.enablePostProcess = enabled;
}
