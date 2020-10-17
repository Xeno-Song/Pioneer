#pragma once

#ifndef __PN_DX11_CONTROLLER_H__
#define __PN_DX11_CONTROLLER_H__

#include "cDx11Device.h"

namespace pioEngine
{
	class cDx11Controller
	{
	public:
		cDx11Controller();
		cDx11Controller(const cDx11Controller&);
		~cDx11Controller();

		bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
		void Cleanup();
		bool Frame();

	private:
		bool Render();

	private:
		cDx11Device* m_device;
	};
}

#endif