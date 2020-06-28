#pragma once

#ifndef __M_C_SYSTEM_MANAGER_H__
#define __M_C_SYSTEM_MANAGER_H__

#define MGetSystem()		cMSystemManager::GetManager()

#include "Mdefines.h"

#include "cMsysWindowManager.h"
#include "cMd3dManager.h"

class cMSystemManager
{
protected:
	static cMSystemManager*		m_pStaticPtr;

private:
	cMsysWindowManager*	m_winManager;
	cMd3dManager*		m_pD3dManager;

public:
	cMSystemManager();
	virtual ~cMSystemManager();

	bool	InitEngine(HINSTANCE _hInstance);
	void	StartEngine();
	void	Cleanup();

public:
	static cMSystemManager*	GetManager();

	cMd3dManager*		GetD3dManager();
	cMsysWindowManager*	GetWindowManager();
};

#endif