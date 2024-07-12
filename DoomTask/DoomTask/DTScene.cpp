#include "DTScene.h"

DTScene::DTScene(DTGraphics& gfx)
	:
	lightGroup(gfx)
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

void DTScene::SetUpLightMesh(std::shared_ptr<DTRenderObjectBase> ro)
{
	lightGroup.SetUpLightMeshes(ro);
}

void DTScene::AddLight(DTGraphics& gfx, float x, float y, float z)
{
	std::unique_ptr<LPointLight> light = std::make_unique<LPointLight>(gfx);
	light->SetPosition(DirectX::XMFLOAT3(x, y, z));

	lightGroup.AddLight(std::move(light));
}

