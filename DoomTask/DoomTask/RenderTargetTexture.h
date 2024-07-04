#pragma once

#include "DTGraphics.h"
#include "DepthStencilTexture.h"

// TODO: add docs 
class RenderTargetTexture
{
	friend class DepthStencilTexture;
private: 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;

public:
	RenderTargetTexture(DTGraphics& gfx, UINT width, UINT height);
	void BindAsTexture(DTGraphics& gfx, UINT slot) const noexcept;
	void BindAsRenderTarget(DTGraphics& gfx) const noexcept;
	void BindAsRenderTarget(DTGraphics& gfx, const DepthStencilTexture& depthStencilTex) const noexcept;

protected:
	static ID3D11DeviceContext* GetContext(DTGraphics& gfx) noexcept;
	static ID3D11Device* GetDevice(DTGraphics& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(DTGraphics& gfx) noexcept;
};

