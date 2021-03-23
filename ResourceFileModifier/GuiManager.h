#pragma once

#ifndef __C_GUI_MANAGER_H__
#define __C_GUI_MANAGER_H__

#include <Windows.h>

class GuiManager
{
public:
	GuiManager();
	GuiManager(GuiManager&);
	~GuiManager();

	void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
	void Destroy() const;
	void StartMainLoop();

	static LRESULT __stdcall MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetWindowHandle() const;

private:
	HINSTANCE	m_hInstance;
	WNDCLASSEXW	m_wndClass;
	HWND		m_hWnd;

	HMENU		m_hMenu;
};

#endif