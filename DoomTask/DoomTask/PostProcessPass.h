#pragma once
#include "DTBindObjectBase.h"
#include "RenderTargetTexture.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

class PostProcessPass
{
private:
	// TODO: add option for multiple textures 
	std::vector<std::shared_ptr<RenderTargetTexture>> sourceTexture;
	std::shared_ptr<RenderTargetTexture> targetTexture;

	BPixelShader pixelShader;
	BVertexShader vertexShader;

	std::vector<std::unique_ptr<DTBindObjectBase>> screenQuadBinds;
	UINT indicesCount;

	void createScreenQuad(DTGraphics& gfx);

public:
	PostProcessPass(DTGraphics& gfx,
					 const std::wstring& pixelShaderPath,
					 const std::wstring& vertexShaderPath,
					 std::vector<std::shared_ptr<RenderTargetTexture>> source,
					 std::shared_ptr<RenderTargetTexture> target = nullptr
	);
	void Render(DTGraphics& gfx) noexcept;
	
};

