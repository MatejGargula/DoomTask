#include "DTWindow.h"
#include "DTApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{

	try 
	{
		DTApp app;
		return app.Run();
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