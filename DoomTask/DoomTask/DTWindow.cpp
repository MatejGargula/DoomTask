#include "DTWindow.h"

#define DTWND_EXPCEPT (hr) DTWindow::Exception(__LINE__, __FILE__, hr)
#define DTWND_LAST_EXCEPT ( ) DTWindow::Exception(__LINE__, __FILE__, GetLastError())

DTWindow::DTWindowClass DTWindow::DTWindowClass::wndClass;

#pragma region Nested Classes

DTWindow::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	DTException(line, file),
	hr(hr)
{
}

const char* DTWindow::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "|ERROR CODE| -> " << GetErrorCode() << std::endl
		<< "|DESCRIPTION| -> " << GetErrorString() << std::endl
		<< GetOriginString();

	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* DTWindow::Exception::GetType() const noexcept
{
	return "DT Window Exception";
}

std::string DTWindow::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuff = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPWSTR>(&pMsgBuff),
		0,
		nullptr
	);

	if (nMsgLen == 0)
	{
		return "Unknown error code";
	}

	std::string errorString = pMsgBuff;
	LocalFree(pMsgBuff);

	return errorString;
}

HRESULT DTWindow::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string DTWindow::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}


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
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
		throw DTWindow::Exception(__LINE__, __FILE__, GetLastError());
	
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

	if (hWnd == nullptr)
		throw DTWindow::Exception(__LINE__, __FILE__, GetLastError());
	
	// Needs to be called. Otherwise the window will remain invisible.
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	gfx = std::make_unique<DTGraphics>(hWnd);
}

DTWindow::~DTWindow()
{
	DestroyWindow(hWnd);
}

std::optional<int> DTWindow::ProcessMessages()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return msg.wParam;
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

DTGraphics& DTWindow::Gfx()
{
	return *gfx;
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
	{
		PostQuitMessage(0); // For red x button in window corner 
		return 0;
	}
	case WM_KILLFOCUS: 
	{
		keyboard.ClearState();
		break;
	}
		
	case WM_KEYDOWN:
	{
		if (!(lParam & 0x40000000) || keyboard.AutorepeatIsEnabled()) 
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	}
	case WM_KEYUP:
	{
		keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	}
	case WM_CHAR:
	{
		keyboard.OnChar(static_cast<unsigned char>(wParam));
		break;
	}
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnMouseMove(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);

		break;
	}


	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

