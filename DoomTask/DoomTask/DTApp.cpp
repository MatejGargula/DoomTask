#include "DTApp.h"

DTApp::DTApp()
	:
	window(800,600,L"DoomTask")
{}

int DTApp::Run()
{
	while (true)
	{
		if (const auto retCode = DTWindow::ProcessMessages())
			return *retCode;

		RunFrame();
	}

	// Message pump
	MSG msg;
	BOOL gResult;

	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		RunFrame();
	}

	if (gResult == -1)
		return -1;

	return msg.wParam;
}

void DTApp::RunFrame()
{
	const float c = std::sin(timer.Peek() / 2.0f + 0.5f); // Testing Delete later
	window.Gfx().ClearBuffer(1.0f, c, 1.0f);

	window.Gfx().EndFrame();
}