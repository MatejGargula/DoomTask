#pragma once

#include "DTSceneObject.h"
#include "DTGraphics.h"
#include <vector>

class DTScene
{
	friend class DTRenderQueue;
private:
	std::vector<std::unique_ptr<DTSceneObject>> sceneObjects;

	std::vector<unsigned int> defaultObjects;
	std::vector<unsigned int> tessalatedObjects;
public: 
	DTScene();

	//std::vector<std::unique_ptr<DTSceneObject>>& GetSceneObjects();
	std::vector<unsigned int>& GetDefaultObjects();
	std::vector<unsigned int>& GetTessalatedObjects();

	void AddSceneObject(std::unique_ptr<DTSceneObject> sceneObject);
	
};

