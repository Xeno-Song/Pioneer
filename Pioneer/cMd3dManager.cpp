#include "cMd3dManager.h"

cMd3dManager::cMd3dManager()
{
}

cMd3dManager::~cMd3dManager()
{

}

bool cMd3dManager::Initialize()
{
	if (LoadD3dParameters() == FALSE)	return false;

	if (CreateDevice() == FALSE)	return false;
	if (CreateSprite() == FALSE)	return false;

	return true;
}

bool cMd3dManager::LoadD3dParameters()
{
	return false;
}

bool cMd3dManager::SaveD3dDtaas()
{
	return false;
}

bool cMd3dManager::CreateDevice()
{
	m_pDeviceControl = new cMd3dDeviceControl();
	//TODO. Device parameter set
	m_pDeviceControl->CreateDevice();

	return true;
}

cMd3dDeviceControl * cMd3dManager::GetDeviceControl()
{
	return m_pDeviceControl;
}

const LPDIRECT3DDEVICE9 cMd3dManager::GetDevice()
{
	if (m_pDeviceControl == nullptr)
	{
		SetLastError(D3DERR_DEVICE_NOT_CREATED, S_OK);
		return NULL;
	}

	return m_pDeviceControl->GetDevice();
}

bool cMd3dManager::CreateSprite()
{
	if (GetDevice() == NULL)
	{
		SetLastError(D3DERR_DEVICE_NOT_CREATED, S_OK);
		return false;
	}

	m_pSpriteControl = new cMd3dSprite();

	return true;
}

cMd3dSprite * cMd3dManager::GetSpriteControl()
{
	return m_pSpriteControl;
}

const LPD3DXSPRITE cMd3dManager::GetSprite()
{
	if (m_pSpriteControl == nullptr)
	{
		SetLastError(D3DERR_SPRITE_NOT_CREATED, S_OK);
		return NULL;
	}

	return m_pSpriteControl->GetSprite();
}

bool cMd3dManager::GetLastError(E_D3DERR * _pError, HRESULT* _pResult)
{
	if (m_lastError == E_D3DERR::D3DERR_NONE)
	{
		(*_pError) = m_lastError;
		(*_pResult) = m_hLastError;
		return true;
	}

	return false;
}

void cMd3dManager::SetLastError(E_D3DERR _pError, HRESULT _pResult)
{
	m_lastError = _pError;
	m_hLastError = m_hLastError;
}

void cMd3dManager::ClearLastError()
{
	m_lastError = D3DERR_NONE;
	m_hLastError = S_OK;
}

