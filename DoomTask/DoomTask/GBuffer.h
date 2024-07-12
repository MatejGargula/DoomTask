#pragma once

#include "RenderTargetTexture.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

/// <summary>
/// Class for storing the main G-buffer textures required for deferred rendering
/// </summary>
class GBuffer
{
private:
	enum
	{
		DIFFUSE_TEX = 0,
		POSITION_TEX,
		NORMAL_TEX,
		SPECULAR_TEX,
		N_GTEXTURES
	};

	std::vector<std::shared_ptr<RenderTargetTexture>> gTextures;
	DepthStencilTexture depthRenderTexture;

	BVertexShader VS;
	BPixelShader PS;

public:
	GBuffer(DTGraphics& gfx);
	
	/// <summary>
	/// Binds the whole G-buffer as a render target
	/// </summary>
	void BindAsRenderTarget(DTGraphics& gfx);

	/// <summary>
	/// Binds the g-buffer as individual textures
	/// </summary>
	void BindAsTextures(DTGraphics& gfx, UINT startSlot);
	
	/// <summary>
	/// Binds the shaders required for collection of data/textures needed for deferred rendering.
	/// </summary>
	void BindCollectionShaders(DTGraphics& gfx);

	/// <summary>
	/// Clears the G-buffer textures.
	/// </summary>
	void Clear(DTGraphics& gfx);

	/// <summary>
	/// returns the vector containing all of the G-buffer textures.
	/// </summary>
	std::vector<std::shared_ptr<RenderTargetTexture>>& GetRenderTextures();
	
};

