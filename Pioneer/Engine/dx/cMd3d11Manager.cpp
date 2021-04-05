#include "../Mdefines.h"
#ifdef __DX_VERSION_11__

#include "cMd3d11Manager.h"

Md3dManager::Md3dManager()
{
}

Md3dManager::~Md3dManager()
{

}

bool Md3dManager::Initialize()
{
	if (LoadD3dParameters() == FALSE)	return false;

	if (CreateDevice() == FALSE)	return false;
	if (CreateSprite() == FALSE)	return false;

	return true;
}

bool Md3dManager::LoadD3dParameters()
{
	return false;
}

bool Md3dManager::SaveD3dDtaas()
{
	return false;
}

bool Md3dManager::CreateDevice()
{
	m_pDeviceControl = new Md3dDeviceControl();
	//TODO. Device parameter set
	m_pDeviceControl->CreateDevice();

	return true;
}

Md3dDeviceControl * Md3dManager::GetDeviceControl()
{
	return m_pDeviceControl;
}

const ID3D11Device* Md3dManager::GetDevice()
{
	if (m_pDeviceControl == nullptr)
	{
		SetLastError(D3DERR_DEVICE_NOT_CREATED, S_OK);
		return NULL;
	}

	return m_pDeviceControl->GetDevice();
}

void Md3dManager::BeginScene() const
{
	m_pDeviceControl->BeginScene();
}

void Md3dManager::EndScene() const
{
	m_pDeviceControl->EndScene();
}

bool Md3dManager::CreateSprite()
{
	if (GetDevice() == NULL)
	{
		SetLastError(D3DERR_DEVICE_NOT_CREATED, S_OK);
		return false;
	}

	m_pSpriteControl = new cMd3dSprite();

	return true;
}

cMd3dSprite * Md3dManager::GetSpriteControl()
{
	return m_pSpriteControl;
}

const LPD3DXSPRITE Md3dManager::GetSprite()
{
	if (m_pSpriteControl == nullptr)
	{
		SetLastError(D3DERR_SPRITE_NOT_CREATED, S_OK);
		return NULL;
	}

	return m_pSpriteControl->GetSprite();
}

bool Md3dManager::GetLastError(E_D3DERR * _pError, HRESULT* _pResult)
{
	if (m_lastError == E_D3DERR::D3DERR_NONE)
	{
		(*_pError) = m_lastError;
		(*_pResult) = m_hLastError;
		return true;
	}

	return false;
}

void Md3dManager::SetLastError(E_D3DERR _pError, HRESULT _pResult)
{
	m_lastError = _pError;
	m_hLastError = m_hLastError;
}

void Md3dManager::ClearLastError()
{
	m_lastError = D3DERR_NONE;
	m_hLastError = S_OK;
}

#endif