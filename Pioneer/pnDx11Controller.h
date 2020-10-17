#pragma once

#ifndef __PN_DX11_CONTROLLER_H__
#define __PN_DX11_CONTROLLER_H__

#include <Windows.h>

namespace pioEngine
{
	class pnDx11Controller
	{
	public:
		pnDx11Controller();
		pnDx11Controller(const pnDx11Controller&);
		~pnDx11Controller();

		bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
		void Shutdown();
		void Frame();

	private:
		void Render();
	};
}

#endif