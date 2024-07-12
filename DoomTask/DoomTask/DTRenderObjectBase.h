#pragma once
#include "DTGraphics.h"
#include "DTBindObjectBase.h"
#include "BIndexBuffer.h"
#include "BTransform.h"

#include <DirectXMath.h>
#include <vector>

// Forward declaration
class DTBindObjectBase;

/// <summary>
/// Base class for all renderable objects.
/// </summary>
class DTRenderObjectBase
{
public:
	DTRenderObjectBase() = default;
	DTRenderObjectBase(const DTRenderObjectBase&) = delete;
	
	virtual ~DTRenderObjectBase() = default;

	/// <summary>
	/// Virtual method that renders the given object onto the screen.
	/// </summary>
	/// <param name="gfx"></param>
	virtual void Render(DTGraphics& gfx) const noexcept;
	
	/// <summary>
	/// Virtual method for disabling the default object shaders.
	/// </summary>
	virtual void DisableShaders();

	/// <summary>
	/// Virtual method for enabling the default object shaders.
	/// </summary>
	virtual void EnableShaders();

	/// <summary>
	/// Add a bind object into the vector of bindable objects.
	/// </summary>
	/// <param name="bind"> Object to be bound in the pipeline </param>
	void AddBind(std::unique_ptr<DTBindObjectBase> bind) noexcept;

	/// <summary>
	/// Add the index buffer of the object
	/// </summary>
	/// <param name="ibuf"> index buffer </param>
	void AddIndexBuffer(std::unique_ptr<class BIndexBuffer> ibuf) noexcept;
private:
	const BIndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<DTBindObjectBase>> binds;

protected:
	bool shadersEnabled = false;
};