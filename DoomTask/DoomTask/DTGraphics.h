#pragma once

#include "DTWnds.h"

#include <d3d11.h>

//TODO: Add docs
class DTGraphics
{
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

public:
	DTGraphics(HWND hWnd);
	DTGraphics(const DTGraphics&) = delete;
	DTGraphics& operator=(const DTGraphics&) = delete;
	~DTGraphics();

	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;
};

