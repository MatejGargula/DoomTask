#pragma once

#include "DTWnds.h"
#include "DTException.h"
#include "DXGIInfoManager.h"
#include "DTBindObjectBase.h"
#include "DTConfig.h"
#include "DTCamera.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>


//TODO: Add docs
class DTGraphics
{
	friend class DTBindObjectBase;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain>  pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

	DxgiInfoManager infoManager;

	DirectX::XMMATRIX projection;

public:
	std::unique_ptr<DTCamera> camera;

	DTGraphics(HWND hWnd);
	DTGraphics(const DTGraphics&) = delete;
	DTGraphics& operator=(const DTGraphics&) = delete;

	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;
	void DrawIndexed(UINT count) noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	
	void DrawTestTriangle(float angle, float x, float z);

#pragma region Nested Classes

	class Exception : public DTException
	{
		using DTException::DTException;
	};

	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};

	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};

	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};

#pragma endregion
};

