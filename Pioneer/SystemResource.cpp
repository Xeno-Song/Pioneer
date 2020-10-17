#include "SystemResource.h"

namespace pioEngine
{

	cSystemResource::cSystemResource()
	{
		m_dx11Control = nullptr;
	}

	cSystemResource::cSystemResource(const cSystemResource&)
	{
	}

	cSystemResource::~cSystemResource()
	{
	}

	bool cSystemResource::Initialize()
	{
		int screenWidth, screenHeight;
		bool result;

		screenWidth = screenHeight = 0;
		InitializeWindow(L"TEST APPLICATION", screenWidth, screenHeight, false);

		m_dx11Control = new cDx11Controller();
		result = m_dx11Control->Initialize(screenWidth, screenHeight, m_hwnd);
		if (!result) { return false; }

		return false;
	}

	void cSystemResource::Cleanup()
	{
		if (m_dx11Control != nullptr)
		{
			m_dx11Control->Cleanup();
			delete m_dx11Control;
			m_dx11Control = nullptr;
		}
	}

	void cSystemResource::Run()
	{
		m_dx11Control->Frame();
	}

	LRESULT cSystemResource::WinMsgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		}

		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}

	bool cSystemResource::Frame()
	{
		return false;
	}

	void cSystemResource::InitializeWindow(LPCWSTR applicationName, int& screenWidth, int& screenHeight, bool fullScreen)
	{
		WNDCLASSEX wc;
		DEVMODE devModeSettings;
		int posX, posY;

		m_hinstance = GetModuleHandle(NULL);
		m_applicationName = applicationName;

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WinMsgHandler;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);
		RegisterClassExW(&wc);

		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		if (fullScreen)
		{
			memset(&devModeSettings, 0, sizeof(devModeSettings));
			devModeSettings.dmSize = sizeof(devModeSettings);
			devModeSettings.dmPelsWidth = (unsigned long)screenWidth;
			devModeSettings.dmPelsHeight = (unsigned long)screenHeight;
			devModeSettings.dmBitsPerPel = 32;
			devModeSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&devModeSettings, CDS_FULLSCREEN);
			posX = posY = 0;
		}
		else
		{
			screenWidth = 800;
			screenHeight = 600;

			posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		}

		m_hwnd = CreateWindowExW(
			WS_EX_APPWINDOW,
			m_applicationName,
			m_applicationName,
			WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE,
			posX,
			posY,
			screenWidth,
			screenHeight,
			NULL,
			NULL,
			m_hinstance,
			NULL);
		ShowWindow(m_hwnd, SW_SHOW);

		SetForegroundWindow(m_hwnd);
		SetFocus(m_hwnd);
		ShowCursor(false);

		return;
	}

	void cSystemResource::ShutdownWindows()
	{
		ShowCursor(true);

		ChangeDisplaySettings(NULL, 0);
		DestroyWindow(m_hwnd);
		m_hwnd = NULL;

		UnregisterClassW(m_applicationName, m_hinstance);

		return;
	}

}