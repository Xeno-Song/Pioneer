#include "GuiManager.h"

GuiManager::GuiManager()
	:m_hWnd(NULL)
	,m_wndClass()
{
}

GuiManager::~GuiManager()
{
}

void GuiManager::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
}

void GuiManager::StartMainLoop()
{
}

LRESULT __stdcall GuiManager::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//MGetSystem()->GetWindowManager()->Destroy();
		return 0;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

HWND GuiManager::GetWindowHandle()
{
    return HWND();
}
