#pragma once

#include <optional>
#include <memory>

#include "DTWnds.h"
#include "DTGraphics.h"
#include "DTException.h"
#include "Keyboard.h"
#include "Mouse.h"

//TODO: Add docs
class DTWindow
{
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<DTGraphics> gfx;

#pragma region Nested Classes
public:
	class Exception : public DTException
	{
		using DTException::DTException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};

private:
	class DTWindowClass
	{
	private:
		static constexpr const char* windowClassName = "Doom Task";
		static DTWindowClass wndClass;
		HINSTANCE hInstance;
		
		DTWindowClass() noexcept;
		~DTWindowClass() noexcept;
		DTWindowClass(const DTWindowClass&) = delete;
		DTWindowClass& operator=(const DTWindowClass&) = delete;
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	};
#pragma endregion

#pragma region Windows Callback
private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;	
#pragma endregion

public:
	Keyboard keyboard; // For keyboard input
	Mouse mouse; // For mouse input 

	DTWindow(int width, int height, const char* name) noexcept;
	~DTWindow();
	DTWindow(const DTWindow&) = delete;
	DTWindow& operator=(const DTWindow&) = delete;
	static std::optional<int> ProcessMessages();
	DTGraphics& Gfx();
};
