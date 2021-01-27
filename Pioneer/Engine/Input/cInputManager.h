#pragma once

#ifndef __C_INPUT_MANAGER_H__
#define __C_INPUT_MANAGER_H__

#include <Windows.h>

namespace pioEngine
{
	class cInputManager
	{
	public:
		cInputManager();
		cInputManager(cInputManager&);

		virtual ~cInputManager();

	public:
		void SetKeyState(unsigned char key, bool state);
		bool GetKeyState(unsigned char key);

		void SetCursorPosition(POINT cursor);
		POINT GetCursorPosition();
		
		bool GetKeyStateAsync(unsigned char key);
		POINT GetCursorPositionAsync();

	private:
		bool m_keyStateMemory[256] = { false };
		POINT m_cursorPosition;
	};
}

#endif	