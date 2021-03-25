#pragma once


#ifndef	__C_M_D3D_DEVICE_IMPLEMENTS_H__
#define	__C_M_D3D_DEVICE_IMPLEMENTS_H__

#include "Md3dConfig.h"

#ifdef __DX_VERSION_11__
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

class Md3dDeviceControl
{
public:
	Md3dDeviceControl();
	virtual ~Md3dDeviceControl();

	bool	Cleanup();
	bool	CreateDevice();
	bool	DestroyDevice();

	bool	GetAdapterList();
	void	SetDefaultParameter();

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

	const ID3D11Device*	GetDevice();

protected:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;

	std::vector<std::string>		m_gpuList;
	std::vector<D3DDISPLAYMODE>	m_monitorList;

	bool	m_initialized;
	int		m_monitorNum;

private:
	UINT	m_fullScreenRefreshRateInHz;
	UINT	m_screenWidth;
	UINT	m_screenHeight;
};

#endif

#endif