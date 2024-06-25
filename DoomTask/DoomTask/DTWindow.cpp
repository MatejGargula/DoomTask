#include "DTWindow.h"

DTWindow::DTWindowClass DTWindow::DTWindowClass::wndClass;

#pragma region Nested Class 
DTWindow::DTWindowClass::DTWindowClass() noexcept
	:
	hInstance(GetModuleHandle(nullptr))
{
	// Register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

DTWindow::DTWindowClass::~DTWindowClass() noexcept
{
	UnregisterClass(windowClassName, GetInstance());
}

const wchar_t* DTWindow::DTWindowClass::GetName() noexcept
{
	return windowClassName;
}

HINSTANCE DTWindow::DTWindowClass::GetInstance() noexcept
{
	return wndClass.hInstance;
}
#pragma endregion

DTWindow::DTWindow(int w, int h, const wchar_t* name) noexcept
	:
	width(w),
	height(h)
{
	// Set Rect of the window
	RECT wr;
	wr.left = 100;
	wr.right = w + wr.left;
	wr.top = 100;
	wr.bottom = h + wr.top;

	// Adjust size of the window to match the given height and width
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		DTWindowClass::GetName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		DTWindowClass::GetInstance(),
		this
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

DTWindow::~DTWindow()
{
	DestroyWindow(hWnd);
}

LRESULT DTWindow::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		DTWindow* const pWnd = static_cast<DTWindow*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&DTWindow::HandleMessageThunk));
		// forward message to window instance handler
		return pWnd->HandleMessage(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT DTWindow::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window instance
	DTWindow* const pWnd = reinterpret_cast<DTWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMessage(hWnd, msg, wParam, lParam);
}

LRESULT DTWindow::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg) 
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

