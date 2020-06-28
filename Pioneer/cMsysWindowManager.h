#pragma once
#include <Windows.h>

class cMsysWindowManager
{
public:
	WNDCLASSEXW	m_wndClass;
	HWND		m_hwnd;

public:
	cMsysWindowManager();
	virtual ~cMsysWindowManager();

	bool	Create(HINSTANCE _hInstance);
	bool	Destroy();
	static LRESULT __stdcall MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle();
};

