#include "GuiManager.h"

GuiManager::GuiManager()
	:m_hInstance(nullptr)
	, m_wndClass()
	, m_hWnd(nullptr)
	, m_hMenu(nullptr)
{
}

GuiManager::GuiManager(GuiManager& target)
	:m_hInstance(nullptr)
	, m_wndClass()
	, m_hWnd(nullptr)
	, m_hMenu(nullptr)
{
	m_wndClass = target.m_wndClass;
	m_hWnd = target.m_hWnd;
}

GuiManager::~GuiManager()
{
	Destroy();
}

void GuiManager::Initialize(const HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;
	ZeroMemory(&m_wndClass, sizeof(m_wndClass));

	m_hMenu = CreateMenu();
	AppendMenuW(m_hMenu, MF_STRING, 1, L"File");
	
	m_wndClass.cbSize = sizeof(WNDCLASSEXW);
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc = MainWndProc;
	m_wndClass.cbClsExtra = NULL;
	m_wndClass.cbWndExtra = NULL;
	m_wndClass.hInstance = hInstance;
	m_wndClass.hIcon = nullptr;
	m_wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_wndClass.lpszClassName = L"MEngine Resource Modifier";

	RegisterClassExW(&m_wndClass);
	m_hWnd = CreateWindowExW(
		NULL,
		L"MEngine Resource Modifier",
		L"MEngine Resource Modifier",
		WS_OVERLAPPEDWINDOW,
		0, 0, 1920, 1080,
		nullptr, nullptr,
		m_wndClass.hInstance,
		nullptr
	);
	ShowWindow(m_hWnd, SW_SHOW);
}

void GuiManager::Destroy() const
{
	DestroyWindow(m_hWnd);
	UnregisterClassW(L"MEngine Resource Modifier", m_wndClass.hInstance);
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

HWND GuiManager::GetWindowHandle() const
{
    return m_hWnd;
}
