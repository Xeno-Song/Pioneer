#pragma once

#ifndef __M_C_SYSTEM_MANAGER_H__
#define __M_C_SYSTEM_MANAGER_H__

#define MGetSystem()		cMSystemManager::GetManager()

#include "Mdefines.h"

#include "cMd3dManager.h"

class cMSystemManager
{
protected:
	static cMSystemManager*		m_pStaticPtr;

private:
	cMd3dManager*	m_pD3dManager;

protected:
	cMSystemManager();
	virtual ~cMSystemManager();

	bool	InitEngine();
	void	StartEngine();

	void	Cleanup();

public:
	static cMSystemManager*	GetManager();

	cMd3dManager*	GetD3dManager();
};

#endif