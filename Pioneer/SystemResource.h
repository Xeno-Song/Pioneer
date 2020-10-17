#pragma once

#ifndef __SYSTEM_RESOURCE_H__
#define __SYSTEM_RESOURCE_H__

// to exclude unused api headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "pnDx11Controller.h"

namespace pioEngine
{
	class cSystemResource
	{
	public:
		cSystemResource();
		cSystemResource(const cSystemResource&);
		~cSystemResource();

		bool Initialize();
		void Shutdown();
		void Run();

		static LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT, WPARAM wParam, LPARAM lParam);

	private:
		bool Frame();
		void InitializeWindow(LPCWSTR applicationName, int& screenWidth, int& screenHeight, bool fullScreen);
		void ShutdownWindows();

	private:
		LPCWSTR		m_applicationName;
		HINSTANCE	m_hinstance;
		HWND		m_hwnd;

		pnDx11Controller* m_dx11Control;
	};
}

#endif