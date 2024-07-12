#pragma once

#include "DTGraphics.h"
#include "DepthStencilTexture.h"

// Forward declaration
class DTGraphics;
class DepthStencilTexture;

/// <summary>
/// Class for storing and binding a render texture as texture or as a render target.
/// </summary>
class RenderTargetTexture
{
	friend class GBuffer;
	friend class DepthStencilTexture;
private: 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;

public:
	RenderTargetTexture(DTGraphics& gfx, UINT width, UINT height);

	/// <summary>
	/// Binds the render texture to the pipeline as a texture 
	/// </summary>
	/// <param name="gfx"> Main graphics class </param>
	/// <param name="slot"> the slot of the texture in the pipeline </param>
	void BindAsTexture(DTGraphics& gfx, UINT slot) const noexcept;

	/// <summary>
	/// Binds the render texture as a render target in the pipeline without depth stencil buffer.
	/// </summary>
	/// <param name="gfx">Main graphics class</param>
	void BindAsRenderTarget(DTGraphics& gfx) const noexcept;

	/// <summary>
	/// Binds the render texture as a render target in the pipeline with depth stencil buffer.
	/// </summary>
	/// <param name="gfx">Main graphics class</param>
	/// <param name="depthStencilTex">depth stencil texture view (can be obtained from a DepthStencilTexture)</param>
	void BindAsRenderTarget(DTGraphics& gfx, const DepthStencilTexture& depthStencilTex) const noexcept;
	
	/// <summary>
	/// Clears the texture for the next frame.
	/// </summary>
	/// <param name="gfx"> Main render texture </param>
	/// <param name="color"> Color to clear the texture </param>
	void ClearRenderTarget(DTGraphics& gfx, const float color[3]) noexcept;

protected:
	/// <summary>
	/// Returns the context of the device context
	/// </summary>
	/// <param name="gfx"> The main graphical component </param>
	/// <returns></returns>
	static ID3D11DeviceContext* GetContext(DTGraphics& gfx) noexcept;

	/// <summary>
	/// Returns the graphics device
	/// </summary>
	/// <param name="gfx">The main graphical component</param>
	/// <returns></returns>
	static ID3D11Device* GetDevice(DTGraphics& gfx) noexcept;

	/// <summary>
	/// Returns the info manager. Needed for reporting exceptions.
	/// </summary>
	/// <param name="gfx"></param>
	/// <returns></returns>
	static DxgiInfoManager& GetInfoManager(DTGraphics& gfx) noexcept;
};

