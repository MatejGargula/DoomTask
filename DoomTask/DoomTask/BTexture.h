#pragma once

#include "DTBindObjectBase.h"
#include "DTGraphics.h"
#include "DTThrowMacros.h"
#include <string>

class BTexture : public DTBindObjectBase
{
private: 
	UINT width;
	UINT height;
	UINT channels;

	UINT slot;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
public:
	BTexture(DTGraphics& gfx, std::string path, UINT slotNum = 0, DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM);
	void Bind(DTGraphics& gfx) noexcept override;
};

