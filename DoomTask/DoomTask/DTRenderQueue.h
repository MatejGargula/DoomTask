#pragma once

#include "DTGraphics.h"
#include "DTSceneObject.h"
#include "LLightGroup.h"
#include "PostProcessPass.h"
#include "GBuffer.h"
#include "BHullShader.h"
#include "BDomainShader.h"
#include "DTScene.h"

/// <summary>
/// Class for handling the rendering of the scene objects along with postprocessing.
/// </summary>
class DTRenderQueue
{
private: 
	GBuffer gBuffer;
	std::vector<PostProcessPass> postProcesses;

	struct PostProcessControlCbuf
	{
		bool enablePostProcess;
		float pad[3];
	};

	PostProcessControlCbuf postProcessContol;
	std::unique_ptr<BPixelConstantBuffer<PostProcessControlCbuf>> pPostProcessControlCbuf;

	BHullShader HS;
	BDomainShader DS;

	bool wireframeMode = false;

	/// <summary>
	/// Enables the tessalation in the pipeline.
	/// </summary>
	/// <param name="gfx"></param>
	void enableTessalationShaders(DTGraphics& gfx);

	/// <summary>
	/// Disables the tessalation in the pipeline
	/// </summary>
	/// <param name="gfx"></param>
	void disableTessalationShaders(DTGraphics& gfx);

	/// <summary>
	/// Renders the given scene.
	/// </summary>
	/// <param name="gfx"> Main graphics class</param>
	/// <param name="scene"> current scene to render </param>
	/// <param name="deltaTime"> delta time of the frame </param>
	void renderScene(DTGraphics& gfx, DTScene& scene, float deltaTime);
	void renderPostProcesses(DTGraphics& gfx);
public:
	DTRenderQueue(DTGraphics& gfx);
	
	/// <summary>
	/// Renders the given scene
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	/// <param name="scene"> scene to render </param>
	/// <param name="deltaTime"> delta time of the current frame </param>
	void RenderObjects(
		DTGraphics& gfx,
		DTScene& scene,
		float deltaTime);

	/// <summary>
	/// Clears render targets
	/// </summary>
	/// <param name="gfx">Main graphics class </param>
	void Clear(DTGraphics& gfx);

	/// <summary>
	/// Enables/Disables wireframe mode
	/// </summary>
	/// <param name="enabled"></param>
	void SetWireframeMode(bool enabled);

	/// <summary>
	/// Enables/Disables the post processes
	/// </summary>
	/// <param name="enabled"></param>
	void SetPostProcessingEnabled(bool enabled);

};

