#include "cMd3dDevice.h"
#include "cMSystemManager.h"
#include "cMd3dManager.h"
#include "defines.h"

cMd3dDevice::cMd3dDevice()
{
	m_pD3d		= NULL;
	m_pDevice	= NULL;

	m_uFullScreenRefreshRateInHz = 0;
}

cMd3dDevice::~cMd3dDevice()
{
}

bool cMd3dDevice::Cleanup()
{
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3d);

	return false;
}

bool cMd3dDevice::CreateDevice()
{
	m_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d == NULL)
	{
		MGetSystem()->GetD3dManager()->SetLastError(E_D3dError::D3DERROR_DIRECT3D9_CREATE_FAILED);
		return FALSE;
	}

	
	
	return false;
}

bool cMd3dDevice::DestroyDevice()
{
	if (m_pDevice == NULL)	return false;

	m_pDevice->Release();
	m_pDevice = nullptr;

	return true;
}

void cMd3dDevice::SetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	memcpy(&m_pD3d, _pD3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

void cMd3dDevice::GetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	if (_pD3dpp == nullptr)	return;
	memcpy(_pD3dpp, &m_pD3d, sizeof(D3DPRESENT_PARAMETERS));
}

void cMd3dDevice::SetBackBufferWidth(UINT _uValue)
{
	m_d3dpp.BackBufferWidth = _uValue;
}

void cMd3dDevice::SetBackBufferHeight(UINT _uValue)
{
	m_d3dpp.BackBufferHeight = _uValue;
}

void cMd3dDevice::SetBackBufferFormat(D3DFORMAT _format)
{
	m_d3dpp.BackBufferFormat = _format;
}

void cMd3dDevice::SetBackBufferCount(UINT _uValue)
{
	m_d3dpp.BackBufferCount = _uValue;
}

void cMd3dDevice::SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType)
{
	m_d3dpp.MultiSampleType = _sampleType;
}

void cMd3dDevice::SetMultiSampleQuality(DWORD _dwQuality)
{
	m_d3dpp.MultiSampleQuality = _dwQuality;
}

void cMd3dDevice::SetSwapEffect(D3DSWAPEFFECT _value)
{
	m_d3dpp.SwapEffect = _value;
}

void cMd3dDevice::SetHDeviceWindow(HWND _value)
{
	m_d3dpp.hDeviceWindow = _value;
}

void cMd3dDevice::SetWindowed(BOOL _value)
{
	m_d3dpp.Windowed = _value;

	if (_value == TRUE)		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	else					m_d3dpp.FullScreen_RefreshRateInHz = m_uFullScreenRefreshRateInHz;
}

void cMd3dDevice::SetEnableAutoDepthStencil(BOOL _value)
{
	m_d3dpp.EnableAutoDepthStencil = _value;
}

void cMd3dDevice::SetAutoDepthStencilFormat(D3DFORMAT _value)
{
	m_d3dpp.AutoDepthStencilFormat = _value;
}

void cMd3dDevice::SetFlags(DWORD _value)
{
	m_d3dpp.Flags = _value;
}

void cMd3dDevice::SetFullScreenRefreshRateInHz(UINT _value)
{
	m_uFullScreenRefreshRateInHz = _value;
	m_d3dpp.FullScreen_RefreshRateInHz = _value;
}

void cMd3dDevice::SetPresentationInterval(UINT _value)
{
	m_d3dpp.PresentationInterval = _value;
}

UINT cMd3dDevice::GetBackBufferWidth()
{
	return m_d3dpp.BackBufferWidth;
}

UINT cMd3dDevice::GetBackBufferHeight()
{
	return m_d3dpp.BackBufferHeight;
}

D3DFORMAT cMd3dDevice::SetBackBufferFormat()
{
	return m_d3dpp.BackBufferFormat;
}

UINT cMd3dDevice::GetBackBufferCount()
{
	return m_d3dpp.BackBufferCount;
}

D3DMULTISAMPLE_TYPE cMd3dDevice::GetMultiSampleType()
{
	return m_d3dpp.MultiSampleType;
}

DWORD cMd3dDevice::GetMultiSampleQuality()
{
	return m_d3dpp.MultiSampleQuality;
}

D3DSWAPEFFECT cMd3dDevice::GetSwapEffect()
{
	return m_d3dpp.SwapEffect;
}

HWND cMd3dDevice::GetHwnd()
{
	return m_d3dpp.hDeviceWindow;
}

BOOL cMd3dDevice::GetWindowed()
{
	return m_d3dpp.Windowed;
}

BOOL cMd3dDevice::GetEnalbeAutoDepthStencil()
{
	return m_d3dpp.EnableAutoDepthStencil;
}

D3DFORMAT cMd3dDevice::GetAutoDepthStencilFormat()
{
	return m_d3dpp.AutoDepthStencilFormat;
}

DWORD cMd3dDevice::GetFlags()
{
	return m_d3dpp.Flags;
}

UINT cMd3dDevice::GetFullScreenRefreshRateInHz()
{
	return m_uFullScreenRefreshRateInHz;
}

UINT cMd3dDevice::GetPresentationInterval()
{
	return m_d3dpp.PresentationInterval;
}

LPDIRECT3DDEVICE9 cMd3dDevice::GetDevice()
{
	return m_pDevice;
}
