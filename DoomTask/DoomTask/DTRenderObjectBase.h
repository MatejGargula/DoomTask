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
	void Render(DTGraphics& gfx) const noexcept;
	void Render(DTGraphics& gfx, BTransform &transform) const noexcept;
	//virtual void Update(float dt) noexcept = 0; // TODO: Maybe delete? 
	void AddBind(std::unique_ptr<DTBindObjectBase> bind) noexcept;
	void AddIndexBuffer(std::unique_ptr<class BIndexBuffer> ibuf) noexcept;
	virtual ~DTRenderObjectBase() = default;
private:
	const BIndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<DTBindObjectBase>> binds;
};