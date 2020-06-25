#include "cMd3dDeviceControl.h"
#include "cMSystemManager.h"
#include "cMd3dManager.h"
#include "defines.h"

cMd3dDeviceControl::cMd3dDeviceControl()
{
	m_pD3d		= NULL;
	m_pDevice	= NULL;

	m_uFullScreenRefreshRateInHz = 0;
}

cMd3dDeviceControl::~cMd3dDeviceControl()
{
}

bool cMd3dDeviceControl::Cleanup()
{
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3d);

	return false;
}

bool cMd3dDeviceControl::CreateDevice()
{
	m_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d == NULL)
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_DIRECT3D9_CREATE_FAILED, NULL);
		return FALSE;
	}

	
	
	return false;
}

bool cMd3dDeviceControl::DestroyDevice()
{
	if (m_pDevice == NULL)	return false;

	m_pDevice->Release();
	m_pDevice = nullptr;

	return true;
}

void cMd3dDeviceControl::SetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	memcpy(&m_pD3d, _pD3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

void cMd3dDeviceControl::GetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	if (_pD3dpp == nullptr)	return;
	memcpy(_pD3dpp, &m_pD3d, sizeof(D3DPRESENT_PARAMETERS));
}

void cMd3dDeviceControl::SetBackBufferWidth(UINT _uValue)
{
	m_d3dpp.BackBufferWidth = _uValue;
}

void cMd3dDeviceControl::SetBackBufferHeight(UINT _uValue)
{
	m_d3dpp.BackBufferHeight = _uValue;
}

void cMd3dDeviceControl::SetBackBufferFormat(D3DFORMAT _format)
{
	m_d3dpp.BackBufferFormat = _format;
}

void cMd3dDeviceControl::SetBackBufferCount(UINT _uValue)
{
	m_d3dpp.BackBufferCount = _uValue;
}

void cMd3dDeviceControl::SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType)
{
	m_d3dpp.MultiSampleType = _sampleType;
}

void cMd3dDeviceControl::SetMultiSampleQuality(DWORD _dwQuality)
{
	m_d3dpp.MultiSampleQuality = _dwQuality;
}

void cMd3dDeviceControl::SetSwapEffect(D3DSWAPEFFECT _value)
{
	m_d3dpp.SwapEffect = _value;
}

void cMd3dDeviceControl::SetHDeviceWindow(HWND _value)
{
	m_d3dpp.hDeviceWindow = _value;
}

void cMd3dDeviceControl::SetWindowed(BOOL _value)
{
	m_d3dpp.Windowed = _value;

	if (_value == TRUE)		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	else					m_d3dpp.FullScreen_RefreshRateInHz = m_uFullScreenRefreshRateInHz;
}

void cMd3dDeviceControl::SetEnableAutoDepthStencil(BOOL _value)
{
	m_d3dpp.EnableAutoDepthStencil = _value;
}

void cMd3dDeviceControl::SetAutoDepthStencilFormat(D3DFORMAT _value)
{
	m_d3dpp.AutoDepthStencilFormat = _value;
}

void cMd3dDeviceControl::SetFlags(DWORD _value)
{
	m_d3dpp.Flags = _value;
}

void cMd3dDeviceControl::SetFullScreenRefreshRateInHz(UINT _value)
{
	m_uFullScreenRefreshRateInHz = _value;
	m_d3dpp.FullScreen_RefreshRateInHz = _value;
}

void cMd3dDeviceControl::SetPresentationInterval(UINT _value)
{
	m_d3dpp.PresentationInterval = _value;
}

UINT cMd3dDeviceControl::GetBackBufferWidth()
{
	return m_d3dpp.BackBufferWidth;
}

UINT cMd3dDeviceControl::GetBackBufferHeight()
{
	return m_d3dpp.BackBufferHeight;
}

D3DFORMAT cMd3dDeviceControl::SetBackBufferFormat()
{
	return m_d3dpp.BackBufferFormat;
}

UINT cMd3dDeviceControl::GetBackBufferCount()
{
	return m_d3dpp.BackBufferCount;
}

D3DMULTISAMPLE_TYPE cMd3dDeviceControl::GetMultiSampleType()
{
	return m_d3dpp.MultiSampleType;
}

DWORD cMd3dDeviceControl::GetMultiSampleQuality()
{
	return m_d3dpp.MultiSampleQuality;
}

D3DSWAPEFFECT cMd3dDeviceControl::GetSwapEffect()
{
	return m_d3dpp.SwapEffect;
}

HWND cMd3dDeviceControl::GetHwnd()
{
	return m_d3dpp.hDeviceWindow;
}

BOOL cMd3dDeviceControl::GetWindowed()
{
	return m_d3dpp.Windowed;
}

BOOL cMd3dDeviceControl::GetEnalbeAutoDepthStencil()
{
	return m_d3dpp.EnableAutoDepthStencil;
}

D3DFORMAT cMd3dDeviceControl::GetAutoDepthStencilFormat()
{
	return m_d3dpp.AutoDepthStencilFormat;
}

DWORD cMd3dDeviceControl::GetFlags()
{
	return m_d3dpp.Flags;
}

UINT cMd3dDeviceControl::GetFullScreenRefreshRateInHz()
{
	return m_uFullScreenRefreshRateInHz;
}

UINT cMd3dDeviceControl::GetPresentationInterval()
{
	return m_d3dpp.PresentationInterval;
}

const LPDIRECT3DDEVICE9 cMd3dDeviceControl::GetDevice()
{
	return m_pDevice;
}
