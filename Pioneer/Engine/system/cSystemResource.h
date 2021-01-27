#pragma once

#ifndef __C_SYSTEM_RESOURCE_H__
#define __C_SYSTEM_RESOURCE_H__

// to exclude unused api headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../dx/cDx11Controller.h"
#include "../Input/cInputManager.h"

namespace pioEngine
{
	class cSystemResource
	{
	public:
		cSystemResource();
		cSystemResource(const cSystemResource&);
		~cSystemResource();

		bool Initialize();
		void Cleanup();
		void Run();

		static LRESULT CALLBACK WinMsgHandler(HWND hwnd, UINT, WPARAM wParam, LPARAM lParam);

	private:
		bool Frame();
		void InitializeWindow(LPCWSTR applicationName, int& screenWidth, int& screenHeight, bool fullScreen);
		void ShutdownWindows();

	public:
		cDx11Controller* GetDx11Controller();
		cInputManager* GetInputManager();

	private:
		LPCWSTR		m_applicationName;
		HINSTANCE	m_hinstance;
		HWND		m_hwnd;

		cDx11Controller* m_dx11Control;
		cInputManager* m_inputManager;


	// WinProc Evnet Handler
	private:
		//static void(pioEngine::cInputManager::* KeyStateChangeEventHandler)(unsigned char key, bool pushed);
		//static void(pioEngine::cInputManager::*		CursorMoveEventHandler)(POINT cursor);
	};

	static cSystemResource* systemResource;
}

#endif