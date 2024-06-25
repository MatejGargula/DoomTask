#include "DTWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{

	try 
	{
		DTWindow window(640, 400, L"Doom Task");

		// Message pump
		MSG msg;
		BOOL gResult;

		while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (window.keyboard.KeyIsPressed(VK_SPACE))
			{
				MessageBox(nullptr, L"SPACE DETECTED", L"Y THO", MB_OK | MB_ICONEXCLAMATION);
			}
		}

		if (gResult == -1)
			return -1;

		return msg.wParam;
	}
	catch (DTException e)
	{
		MessageBox(nullptr, reinterpret_cast<LPCWSTR>(e.what()), reinterpret_cast<LPCWSTR>(e.GetType()), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, reinterpret_cast<LPCWSTR>(e.what()), L"Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, L"No details available", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return -1;
}