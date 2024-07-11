#include "DTRenderObjectBase.h"

#include <cassert>
#include <typeinfo>

void DTRenderObjectBase::Render(DTGraphics& gfx) const noexcept
{
	for (auto& b : binds)
		b->Bind(gfx);

	gfx.DrawIndexed(pIndexBuffer->GetCount());

}

void DTRenderObjectBase::AddBind(std::unique_ptr<DTBindObjectBase> bind) noexcept
{
	assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(BIndexBuffer));
	binds.push_back(std::move(bind));
}

void DTRenderObjectBase::AddIndexBuffer(std::unique_ptr<class BIndexBuffer> ibuf) noexcept
{
	assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
	pIndexBuffer = ibuf.get();
	this->binds.push_back(std::move(ibuf));
}

void DTRenderObjectBase::DisableShaders()
{
	shadersEnabled = false;
}

void DTRenderObjectBase::EnableShaders()
{
	shadersEnabled = false;
}
