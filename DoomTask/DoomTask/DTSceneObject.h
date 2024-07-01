#pragma once

#include "DTRenderObjectBase.h"
#include "BTransform.h"

class DTSceneObject
{
private:
	std::shared_ptr<DTRenderObjectBase> renderObject; // Mesh or primitive
	// TODO add material
public: 
	BTransform transform;

	DTSceneObject(DTGraphics& gfx);
	DTSceneObject(DTGraphics& gfx, std::shared_ptr<DTRenderObjectBase> ro);

	void Render(DTGraphics& gfx);
	void Update(float dt);
	void SetRenderObject(std::shared_ptr<DTRenderObjectBase> ro);
};

