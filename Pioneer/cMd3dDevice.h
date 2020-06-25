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

private:
	UINT	m_uFullScreenRefreshRateInHz;

public:
	cMd3dDevice();
	virtual ~cMd3dDevice();

	bool	Cleanup();

	bool	CreateDevice();
	bool	DestroyDevice();

	////

	void	SetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp);
	void	GetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp);

	void	SetBackBufferWidth(UINT _uValue);
	void	SetBackBufferHeight(UINT _uValue);
	void	SetBackBufferFormat(D3DFORMAT _format);
	void	SetBackBufferCount(UINT _uValue);
	void	SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType);
	void	SetMultiSampleQuality(DWORD _dwQuality);
	void	SetSwapEffect(D3DSWAPEFFECT _value);
	void	SetHDeviceWindow(HWND _value);
	void	SetWindowed(BOOL _value);
	void	SetEnableAutoDepthStencil(BOOL _value);
	void	SetAutoDepthStencilFormat(D3DFORMAT _value);
	void	SetFlags(DWORD _value);
	void	SetFullScreenRefreshRateInHz(UINT _value);
	void	SetPresentationInterval(UINT _value);

	UINT	GetBackBufferWidth();
	UINT	GetBackBufferHeight();
	D3DFORMAT	SetBackBufferFormat();
	UINT	GetBackBufferCount();
	D3DMULTISAMPLE_TYPE	GetMultiSampleType();
	DWORD	GetMultiSampleQuality();
	D3DSWAPEFFECT	GetSwapEffect();
	HWND	GetHwnd();
	BOOL	GetWindowed();
	BOOL	GetEnalbeAutoDepthStencil();
	D3DFORMAT	GetAutoDepthStencilFormat();
	DWORD	GetFlags();
	UINT	GetFullScreenRefreshRateInHz();
	UINT	GetPresentationInterval();

	LPDIRECT3DDEVICE9	GetDevice();
};

#endif