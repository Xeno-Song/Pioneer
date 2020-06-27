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

bool cMSystemManager::InitEngine()
{
	m_pD3dManager = new cMd3dManager();
	
	m_pD3dManager->Initialize();

	return false;
}

void cMSystemManager::StartEngine()
{
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
