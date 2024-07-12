#pragma once

#include <optional>
#include <memory>
#include <vector>

#include "DTWnds.h"
#include "DTGraphics.h"
#include "DTException.h"
#include "Keyboard.h"
#include "Mouse.h"

/// <summary>
/// Main class for handling the manipulation with windows window. Holds the main windows handels.
/// </summary>
class DTWindow
{
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<DTGraphics> gfx;

	bool cursorEnabled = false;

	std::vector<char> rawBuffer;

	/// <summary>
	/// Hides the cursor
	/// </summary>
	void hideCursor();

	/// <summary>
	/// Shows the cursor
	/// </summary>
	void showCursor();

#pragma region Nested Classes
public:
	/// <summary>
	/// Base exception for the window exceptions.
	/// </summary>
	class Exception : public DTException
	{
		using DTException::DTException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};

	/// <summary>
	/// Standard exception for the window problems.
	/// </summary>
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

	/// <summary>
	/// Exception for detecting no graphics.
	/// </summary>
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};

private:

	/// <summary>
	/// Class for handling and creating the windwows class
	/// </summary>
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
	/// <summary>
	/// Sets up the main message pump.
	/// </summary>
	/// <returns> windows LRESULT </returns>
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	
	/// <summary>
	/// Forwads the windows messages to the HandleMessages class. 
	/// </summary>
	/// <returns> windows LRESULT </returns>
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
	void SetTitle(const std::string& title);

	/// <summary>
	/// Enables the cursor in the window.
	/// </summary>
	void EnableCursor();

	/// <summary>
	/// Disables the cursor in the window.
	/// </summary>
	void DisableCursor();

	/// <summary>
	/// Confines the mouse in the created window.
	/// </summary>
	void ConfineCursor();

	/// <summary>
	/// Frees the cursor from this window.
	/// </summary>
	void FreeCursor();
};
