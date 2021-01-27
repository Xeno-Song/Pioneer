#include "cInputManager.h"

namespace pioEngine
{
	cInputManager::cInputManager()
	{
		for (int i = 0; i < 256; i++)
			m_keyStateMemory[i] = false;
	}

	cInputManager::cInputManager(cInputManager & origin)
	{
		for (int i = 0; i < 256; i++)
		{
			m_keyStateMemory[i] = origin.GetKeyState(i);
		}

		m_cursorPosition = origin.GetCursorPosition();
	}

	cInputManager::~cInputManager()
	{
	}

	void cInputManager::SetKeyState(unsigned char key, bool state)
	{
		m_keyStateMemory[key] = state;
	}

	bool cInputManager::GetKeyState(unsigned char key)
	{
		return m_keyStateMemory[key];
	}

	void cInputManager::SetCursorPosition(POINT cursor)
	{
		m_cursorPosition = cursor;
	}

	POINT cInputManager::GetCursorPosition()
	{
		return m_cursorPosition;
	}

	bool cInputManager::GetKeyStateAsync(unsigned char key)
	{
		bool result;
		result = GetAsyncKeyState(key);

			return false;
	}

	POINT cInputManager::GetCursorPositionAsync()
	{
		POINT cursor;
		
		if (GetCursorPos(&cursor) == false)
			return POINT{ 0, 0 };

		return cursor;
	}

}