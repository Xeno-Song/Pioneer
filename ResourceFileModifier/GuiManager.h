#pragma once

#ifndef __C_GUI_MANAGER_H__
#define __C_GUI_MANAGER_H__

#include <Windows.h>

class GuiManager
{
public:
	GuiManager();
	virtual ~GuiManager();

public:
	void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
	void StartMainLoop();


	static LRESULT __stdcall MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle();

private:
	WNDCLASSEXW	m_wndClass;
	HWND		m_hWnd;
};

#endif