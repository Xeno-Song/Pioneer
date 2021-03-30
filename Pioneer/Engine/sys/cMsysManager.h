#pragma once

#ifndef __M_C_SYSTEM_MANAGER_H__
#define __M_C_SYSTEM_MANAGER_H__

#define MGetSystem()		MsysManager::GetManager()

#include "../Mdefines.h"

#include "../sys/wnd/cMsysWindowManager.h"
#include "../sys/thd/MsysThreadManager.h"
#include "../seq/cMseqBase.h"
#include "../util/timer/cMutilTimerManager.h"
#include "../physics/MphysicsManager.h"

#ifdef __DX_VERSION_11__
#include "../dx/cMd3d11Manager.h"
#else
#include "../dx/cMd3d9Manager.h"
#endif

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

	cMseqBase*			m_currSeq;

public:
	MsysManager();
	virtual ~MsysManager();

	bool	InitEngine(HINSTANCE hInstance);
	void	StartEngine(cMseqBase*	initSeq);
	void	Cleanup();

public:
	static MsysManager*	GetManager();

	void	ChangeSequence(cMseqBase* _seq);

	Md3dManager*		GetD3dManager() const;
	MsysWindowManager*	GetWindowManager() const;
	MsysThreadManager*	GetThreadManager() const;
	MutilTimerManager*	GetTimerManager() const;
	MphysicsManager*	GetPhysicsManager() const;
};

#endif