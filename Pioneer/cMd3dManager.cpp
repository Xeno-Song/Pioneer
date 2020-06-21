#include "cMd3dManager.h"

cMd3dManager::cMd3dManager()
{
	m_pDevice = NULL;
}

cMd3dManager::~cMd3dManager()
{

}

bool cMd3dManager::CreateDevice(bool _bWindowed)
{
	return false;
}

LPDIRECT3DDEVICE9 cMd3dManager::GetDevice()
{
	return LPDIRECT3DDEVICE9();
}
