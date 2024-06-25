#pragma once
#include "DTWnds.h"

class DTWindow
{
private:
#pragma region Nested Class
	class DTWindowClass
	{
	private:
		DTWindowClass() noexcept;
		~DTWindowClass() noexcept;
		DTWindowClass(const DTWindowClass&) = delete;
		DTWindowClass& operator=(const DTWindowClass&) = delete;
		static constexpr const wchar_t* windowClassName = L"Doom Task";
		static DTWindowClass wndClass;
		HINSTANCE hInstance;
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
	
	int width;
	int height;
	HWND hWnd;
public:
	DTWindow(int width, int height, const wchar_t* name) noexcept;
	~DTWindow();
	DTWindow(const DTWindow&) = delete;
	DTWindow& operator=(const DTWindow&) = delete;
};

