#include "cMsysWindowManager.h"
#include "../../MEngine.h"

MsysWindowManager::MsysWindowManager()
	:m_wndClass()
	, m_hwnd(nullptr)
	, m_screenWidth(0)
	, m_screenHeight(0)
	, m_windowWidth(0)
	, m_windowHeight(0)
{
}

MsysWindowManager::~MsysWindowManager()
{
	Destroy();
}

bool MsysWindowManager::Create(HINSTANCE hInstance)
{
	ZeroMemory(&m_wndClass, sizeof(m_wndClass));

	m_wndClass.cbSize = sizeof(WNDCLASSEXW);
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc = MainWndProc;
	m_wndClass.cbClsExtra = NULL;
	m_wndClass.cbWndExtra = NULL;
	m_wndClass.hInstance = hInstance;
	m_wndClass.hIcon = NULL;
	m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wndClass.lpszClassName = L"Pioneer";

	m_screenHeight = GetSystemMetrics(SM_CXSCREEN);
	m_screenWidth = GetSystemMetrics(SM_CYSCREEN);

	RegisterClassExW(&m_wndClass);
	m_hwnd = CreateWindowExW(
		NULL,
		L"Pioneer",
		L"Pioneer",
		WS_POPUP | WS_VISIBLE,
		0,
		0,
		m_screenWidth,
		m_screenHeight,
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

HWND MsysWindowManager::GetWindowHandle() const
{
	return m_hwnd;
}

UINT MsysWindowManager::GetScreenWidth() const
{
	return m_screenWidth;
}

UINT MsysWindowManager::GetScreenHeight() const
{
	return m_screenHeight;
}

UINT MsysWindowManager::GetWindowWidth() const
{
	return m_windowWidth;
}

UINT MsysWindowManager::GetWindowHeight() const
{
	return m_windowHeight;
}
