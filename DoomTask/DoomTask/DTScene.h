#pragma once

#include "DTSceneObject.h"
#include "DTGraphics.h"
#include "LLightGroup.h"
#include <vector>

/// <summary>
/// Class for storing scene data and information. Contains scene objects and lights.
/// </summary>
class DTScene
{
	friend class DTRenderQueue;
public:
	LLightGroup lightGroup;
private:
	std::vector<std::unique_ptr<DTSceneObject>> sceneObjects;

	std::vector<unsigned int> defaultObjects;
	std::vector<unsigned int> tessalatedObjects;

	/// <summary>
	/// Returns the indices of the default type scene objects
	/// </summary>
	/// <returns></returns>
	std::vector<unsigned int>& GetDefaultObjects();

	/// <summary>
	/// Returns the indices of the tessalated type scene objects
	/// </summary>
	/// <returns></returns>
	std::vector<unsigned int>& GetTessalatedObjects();

public: 
	DTScene(DTGraphics& gfx);

	/// <summary>
	/// Add the given scene object into the scene.
	/// </summary>
	/// <param name="sceneObject"></param>
	void AddSceneObject(std::unique_ptr<DTSceneObject> sceneObject);
	
	/// <summary>
	/// Sets up the mesh for visualizing the lights in the scene
	/// </summary>
	/// <param name="ro"></param>
	void SetUpLightMesh(std::shared_ptr<DTRenderObjectBase> ro);

	/// <summary>
	/// Add a light to the scene on the given position.
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	/// <param name="x"> X position of the new light </param>
	/// <param name="y"> Y position of the new light </param>
	/// <param name="z"> Z position of the new light </param>
	void AddLight(DTGraphics& gfx, float x, float y, float z);
};

