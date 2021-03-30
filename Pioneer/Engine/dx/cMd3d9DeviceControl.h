#pragma once


#ifndef	__M_D3D_DEVICE_CONTROL_H__
#define	__M_D3D_DEVICE_CONTROL_H__

#include "../Mdefines.h"
#ifndef __DX_VERSION_11__

#include "Md3dConfig.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Md3dDeviceControl
{
protected:
	LPDIRECT3D9				m_pD3d;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;

	std::vector<std::string>		m_gpuList;
	std::vector<D3DDISPLAYMODE>	m_monitorList;

	bool	m_initialized;
	int		m_monitorNum;

private:
	UINT	m_uFullScreenRefreshRateInHz;

public:
	Md3dDeviceControl();
	virtual ~Md3dDeviceControl();

	bool	Cleanup();
	bool	CreateDevice();
	bool	DestroyDevice();

	bool	GetAdapterList();
	void	SetDefaultParameter();

	void	LoadData(Md3dDeviceConfig* _datas);
	void	SaveData(Md3dDeviceConfig* _datas);
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

	
	UINT				GetBackBufferWidth();
	UINT				GetBackBufferHeight();
	D3DFORMAT			GetBackBufferFormat();
	UINT				GetBackBufferCount();
	D3DMULTISAMPLE_TYPE	GetMultiSampleType();
	DWORD				GetMultiSampleQuality();
	D3DSWAPEFFECT		GetSwapEffect();
	HWND				GetHwnd();
	BOOL				GetWindowed();
	BOOL				GetAutoDepthStencilEnable();
	D3DFORMAT			GetAutoDepthStencilFormat();
	DWORD				GetFlags();
	UINT				GetFullScreenRefreshRateInHz();
	UINT				GetPresentationInterval();

	const LPDIRECT3DDEVICE9	GetDevice();
};

#endif
#endif