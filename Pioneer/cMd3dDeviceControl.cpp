#include "cMd3dDeviceControl.h"
#include "cMSystemManager.h"
#include "cMd3dManager.h"
#include "Mdefines.h"

cMd3dDeviceControl::cMd3dDeviceControl()
{
	m_pD3d		= NULL;
	m_pDevice	= NULL;

	m_uFullScreenRefreshRateInHz = 0;
}

cMd3dDeviceControl::~cMd3dDeviceControl()
{
}

/**
* @brief	Delete objects in this device control
* @return	return true if success, otherwise false
*/
bool cMd3dDeviceControl::Cleanup()
{
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3d);

	return false;
}

/**
* @brief	Create device object
* @return	return true if success, otherwise false
* @return	if failed to create, you can check error in the function below
* @see		cMd3dManager::GetLastError()
*/
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

/**
* @brief	Destroy device object
* @return	return true if success, otherwise false
* @return	if failed to create, you can check error in the function below
* @see		cMd3dManager::GetLastError()
*/
bool cMd3dDeviceControl::DestroyDevice()
{
	if (m_pDevice == NULL)	return false;

	m_pDevice->Release();
	m_pDevice = nullptr;

	return true;
}

/**
* @brief	Set device creation parameters
* @param	D3DPRESENT_PARAMETERS* _pD3dpp source parameters pointer
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresent-parameters
*/
void cMd3dDeviceControl::SetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	memcpy(&m_pD3d, _pD3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

/**
* @brief	Get device creation parameters
* @param	D3DPRESENT_PARAMETERS* _pD3dpp result parameters pointer
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresent-parameters
*/
void cMd3dDeviceControl::GetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	if (_pD3dpp == nullptr)	return;
	memcpy(_pD3dpp, &m_pD3d, sizeof(D3DPRESENT_PARAMETERS));
}

/**
* @brief	Set device back buffer width
* @param	UINT _uValue Width to change
*/
void cMd3dDeviceControl::SetBackBufferWidth(UINT _uValue)
{
	m_d3dpp.BackBufferWidth = _uValue;
}

/**
* @brief	Set device back buffer height
* @param	UINT _uValue Height to change
*/
void cMd3dDeviceControl::SetBackBufferHeight(UINT _uValue)
{
	m_d3dpp.BackBufferHeight = _uValue;
}

/**
* @brief	Set device back buffer format
* @param	D3DFORMAT _format Buffer format to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
void cMd3dDeviceControl::SetBackBufferFormat(D3DFORMAT _format)
{
	m_d3dpp.BackBufferFormat = _format;
}

/**
* @brief	Set device back buffer width
* @param	UINT _uValue Width to change
*/
void cMd3dDeviceControl::SetBackBufferCount(UINT _uValue)
{
	m_d3dpp.BackBufferCount = _uValue;
}

/**
* @brief	Set device multi smaple type
* @param	D3DMULTISAMPLE_TYPE _sampleType Sample type to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dmultisample-type
*/
void cMd3dDeviceControl::SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType)
{
	m_d3dpp.MultiSampleType = _sampleType;
}

/**
* @brief	Set device multi sample quality
* @param	DWORD _dwQuality Quility to change
*/
void cMd3dDeviceControl::SetMultiSampleQuality(DWORD _dwQuality)
{
	m_d3dpp.MultiSampleQuality = _dwQuality;
}

/**
* @brief	Set device swap effect
* @param	D3DSWAPEFFECT _value Swap effect to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dswapeffect
*/
void cMd3dDeviceControl::SetSwapEffect(D3DSWAPEFFECT _value)
{
	m_d3dpp.SwapEffect = _value;
}

/**
* @brief	Set device target window handle
* @param	HWND _value Window handle to change
*/
void cMd3dDeviceControl::SetHDeviceWindow(HWND _value)
{
	m_d3dpp.hDeviceWindow = _value;
}

/**
* @brief	Set device mode is windowed
* @param	BOOL _value if true, device create by windowed. else if false, device create by fullscreen
*/
void cMd3dDeviceControl::SetWindowed(BOOL _value)
{
	m_d3dpp.Windowed = _value;

	if (_value == TRUE)		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	else					m_d3dpp.FullScreen_RefreshRateInHz = m_uFullScreenRefreshRateInHz;
}

/**
* @brief	Set device auto depth stencil
* @param	BOOL _value if true, enalbe auto depth stencil
*/
void cMd3dDeviceControl::SetEnableAutoDepthStencil(BOOL _value)
{
	m_d3dpp.EnableAutoDepthStencil = _value;
}

/**
* @brief	Set device auto depth stencil format
* @param	D3DFORMAT _value Buffer format to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
void cMd3dDeviceControl::SetAutoDepthStencilFormat(D3DFORMAT _value)
{
	m_d3dpp.AutoDepthStencilFormat = _value;
}

/**
* @brief	Set device create flags
* @param	DWORD _value flags to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresentflag
*/
void cMd3dDeviceControl::SetFlags(DWORD _value)
{
	m_d3dpp.Flags = _value;
}

/**
* @brief	Set device full screen refresh rate to Hz
* @param	UINT _value refresh Hz to change (in fullscreen)
*/
void cMd3dDeviceControl::SetFullScreenRefreshRateInHz(UINT _value)
{
	m_uFullScreenRefreshRateInHz = _value;
	m_d3dpp.FullScreen_RefreshRateInHz = _value;
}

/**
* @brief	Set device presentation interval
* @details	if set 60, swap chain can show 60 frame/sec
* @defails	a.k.a max framerate
* @param	UINT _value Maximum interval
*/
void cMd3dDeviceControl::SetPresentationInterval(UINT _value)
{
	m_d3dpp.PresentationInterval = _value;
}

/**
* @brief	Get device back buffer width
* @return	return device back buffer width to UINT
*/
UINT cMd3dDeviceControl::GetBackBufferWidth()
{
	return m_d3dpp.BackBufferWidth;
}

/**
* @brief	Get device back buffer height
* @return	return device back buffer height to UINT
*/
UINT cMd3dDeviceControl::GetBackBufferHeight()
{
	return m_d3dpp.BackBufferHeight;
}

/**
* @brief	Get device back buffer format
* @return	return device back buffer format to D3DFORMAT
* @see		SetBackBufferFormat()
*/
D3DFORMAT cMd3dDeviceControl::GetBackBufferFormat()
{
	return m_d3dpp.BackBufferFormat;
}

/**
* @brief	Get device back buffer count
* @return	return device back buffer count to UINT
*/
UINT cMd3dDeviceControl::GetBackBufferCount()
{
	return m_d3dpp.BackBufferCount;
}

/**
* @brief	Get device multi sample type
* @return	return device multi sample type to D3DMULTISAMPLE_TYPE
* @see		SetMultiSampleType()
*/
D3DMULTISAMPLE_TYPE cMd3dDeviceControl::GetMultiSampleType()
{
	return m_d3dpp.MultiSampleType;
}

/**
* @brief	Get device multi sample quality
* @return	return device multi sample quality to DWORD
* @see		SetMultiSampleQuality()
*/
DWORD cMd3dDeviceControl::GetMultiSampleQuality()
{
	return m_d3dpp.MultiSampleQuality;
}

/**
* @brief	Get device swap effect
* @return	return device swap effect to D3DSWAPEFFECT
* @see		SetMultiSampleQuality()
*/
D3DSWAPEFFECT cMd3dDeviceControl::GetSwapEffect()
{
	return m_d3dpp.SwapEffect;
}

/**
* @brief	Get device window handle
* @return	return device window handle to HWND
*/
HWND cMd3dDeviceControl::GetHwnd()
{
	return m_d3dpp.hDeviceWindow;
}

/**
* @brief	Get device windowed mode
* @return	return device windowed mode width to UINT
*/
BOOL cMd3dDeviceControl::GetWindowed()
{
	return m_d3dpp.Windowed;
}

/**
* @brief	Get device auto depth stencil mode enabled
* @return	return device auto depth stencil mode is enable to BOOL
*/
BOOL cMd3dDeviceControl::GetEnalbeAutoDepthStencil()
{
	return m_d3dpp.EnableAutoDepthStencil;
}

/**
* @brief	Get device auto depth stencil format
* @return	return device auto depth stencil format to D3DFORMAT
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
D3DFORMAT cMd3dDeviceControl::GetAutoDepthStencilFormat()
{
	return m_d3dpp.AutoDepthStencilFormat;
}

/**
* @brief	Get device flags
* @return	return device flags to D3DFORMAT
*/
DWORD cMd3dDeviceControl::GetFlags()
{
	return m_d3dpp.Flags;
}

/**
* @brief	Get device full screen refresh rate in Hz
* @return	return device full screen refresh rate in Hz to UINT
*/
UINT cMd3dDeviceControl::GetFullScreenRefreshRateInHz()
{
	return m_uFullScreenRefreshRateInHz;
}

/**
* @brief	Get device presentation interval
* @return	return device presentation interval UINT
*/
UINT cMd3dDeviceControl::GetPresentationInterval()
{
	return m_d3dpp.PresentationInterval;
}

/**
	* @brief	Get device pointer
	* @return	return device to LPDIRECT3DDEVICE9
	*/
const LPDIRECT3DDEVICE9 cMd3dDeviceControl::GetDevice()
{
	return m_pDevice;
}
