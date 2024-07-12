#pragma once
#include "DTRenderObjectBase.h"
#include "RMesh.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

#include <vector>

/// <summary>
/// Class for storing multiple meshes in one class. Can render and load all meshed stored in one file.
/// </summary>
class RMultiMesh : public DTRenderObjectBase
{
private:
    std::vector<std::unique_ptr<RMesh>> meshes;
    std::unique_ptr<BVertexShader> VS; 
    std::unique_ptr<BPixelShader> PS;

public:
    RMultiMesh(DTGraphics& gfx, std::string path);
    
    /// <summary>
    /// Renders all of the loaded meshes
    /// </summary>
    /// <param name="gfx"> main graphics class </param>
    void Render(DTGraphics& gfx) const noexcept override;
    
    /// <summary>
    /// Sets the default shader of the meshes.
    /// </summary>
    /// <param name="gfx"> Main graphics class </param>
    /// <param name="path"> path to the compiled shader (.cso file) </param>
    void SetPS(DTGraphics& gfx, const std::wstring& path);
    
    /// <summary>
    /// Sets the default shader of the meshes.
    /// </summary>
    /// <param name="gfx"> Main graphics class </param>
    /// <param name="path"> path to the compiled shader (.cso file) </param>
    void SetVS(DTGraphics& gfx, const std::wstring& path);
    
};

