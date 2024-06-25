#pragma once

#include "DTWnds.h"
#include "DTException.h"
#include "Keyboard.h"
#include "Mouse.h"

class DTWindow
{
private:
	int width;
	int height;
	HWND hWnd;

#pragma region Nested Classes
	class Exception : public DTException
	{
	private:
		HRESULT hr;
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	};

	class DTWindowClass
	{
	private:
		static constexpr const wchar_t* windowClassName = L"Doom Task";
		static DTWindowClass wndClass;
		HINSTANCE hInstance;
		
		DTWindowClass() noexcept;
		~DTWindowClass() noexcept;
		DTWindowClass(const DTWindowClass&) = delete;
		DTWindowClass& operator=(const DTWindowClass&) = delete;
	public:
		static const wchar_t* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	};
#pragma endregion

#pragma region Windows Callback
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;	
#pragma endregion

public:
	Keyboard keyboard; // For keyboard input
	Mouse mouse; // For mouse input 

	DTWindow(int width, int height, const wchar_t* name) noexcept;
	~DTWindow();
	DTWindow(const DTWindow&) = delete;
	DTWindow& operator=(const DTWindow&) = delete;
};
