#pragma once
#include "DTBindObjectBase.h"
#include "RenderTargetTexture.h"
#include "BPixelShader.h"
#include "BVertexShader.h"

/// <summary>
/// Class for storing a single post-process.
/// </summary>
class PostProcessPass
{
private:
	std::vector<std::shared_ptr<RenderTargetTexture>> sourceTexture;
	std::shared_ptr<RenderTargetTexture> targetTexture;

	BPixelShader pixelShader;
	BVertexShader vertexShader;

	std::vector<std::unique_ptr<DTBindObjectBase>> screenQuadBinds;
	UINT indicesCount;

	/// <summary>
	/// Creates the screen quad for full screen post-processing.
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	void createScreenQuad(DTGraphics& gfx);

public:
	PostProcessPass(DTGraphics& gfx,
					 const std::wstring& pixelShaderPath,
					 const std::wstring& vertexShaderPath,
					 std::vector<std::shared_ptr<RenderTargetTexture>> source,
					 std::shared_ptr<RenderTargetTexture> target = nullptr
	);
	
	PostProcessPass(DTGraphics& gfx,
		const std::wstring& pixelShaderPath,
		const std::wstring& vertexShaderPath,
		std::shared_ptr<RenderTargetTexture> source,
		std::shared_ptr<RenderTargetTexture> target = nullptr
	);

	/// <summary>
	/// Processes the post-process from the given source texture and outputs it into the given render target.
	/// </summary>
	/// <param name="gfx"></param>
	void Render(DTGraphics& gfx) noexcept;

	/// <summary>
	/// Returns the render target texture of this post-process.
	/// </summary>
	/// <returns> render target texture </returns>
	std::shared_ptr<RenderTargetTexture> GetTargetTexture();

	/// <summary>
	/// Sets the current render target of this post-process.
	/// </summary>
	/// <param name="targetTex"></param>
	void SetTargetTexture(std::shared_ptr<RenderTargetTexture> targetTex);
};

