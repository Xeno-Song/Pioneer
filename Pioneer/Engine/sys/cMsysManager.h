#pragma once

#ifndef __M_C_SYSTEM_MANAGER_H__
#define __M_C_SYSTEM_MANAGER_H__

#define MGetSystem()		MsysManager::GetManager()

#include "../Mdefines.h"

#include "../sys/wnd/cMsysWindowManager.h"
#include "../sys/thd/cMsysThreadManager.h"
#include "../seq/cMseqBase.h"
#include "../dx/cMd3dManager.h"
#include "../util/timer/cMutilTimerManager.h"
#include "../physics/MphysicsManager.h"

class MsysManager
{
protected:
	static MsysManager*		m_pStaticPtr;

private:
	// System Resource
	MsysWindowManager*	m_winManager;
	Md3dManager*		m_d3dManager;
	MsysThreadManager*	m_threadManager;
	MutilTimerManager*	m_timerManager;

	// Game Resource
	MphysicsManager*	m_physicsManager;

	cMseqBase*			m_pCurrSeq;

public:
	MsysManager();
	virtual ~MsysManager();

	bool	InitEngine(HINSTANCE _hInstance);
	void	StartEngine(cMseqBase*	_initSeq);
	void	Cleanup();

public:
	static MsysManager*	GetManager();

	void	ChangeSequence(cMseqBase* _seq);

	Md3dManager*		GetD3dManager();
	MsysWindowManager*	GetWindowManager();
	MsysThreadManager*	GetThreadManager();
	MutilTimerManager*	GetTimerManager();
	MObjectManager*		GetObjectManager();
};

#endif