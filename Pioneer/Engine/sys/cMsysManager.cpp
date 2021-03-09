#include "cMsysManager.h"
#include "../Mdefines.h"

MsysManager*		MsysManager::m_pStaticPtr;

MsysManager::MsysManager()
{
	m_d3dManager = nullptr;
}

MsysManager::~MsysManager()
{
	Cleanup();
}

bool MsysManager::InitEngine(HINSTANCE _hInstance)
{
	m_winManager = new MsysWindowManager();
	m_d3dManager = new Md3dManager();
	m_threadManager = new MsysThreadManager();
	m_timerManager = new MutilTimerManager();
	m_objectManager = new MObjectManager();
	
	m_winManager->Create(_hInstance);
	m_d3dManager->Initialize();
	m_d3dManager->CreateDevice();
	m_timerManager->InitializeTimerManager();

	return true;
}

void MsysManager::StartEngine(cMseqBase* _initSeq)
{


	Sleep(10000);
}

MsysManager * MsysManager::GetManager()
{
	if (m_pStaticPtr == nullptr)
	{
		m_pStaticPtr = new MsysManager();
	}
	return m_pStaticPtr;
}

void MsysManager::ChangeSequence(cMseqBase * _seq)
{
}

void MsysManager::Cleanup()
{
	SAFE_DELETE(m_d3dManager);
	SAFE_DELETE(m_winManager);
	SAFE_DELETE(m_threadManager);
	SAFE_DELETE(m_timerManager);
	SAFE_DELETE(m_objectManager);
}

Md3dManager * MsysManager::GetD3dManager()
{
	return m_d3dManager;
}

MsysWindowManager * MsysManager::GetWindowManager()
{
	return m_winManager;
}

MsysThreadManager * MsysManager::GetThreadManager()
{
	return m_threadManager;
}

MutilTimerManager * MsysManager::GetTimerManager()
{
	return m_timerManager;
}

MObjectManager* MsysManager::GetObjectManager()
{
	return m_objectManager;
}
