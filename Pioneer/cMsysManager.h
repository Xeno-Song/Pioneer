#pragma once

#ifndef __M_C_SYSTEM_MANAGER_H__
#define __M_C_SYSTEM_MANAGER_H__

#define MGetSystem()		cMsysManager::GetManager()

#include "Mdefines.h"

#include "cMsysWindowManager.h"
#include "cMsysThreadManager.h"
#include "cMseqBase.h"
#include "cMd3dManager.h"
#include "cMutilTimerManager.h"

class cMsysManager
{
protected:
	static cMsysManager*		m_pStaticPtr;

private:
	cMsysWindowManager*	m_winManager;
	cMd3dManager*		m_d3dManager;
	cMsysThreadManager*	m_threadManager;
	cMutilTimerManager*	m_timerManager;
		
	cMseqBase*			m_pCurrSeq;

public:
	cMsysManager();
	virtual ~cMsysManager();

	bool	InitEngine(HINSTANCE _hInstance);
	void	StartEngine(cMseqBase*	_initSeq);
	void	Cleanup();

public:
	static cMsysManager*	GetManager();

	void	ChangeSequence(cMseqBase* _seq);

	cMd3dManager*		GetD3dManager();
	cMsysWindowManager*	GetWindowManager();
	cMsysThreadManager*	GetThreadManager();
	cMutilTimerManager*	GetTimerManager();
};

#endif