#pragma once

#include "RenderTargetTexture.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

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
	void BindAsRenderTarget(DTGraphics& gfx);
	void BindAsTextures(DTGraphics& gfx, UINT startSlot);
	void BindCollectionShaders(DTGraphics& gfx);
	void Clear(DTGraphics& gfx);

	std::vector<std::shared_ptr<RenderTargetTexture>> GetRenderTextures();
	
};

