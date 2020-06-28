#include "cMSystemManager.h"
#include "Mdefines.h"

cMSystemManager*		cMSystemManager::m_pStaticPtr;

cMSystemManager::cMSystemManager()
{
	m_pD3dManager = nullptr;
}

cMSystemManager::~cMSystemManager()
{
	Cleanup();
}

bool cMSystemManager::InitEngine(HINSTANCE _hInstance)
{
	m_winManager = new cMsysWindowManager();
	m_pD3dManager = new cMd3dManager();
	
	m_winManager->Create(_hInstance);
	m_pD3dManager->Initialize();
	m_pD3dManager->CreateDevice();

	return false;
}

void cMSystemManager::StartEngine()
{
	Sleep(10000);
}

cMSystemManager * cMSystemManager::GetManager()
{
	if (m_pStaticPtr == nullptr)
	{
		m_pStaticPtr = new cMSystemManager();
	}
	return m_pStaticPtr;
}

void cMSystemManager::Cleanup()
{
	SAFE_DELETE(m_pD3dManager);
}

cMd3dManager * cMSystemManager::GetD3dManager()
{
	return m_pD3dManager;
}

cMsysWindowManager * cMSystemManager::GetWindowManager()
{
	return m_winManager;
}
