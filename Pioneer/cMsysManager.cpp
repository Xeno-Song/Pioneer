#include "cMsysManager.h"
#include "Mdefines.h"

cMsysManager*		cMsysManager::m_pStaticPtr;

cMsysManager::cMsysManager()
{
	m_pD3dManager = nullptr;
}

cMsysManager::~cMsysManager()
{
	Cleanup();
}

bool cMsysManager::InitEngine(HINSTANCE _hInstance)
{
	m_winManager = new cMsysWindowManager();
	m_pD3dManager = new cMd3dManager();
	
	m_winManager->Create(_hInstance);
	m_pD3dManager->Initialize();
	m_pD3dManager->CreateDevice();

	return false;
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
	SAFE_DELETE(m_pD3dManager);
}

cMd3dManager * cMsysManager::GetD3dManager()
{
	return m_pD3dManager;
}

cMsysWindowManager * cMsysManager::GetWindowManager()
{
	return m_winManager;
}
