#pragma once
#include "DTGraphics.h"
#include "DTBindObjectBase.h"
#include "BIndexBuffer.h"
#include "BTransform.h"

#include <DirectXMath.h>
#include <vector>

class DTBindObjectBase;

class DTRenderObjectBase
{
public:
	DTRenderObjectBase() = default;
	DTRenderObjectBase(const DTRenderObjectBase&) = delete;
	
	virtual ~DTRenderObjectBase() = default;
	virtual void Render(DTGraphics& gfx) const noexcept;
	virtual void DisableShaders();
	virtual void EnableShaders();

	void AddBind(std::unique_ptr<DTBindObjectBase> bind) noexcept;
	void AddIndexBuffer(std::unique_ptr<class BIndexBuffer> ibuf) noexcept;
private:
	const BIndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<DTBindObjectBase>> binds;

protected:
	bool shadersEnabled = false;
};