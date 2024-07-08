#include "DTSceneObject.h"


DTSceneObject::DTSceneObject(DTGraphics& gfx)
	:
	transform(gfx)
{}

DTSceneObject::DTSceneObject(DTGraphics & gfx, std::shared_ptr<DTRenderObjectBase> ro, std::shared_ptr<BMaterial> mat)
	:
	transform(gfx),
	renderObject(ro),
	material(mat)
{}

void DTSceneObject::Render(DTGraphics& gfx)
{
	if (renderObject != nullptr && material != nullptr)
	{
		//material->Bind(gfx);
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

void DTSceneObject::SetMaterial(std::shared_ptr<BMaterial> mat)
{
	material = mat;
}


