#pragma once

#include "DTGraphics.h"
#include <d3d11.h>
#include <wrl.h>

// Forward declaration
class DTGraphics;

/// <summary>
/// Depth stencil or Z-buffer texture for rendering with depth culling.
/// </summary>
class DepthStencilTexture
{
	friend class GBuffer;
	friend class RenderTargetTexture;
private: 
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

public:
	DepthStencilTexture(DTGraphics& gfx, UINT width, UINT height);
	
	/// <summary>
	/// Binds the texture a depth texture target
	/// </summary>
	/// <param name="gfx"></param>
	void BindAsDepthBuffer(DTGraphics& gfx) const noexcept;
	
	/// <summary>
	/// Clears the texture for the next frame
	/// </summary>
	/// <param name="gfx"></param>
	void Clear(DTGraphics& gfx) const noexcept;

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

