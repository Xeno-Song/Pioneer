#pragma once

#ifndef __M_C_D3DMANAGER_H__
#define __M_C_D3DMANAGER_H__

#include "cMd3dDeviceControl.h"
#include "cMd3dSprite.h"

#include "ErrorCodes.h"

class cMd3dManager
{
public:
	cMd3dManager();
	virtual ~cMd3dManager();

protected:
	cMd3dDeviceControl*	m_pDeviceControl;
	cMd3dSprite*		m_pSpriteControl;

private:
	E_D3DERR		m_lastError;
	HRESULT			m_hLastError;

public:
	bool	Initialize();

	bool	LoadD3dParameters();
	bool	SaveD3dDtaas();

	bool					CreateDevice();
	cMd3dDeviceControl*		GetDeviceControl();
	const LPDIRECT3DDEVICE9	GetDevice();

	bool					CreateSprite();
	cMd3dSprite*			GetSpriteControl();
	const LPD3DXSPRITE		GetSprite();

	bool	GetLastError(E_D3DERR* _pError, HRESULT* _pResult = nullptr);
	void	SetLastError(E_D3DERR _pError, HRESULT m_hLastError);
	void	ClearLastError();
};

#endif