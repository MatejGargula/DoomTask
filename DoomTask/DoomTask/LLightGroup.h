#pragma once

#include "LPointLight.h"

/// <summary>
/// Class for storing the information about a specified group of point lights. 
/// </summary>
class LLightGroup
{
private: 
	/// <summary>
	/// Structure for storing the light data for the constant light buffer
	/// </summary>
	struct LightGroupCbuf
	{
		LPointLight::PointLightCBuf lights[MAX_LIGHTS];
		int nLights;
		float pad[3];
	};

	LightGroupCbuf data;
	std::unique_ptr<BPixelConstantBuffer<LightGroupCbuf>> pPcbuf;
	bool lightMeshesSetUp = false;
	std::shared_ptr<DTRenderObjectBase> ro;

	/// <summary>
	/// Updates the current data in the attached constant buffer.
	/// </summary>
	void updateData();
public: 
	std::vector<std::unique_ptr<LPointLight>> lights;

	LLightGroup(DTGraphics& gfx);

	/// <summary>
	/// Binds the constant buffer containing the data about the light group to the pipeline.
	/// </summary>
	/// <param name="gfx"></param>
	void BindGroup(DTGraphics& gfx);

	/// <summary>
	/// Add a light to the group.
	/// </summary>
	/// <param name="light"> unique pointer to the light </param>
	void AddLight(std::unique_ptr<LPointLight> light);
	
	/// <summary>
	/// Renders the set meshes for visualizing the light position.
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	void RenderLightsRO(DTGraphics& gfx);

	/// <summary>
	/// Sets up the mesh for visualizing the positions of the lights.
	/// </summary>
	/// <param name="roMesh"> mesh to render on the position of the lights </param>
	void SetUpLightMeshes(std::shared_ptr<DTRenderObjectBase> roMesh);
};

