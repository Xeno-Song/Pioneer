#pragma once

#ifndef	__C_M_D3D_MANAGER_H__
#define	__C_M_D3D_MANAGER_H__

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class cMd3dDevice
{
protected:
	LPDIRECT3D9				m_pD3d;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;

public:
	cMd3dDevice();
	virtual ~cMd3dDevice();

	bool	Cleanup();

	bool	CreateDevice();
	bool	DestroyDevice();

	LPDIRECT3DDEVICE9	GetDevice();
};

#endif