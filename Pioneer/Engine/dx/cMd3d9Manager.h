#pragma once

#ifndef __M_C_D3DMANAGER_H__
#define __M_C_D3DMANAGER_H__
#include "../Mdefines.h"
#ifndef __DX_VERSION_11__

#include "../res/sprite/cMd3dSprite.h"
#include "../MErrorCodes.h"
#include "cMd3d9DeviceControl.h"

class Md3dManager
{
public:
	Md3dManager();
	virtual ~Md3dManager();

protected:
	Md3dDeviceControl*	m_pDeviceControl;
	cMd3dSprite*		m_pSpriteControl;

private:
	E_D3DERR		m_lastError;
	HRESULT			m_hLastError;

public:
	bool	Initialize();

	bool	LoadD3dParameters();
	bool	SaveD3dDtaas();

	bool					CreateDevice();
	Md3dDeviceControl*		GetDeviceControl();
	const LPDIRECT3DDEVICE9	GetDevice();

	bool					CreateSprite();
	cMd3dSprite*			GetSpriteControl();
	const LPD3DXSPRITE		GetSprite();

	bool	GetLastError(E_D3DERR* _pError, HRESULT* _pResult = nullptr);
	void	SetLastError(E_D3DERR _pError, HRESULT m_hLastError);
	void	ClearLastError();
};

#endif
#endif