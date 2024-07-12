#pragma once

#include "DTWnds.h"
#include "DTException.h"
#include "DXGIInfoManager.h"
#include "DTBindObjectBase.h"
#include "DTConfig.h"
#include "DTCamera.h"
#include "RenderTargetTexture.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

// Forward declaration
class DTCamera;
class DepthStencilTexture;
class RenderTargetTexture;

/// <summary>
/// Main graphical class of the application. Handles rendering, context and device creation. 
/// Modifies the graphical pipeline. 
/// </summary>
class DTGraphics
{
	friend class GBuffer;
	friend class PostProcessPass;
	friend class DepthStencilTexture;
	friend class RenderTargetTexture;
	friend class DTBindObjectBase;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain>  pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pWireRasterState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pSolidRasterState;

	DxgiInfoManager infoManager;

	bool postProcessingEnabled;

	std::shared_ptr<RenderTargetTexture> mainSceneRenderTexture;
	std::shared_ptr<DepthStencilTexture> mainDepthRenderTexture;
	
public:
	std::unique_ptr<DTCamera> camera;

	DTGraphics(HWND hWnd);
	DTGraphics(const DTGraphics&) = delete;
	DTGraphics& operator=(const DTGraphics&) = delete;

	/// <summary>
	/// Handles the end of the frame rendering.
	/// </summary>
	/// <returns></returns>
	void EndFrame();

	/// <summary>
	/// Clears the main backbuffer of the screen.
	/// </summary>
	void ClearBackBuffer(float r, float g, float b) noexcept;
	
	/// <summary>
	/// Sends a indexed draw call.
	/// </summary>
	void DrawIndexed(UINT count);
	
	/// <summary>
	/// Switches the render target from back buffer to a main renderTexture.
	/// </summary>
	void EnablePostProcessing();
	
	/// <summary>
	/// Switches the render target from back main render texture to the back buffer.
	/// </summary>
	void DisablePostProcessing();

	/// <summary>
	/// Returns a pointer to the main render texture if post processing is enabled.
	/// </summary>
	std::shared_ptr<RenderTargetTexture> GetMainRenderTexture();

	/// <summary>
	/// Getter for is processed enabled
	/// </summary>
	bool isPostprocessingEnabled();

	/// <summary>
	/// Sets the current topology for rendering meshes.
	/// </summary>
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY type);
	
	/// <summary>
	/// Enables wireframe mode 
	/// </summary>
	void EnableWireframe();

	/// <summary>
	/// Disables wireframe mode
	/// </summary>
	void DisableWireframe();

#pragma region Nested Classes

	/// <summary>
	/// Base class for graphical exceptions
	/// </summary>
	class Exception : public DTException
	{
		using DTException::DTException;
	};

	/// <summary>
	/// Standard graphical exception.
	/// </summary>
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

	/// <summary>
	/// Exception for catching the device removed exception.
	/// </summary>
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};

	/// <summary>
	/// Exception for reporting error in the pipeline set up
	/// </summary>
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

