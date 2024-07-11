#include "DTScene.h"

DTScene::DTScene()
{
}

std::vector<unsigned int>& DTScene::GetDefaultObjects()
{
	return defaultObjects;
}

std::vector<unsigned int>& DTScene::GetTessalatedObjects()
{
	return tessalatedObjects;
}

void DTScene::AddSceneObject(std::unique_ptr<DTSceneObject> sceneObject)
{
	switch (sceneObject->type)
	{
		case DTSceneObject::Type::DEFAULT :
		{
			defaultObjects.push_back(sceneObjects.size());
			break;
		}
		case DTSceneObject::Type::TESSALATED :
		{
			tessalatedObjects.push_back(sceneObjects.size());
			break;
		}
	}

	sceneObjects.push_back(std::move(sceneObject));
}


