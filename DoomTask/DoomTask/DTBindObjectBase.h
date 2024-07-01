#pragma once

#include "DTGraphics.h"

#include <d3d11.h>
#include <string>

class DTGraphics;

class DTBindObjectBase
{
public:
public:
	virtual void Bind(DTGraphics& gfx) noexcept = 0;
	virtual ~DTBindObjectBase() = default;
protected:
	static ID3D11DeviceContext* GetContext(DTGraphics& gfx) noexcept;
	static ID3D11Device* GetDevice(DTGraphics& gfx) noexcept;
	static DxgiInfoManager& GetInfoManager(DTGraphics& gfx) noexcept;
};

