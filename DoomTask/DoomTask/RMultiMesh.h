#pragma once
#include "DTRenderObjectBase.h"
#include "RMesh.h"

#include <vector>

/// <summary>
/// TODO: Add docs
/// </summary>
class RMultiMesh : public DTRenderObjectBase
{
private:
    std::vector<std::unique_ptr<RMesh>> meshes;
public:
    RMultiMesh(DTGraphics& gfx, std::string path);
    void Render(DTGraphics& gfx) const noexcept override;
    void Render(DTGraphics& gfx, BTransform& transform) const noexcept override;
};

