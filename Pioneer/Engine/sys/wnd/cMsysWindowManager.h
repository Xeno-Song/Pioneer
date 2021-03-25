#pragma once
#include <Windows.h>

class MsysWindowManager final
{
public:
	MsysWindowManager();
	~MsysWindowManager();

	bool	Create(HINSTANCE hInstance);
	bool	Destroy();
	static LRESULT __stdcall MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle() const;

	UINT GetScreenWidth() const;
	UINT GetScreenHeight() const;
	UINT GetWindowWidth() const;
	UINT GetWindowHeight() const;

private:
	WNDCLASSEXW	m_wndClass;
	HWND		m_hwnd;

	// Monitor size
	UINT		m_screenWidth;
	UINT		m_screenHeight;
	// Display window size - for window mode
	UINT		m_windowWidth;
	UINT		m_windowHeight;
};

