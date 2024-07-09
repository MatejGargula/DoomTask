#pragma once
#include "DTRenderObjectBase.h"
#include "RMesh.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

#include <vector>

/// <summary>
/// TODO: Add docs
/// </summary>
class RMultiMesh : public DTRenderObjectBase
{
private:
    std::vector<std::unique_ptr<RMesh>> meshes;
    std::unique_ptr<BVertexShader> VS; 
    std::unique_ptr<BPixelShader> PS;

public:
    RMultiMesh(DTGraphics& gfx, std::string path);
    void Render(DTGraphics& gfx) const noexcept override;
    void Render(DTGraphics& gfx, BTransform& transform) const noexcept override;
    void SetPS(DTGraphics& gfx, const std::wstring& path);
    void SetVS(DTGraphics& gfx, const std::wstring& path);
    
};

