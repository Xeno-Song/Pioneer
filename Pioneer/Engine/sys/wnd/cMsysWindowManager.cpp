#include "cMsysWindowManager.h"
#include "../../MEngine.h"

MsysWindowManager::MsysWindowManager()
{
}

MsysWindowManager::~MsysWindowManager()
{
}

bool MsysWindowManager::Create(HINSTANCE _hInstance)
{
	ZeroMemory(&m_wndClass, sizeof(m_wndClass));

	m_wndClass.cbSize = sizeof(WNDCLASSEXW);
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc = MainWndProc;
	m_wndClass.cbClsExtra = NULL;
	m_wndClass.cbWndExtra = NULL;
	m_wndClass.hInstance = _hInstance;
	m_wndClass.hIcon = NULL;
	m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wndClass.lpszClassName = L"Pioneer";

	RegisterClassExW(&m_wndClass);
	m_hwnd = CreateWindowExW(
		NULL,
		L"Pioneer",
		L"Pioneer",
		WS_POPUP | WS_VISIBLE,
		0,
		0,
		1920,
		1080,
		NULL,
		NULL,
		m_wndClass.hInstance,
		NULL
	);
	ShowWindow(m_hwnd, SW_SHOW);

	return false;
}

bool MsysWindowManager::Destroy()
{
	DestroyWindow(m_hwnd);
	UnregisterClassW(L"Pioneer", m_wndClass.hInstance);

	return false;
}

LRESULT MsysWindowManager::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//MGetSystem()->GetWindowManager()->Destroy();
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

HWND MsysWindowManager::GetWindowHandle()
{
	return m_hwnd;
}
