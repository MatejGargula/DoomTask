#include "DTSceneObject.h"


DTSceneObject::DTSceneObject(DTGraphics& gfx)
	:
	transform(gfx)
{}

DTSceneObject::DTSceneObject(DTGraphics & gfx, std::shared_ptr<DTRenderObjectBase> ro)
	:
	transform(gfx),
	renderObject(ro)
{}

void DTSceneObject::Render(DTGraphics& gfx)
{
	if (renderObject != nullptr)
	{
		renderObject->Render(gfx, transform);
	}
}

void DTSceneObject::Update(float dt)
{

}

void DTSceneObject::SetRenderObject(std::shared_ptr<DTRenderObjectBase> ro)
{
	renderObject = ro;
}


