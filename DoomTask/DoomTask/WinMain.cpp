#include "DTWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	DTWindow window(640, 400, L"Doom Task");
	
	// Message pump
	MSG msg;
	BOOL gResult;

	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	if (gResult == -1)	
		return -1;
	
	return msg.wParam;
}