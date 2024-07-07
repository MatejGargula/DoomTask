#pragma once

#include "DTGraphics.h"
#include <d3d11.h>
#include <wrl.h>

class DTGraphics;

class DepthStencilTexture
{
	friend class RenderTargetTexture;
private: 
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

public:
	DepthStencilTexture(DTGraphics& gfx, UINT width, UINT height);
	void BindAsDepthBuffer(DTGraphics& gfx) const noexcept;
	void Clear(DTGraphics& gfx) const noexcept;

protected:
	static ID3D11DeviceContext* GetContext(DTGraphics& gfx) noexcept;
	static ID3D11Device* GetDevice(DTGraphics& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(DTGraphics& gfx) noexcept;
};

