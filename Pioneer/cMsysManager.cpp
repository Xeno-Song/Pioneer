#include "cMsysManager.h"
#include "Mdefines.h"

cMsysManager*		cMsysManager::m_pStaticPtr;

cMsysManager::cMsysManager()
{
	m_d3dManager = nullptr;
}

cMsysManager::~cMsysManager()
{
	Cleanup();
}

bool cMsysManager::InitEngine(HINSTANCE _hInstance)
{
	m_winManager = new cMsysWindowManager();
	m_d3dManager = new cMd3dManager();
	m_threadManager = new cMsysThreadManager();
	m_timerManager = new cMutilTimerManager();
	
	m_winManager->Create(_hInstance);
	m_d3dManager->Initialize();
	m_d3dManager->CreateDevice();

	return true;
}

void cMsysManager::StartEngine(cMseqBase* _initSeq)
{


	Sleep(10000);
}

cMsysManager * cMsysManager::GetManager()
{
	if (m_pStaticPtr == nullptr)
	{
		m_pStaticPtr = new cMsysManager();
	}
	return m_pStaticPtr;
}

void cMsysManager::ChangeSequence(cMseqBase * _seq)
{
}

void cMsysManager::Cleanup()
{
	SAFE_DELETE(m_d3dManager);
}

cMd3dManager * cMsysManager::GetD3dManager()
{
	return m_d3dManager;
}

cMsysWindowManager * cMsysManager::GetWindowManager()
{
	return m_winManager;
}

cMsysThreadManager * cMsysManager::GetThreadManager()
{
	return m_threadManager;
}

cMutilTimerManager * cMsysManager::GetTimerManager()
{
	return m_timerManager;
}
