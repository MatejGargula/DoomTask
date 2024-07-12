#pragma once

#include "DTRenderObjectBase.h"
#include "BTransform.h"
#include "BMaterial.h"

/// <summary>
/// Class for storing the data of an object in the scene.
/// Holds the render objects (Mesh to render) and Transform for information about the position and rotation of the object.
/// </summary>
class DTSceneObject
{
private:
	std::shared_ptr<DTRenderObjectBase> renderObject; // Mesh or primitive
	
public: 

	enum Type
	{
		DEFAULT,
		TESSALATED
	};

	Type type = DEFAULT;
	BTransform transform;

	DTSceneObject(DTGraphics& gfx);
	DTSceneObject(DTGraphics& gfx, std::shared_ptr<DTRenderObjectBase> ro);

	/// <summary>
	/// Renders the render object onto the screen with the given transform.
	/// </summary>
	/// <param name="gfx"></param>
	void Render(DTGraphics& gfx);

	/// <summary>
	/// Virtual method for updating the scene object
	/// </summary>
	/// <param name="dt"></param>
	virtual void Update(float dt);
	
	/// <summary>
	/// Sets the mesh to be rendered with this scene object
	/// </summary>
	/// <param name="ro"></param>
	void SetRenderObject(std::shared_ptr<DTRenderObjectBase> ro);
};

