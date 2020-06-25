#pragma once

#ifndef	__C_M_D3D_MANAGER_H__
#define	__C_M_D3D_MANAGER_H__

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class cMd3dDeviceControl
{
protected:
	LPDIRECT3D9				m_pD3d;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;

private:
	UINT	m_uFullScreenRefreshRateInHz;

public:
	cMd3dDeviceControl();
	virtual ~cMd3dDeviceControl();


	bool	Cleanup();
	bool	CreateDevice();
	bool	DestroyDevice();

	void	SetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp);
	void	GetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp);

	void	SetBackBufferWidth(UINT _uValue);
	void	SetBackBufferHeight(UINT _uValue);
	void	GetBackBufferFormat(D3DFORMAT _format);
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
	/**
	* @brief	Get device back buffer format
	* @return	return device back buffer format to D3DFORMAT
	* @see		SetBackBufferFormat()
	*/
	D3DFORMAT	GetBackBufferFormat();
	/**
	* @brief	Get device back buffer count
	* @return	return device back buffer count to UINT
	*/
	UINT	GetBackBufferCount();
	/**
	* @brief	Get device multi sample type
	* @return	return device multi sample type to D3DMULTISAMPLE_TYPE
	* @see		SetMultiSampleType()
	*/
	D3DMULTISAMPLE_TYPE	GetMultiSampleType();
	/**
	* @brief	Get device multi sample quality
	* @return	return device multi sample quality to DWORD
	* @see		SetMultiSampleQuality()
	*/
	DWORD	GetMultiSampleQuality();
	/**
	* @brief	Get device swap effect
	* @return	return device swap effect to D3DSWAPEFFECT
	* @see		SetMultiSampleQuality()
	*/
	D3DSWAPEFFECT	GetSwapEffect();
	/**
	* @brief	Get device window handle
	* @return	return device window handle to HWND
	*/
	HWND	GetHwnd();
	/**
	* @brief	Get device windowed mode
	* @return	return device windowed mode width to UINT
	*/
	BOOL	GetWindowed();
	/**
	* @brief	Get device auto depth stencil mode enabled
	* @return	return device auto depth stencil mode is enable to BOOL
	*/
	BOOL	GetEnalbeAutoDepthStencil();
	/**
	* @brief	Get device auto depth stencil format
	* @return	return device auto depth stencil format to D3DFORMAT
	* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
	*/
	D3DFORMAT	GetAutoDepthStencilFormat();
	/**
	* @brief	Get device flags
	* @return	return device flags to D3DFORMAT
	*/
	DWORD	GetFlags();
	/**
	* @brief	Get device full screen refresh rate in Hz
	* @return	return device full screen refresh rate in Hz to UINT
	*/
	UINT	GetFullScreenRefreshRateInHz();
	/**
	* @brief	Get device presentation interval
	* @return	return device presentation interval UINT
	*/
	UINT	GetPresentationInterval();

	
	const LPDIRECT3DDEVICE9	GetDevice();
};

#endif