#pragma once

#include "DTRenderObjectBase.h"
#include "BTransform.h"
#include "BMaterial.h"

class DTSceneObject
{
private:
	std::shared_ptr<DTRenderObjectBase> renderObject; // Mesh or primitive
	std::shared_ptr<BMaterial> material; // Mesh or primitive

	// TODO add material
public: 
	BTransform transform;

	DTSceneObject(DTGraphics& gfx);
	DTSceneObject(DTGraphics& gfx, std::shared_ptr<DTRenderObjectBase> ro);
	DTSceneObject(DTGraphics& gfx, std::shared_ptr<DTRenderObjectBase> ro, std::shared_ptr<BMaterial> mat);

	void Render(DTGraphics& gfx);
	void Update(float dt);
	void SetRenderObject(std::shared_ptr<DTRenderObjectBase> ro);
	void SetMaterial(std::shared_ptr<BMaterial> mat);
};

