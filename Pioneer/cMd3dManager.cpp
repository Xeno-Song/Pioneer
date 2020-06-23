#include "cMd3dManager.h"

cMd3dManager::cMd3dManager()
{
}

cMd3dManager::~cMd3dManager()
{

}

bool cMd3dManager::GetLastError(E_D3dError * _pError)
{
	if (m_lastError == E_D3dError::D3DERROR_NONE)
	{
		(*_pError) = m_lastError;
		return true;
	}

	return false;
}

void cMd3dManager::SetLastError(E_D3dError _pError)
{
	m_lastError = _pError;
}
