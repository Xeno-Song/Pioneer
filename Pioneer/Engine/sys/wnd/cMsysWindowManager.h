#pragma once
#include <Windows.h>

class MsysWindowManager
{
public:
	WNDCLASSEXW	m_wndClass;
	HWND		m_hwnd;

public:
	MsysWindowManager();
	virtual ~MsysWindowManager();

	bool	Create(HINSTANCE _hInstance);
	bool	Destroy();
	static LRESULT __stdcall MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle();
};

