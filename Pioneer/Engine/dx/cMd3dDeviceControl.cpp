#include "cMd3dDeviceControl.h"
#include "../sys/cMsysManager.h"
#include "../Mdefines.h"

Md3dDeviceControl::Md3dDeviceControl()
{
	m_pD3d		= NULL;
	m_pDevice	= NULL;

	m_uFullScreenRefreshRateInHz = 0;
}

Md3dDeviceControl::~Md3dDeviceControl()
{
	Cleanup();
}

/**
* @brief	Delete objects in this device control
* @return	return true if success, otherwise false
*/
bool Md3dDeviceControl::Cleanup()
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
bool Md3dDeviceControl::CreateDevice()
{
	HRESULT hResult = S_OK;

	m_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d == NULL)
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_DIRECT3D9_CREATE_FAILED, NULL);
		return FALSE;
	}

	if (GetAdapterList() == FALSE)
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_DEVICE_CANNOT_LOAD_ADAPTER_LIST, NULL);
		return FALSE;
	}
	
	if (m_initalized == FALSE)
	{
		SetDefaultParameter();
	}

	HWND	hwnd = NULL;
	hwnd = MGetSystem()->GetWindowManager()->GetWindowHandle();
	if (hwnd == NULL)
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_DEVICE_WINDOW_IS_NOT_CREATED, NULL);
		return FALSE;
	}

	m_d3dpp.hDeviceWindow = hwnd;

	hResult = m_pD3d->CreateDevice(
		m_monitorNum,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&m_d3dpp,
		&m_pDevice
	);
	if (FAILED(hResult))
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_DEVICE_CREATE_FAILED, NULL);
		return FALSE;
	}

	hResult = m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xFFFF0000, 0.0f, NULL);
	hResult = m_pDevice->Present(NULL, NULL, NULL, NULL);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	return true;
}

/**
* @brief	Destroy device object
* @return	return true if success, otherwise false
* @return	if failed to create, you can check error in the function below
* @see		cMd3dManager::GetLastError()
*/
bool Md3dDeviceControl::DestroyDevice()
{
	if (m_pDevice == NULL)	return false;

	m_pDevice->Release();
	m_pDevice = nullptr;

	return true;
}

bool Md3dDeviceControl::GetAdapterList()
{
	UINT adapterNum = 0;
	D3DADAPTER_IDENTIFIER9	adapterIdentifierList;
	D3DDISPLAYMODE	displayMode;

	ZeroMemory(&adapterIdentifierList, sizeof(D3DADAPTER_IDENTIFIER9));
	ZeroMemory(&displayMode, sizeof(D3DDISPLAYMODE));

	if (m_pD3d == NULL)
	{
		return false;
	}

	adapterNum = m_pD3d->GetAdapterCount();

	for (UINT i = 0; i < adapterNum; i++)
	{
		m_pD3d->GetAdapterIdentifier(i, NULL, &adapterIdentifierList);
		m_pD3d->GetAdapterDisplayMode(i, &displayMode);

		std::string	gpuName;
		gpuName.clear();
		gpuName.assign(adapterIdentifierList.DeviceName);

		bool	isAlreadyAdded = false;
		for (auto i : m_gpuList)
		{
			if (i.compare(gpuName.data()) == 0)
			{
				isAlreadyAdded = true;
				break;
			}
		}

		if (isAlreadyAdded == false)
		{
			m_gpuList.emplace_back(gpuName);
		}

		m_monitorList.emplace_back(displayMode);
	}

	return true;
}

void Md3dDeviceControl::SetDefaultParameter()
{
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferHeight = 1080;
	m_d3dpp.BackBufferWidth = 1920;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
}

void Md3dDeviceControl::LoadData(Md3dDeviceDatas * _datas)
{
	m_initalized = (bool)_datas->m_initialized;
	m_monitorNum = _datas->m_monitorNum;

	SetBackBufferWidth(_datas->m_backBufferWidth);
	SetBackBufferHeight(_datas->m_backBufferHeight);
	SetBackBufferFormat(_datas->m_backBufferFormat);
	SetBackBufferCount(_datas->m_backBufferCount);
	SetMultiSampleType(_datas->m_multiSampleType);
	SetMultiSampleQuality(_datas->m_multiSampleQuality);
	SetSwapEffect(_datas->m_swapEffect);
	SetWindowed(_datas->m_windowed);
	SetEnableAutoDepthStencil(_datas->m_enableAutoDepthStencil);
	SetAutoDepthStencilFormat(_datas->m_autoDepthStencilFormat);
	SetFlags(_datas->m_flags);
	SetFullScreenRefreshRateInHz(_datas->m_fullScreenRefreshRateInHz);
	SetPresentationInterval(_datas->m_presentationInterval);
}

void Md3dDeviceControl::SaveData(Md3dDeviceDatas * _datas)
{
	_datas->m_initialized = (int)m_initalized;
	_datas->m_monitorNum = (int)m_monitorNum;

	_datas->m_backBufferWidth = GetBackBufferWidth();
	_datas->m_backBufferHeight = GetBackBufferHeight();
	_datas->m_backBufferFormat = GetBackBufferFormat();
	_datas->m_backBufferCount = GetBackBufferCount();
	_datas->m_multiSampleType = GetMultiSampleType();
	_datas->m_multiSampleQuality = GetMultiSampleQuality();
	_datas->m_swapEffect = GetSwapEffect();
	_datas->m_windowed = GetWindowed();
	_datas->m_enableAutoDepthStencil = GetEnalbeAutoDepthStencil();
	_datas->m_autoDepthStencilFormat = GetAutoDepthStencilFormat();
	_datas->m_flags = GetFlags();
	_datas->m_fullScreenRefreshRateInHz = GetFullScreenRefreshRateInHz();
	_datas->m_presentationInterval = GetPresentationInterval();
}

/**
* @brief	Set device creation parameters
* @param	D3DPRESENT_PARAMETERS* _pD3dpp source parameters pointer
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresent-parameters
*/
void Md3dDeviceControl::SetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	memcpy(&m_pD3d, _pD3dpp, sizeof(D3DPRESENT_PARAMETERS));
}

/**
* @brief	Get device creation parameters
* @param	D3DPRESENT_PARAMETERS* _pD3dpp result parameters pointer
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresent-parameters
*/
void Md3dDeviceControl::GetDeviceParameter(D3DPRESENT_PARAMETERS * _pD3dpp)
{
	if (_pD3dpp == nullptr)	return;
	memcpy(_pD3dpp, &m_pD3d, sizeof(D3DPRESENT_PARAMETERS));
}

/**
* @brief	Set device back buffer width
* @param	UINT _uValue Width to change
*/
void Md3dDeviceControl::SetBackBufferWidth(UINT _uValue)
{
	m_d3dpp.BackBufferWidth = _uValue;
}

/**
* @brief	Set device back buffer height
* @param	UINT _uValue Height to change
*/
void Md3dDeviceControl::SetBackBufferHeight(UINT _uValue)
{
	m_d3dpp.BackBufferHeight = _uValue;
}

/**
* @brief	Set device back buffer format
* @param	D3DFORMAT _format Buffer format to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
void Md3dDeviceControl::SetBackBufferFormat(D3DFORMAT _format)
{
	m_d3dpp.BackBufferFormat = _format;
}

/**
* @brief	Set device back buffer width
* @param	UINT _uValue Width to change
*/
void Md3dDeviceControl::SetBackBufferCount(UINT _uValue)
{
	m_d3dpp.BackBufferCount = _uValue;
}

/**
* @brief	Set device multi smaple type
* @param	D3DMULTISAMPLE_TYPE _sampleType Sample type to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dmultisample-type
*/
void Md3dDeviceControl::SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType)
{
	m_d3dpp.MultiSampleType = _sampleType;
}

/**
* @brief	Set device multi sample quality
* @param	DWORD _dwQuality Quility to change
*/
void Md3dDeviceControl::SetMultiSampleQuality(DWORD _dwQuality)
{
	m_d3dpp.MultiSampleQuality = _dwQuality;
}

/**
* @brief	Set device swap effect
* @param	D3DSWAPEFFECT _value Swap effect to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dswapeffect
*/
void Md3dDeviceControl::SetSwapEffect(D3DSWAPEFFECT _value)
{
	m_d3dpp.SwapEffect = _value;
}

/**
* @brief	Set device target window handle
* @param	HWND _value Window handle to change
*/
void Md3dDeviceControl::SetHDeviceWindow(HWND _value)
{
	m_d3dpp.hDeviceWindow = _value;
}

/**
* @brief	Set device mode is windowed
* @param	BOOL _value if true, device create by windowed. else if false, device create by fullscreen
*/
void Md3dDeviceControl::SetWindowed(BOOL _value)
{
	m_d3dpp.Windowed = _value;

	if (_value == TRUE)		m_d3dpp.FullScreen_RefreshRateInHz = 0;
	else					m_d3dpp.FullScreen_RefreshRateInHz = m_uFullScreenRefreshRateInHz;
}

/**
* @brief	Set device auto depth stencil
* @param	BOOL _value if true, enalbe auto depth stencil
*/
void Md3dDeviceControl::SetEnableAutoDepthStencil(BOOL _value)
{
	m_d3dpp.EnableAutoDepthStencil = _value;
}

/**
* @brief	Set device auto depth stencil format
* @param	D3DFORMAT _value Buffer format to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
void Md3dDeviceControl::SetAutoDepthStencilFormat(D3DFORMAT _value)
{
	m_d3dpp.AutoDepthStencilFormat = _value;
}

/**
* @brief	Set device create flags
* @param	DWORD _value flags to change
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dpresentflag
*/
void Md3dDeviceControl::SetFlags(DWORD _value)
{
	m_d3dpp.Flags = _value;
}

/**
* @brief	Set device full screen refresh rate to Hz
* @param	UINT _value refresh Hz to change (in fullscreen)
*/
void Md3dDeviceControl::SetFullScreenRefreshRateInHz(UINT _value)
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
void Md3dDeviceControl::SetPresentationInterval(UINT _value)
{
	m_d3dpp.PresentationInterval = _value;
}

/**
* @brief	Get device back buffer width
* @return	return device back buffer width to UINT
*/
UINT Md3dDeviceControl::GetBackBufferWidth()
{
	return m_d3dpp.BackBufferWidth;
}

/**
* @brief	Get device back buffer height
* @return	return device back buffer height to UINT
*/
UINT Md3dDeviceControl::GetBackBufferHeight()
{
	return m_d3dpp.BackBufferHeight;
}

/**
* @brief	Get device back buffer format
* @return	return device back buffer format to D3DFORMAT
* @see		SetBackBufferFormat()
*/
D3DFORMAT Md3dDeviceControl::GetBackBufferFormat()
{
	return m_d3dpp.BackBufferFormat;
}

/**
* @brief	Get device back buffer count
* @return	return device back buffer count to UINT
*/
UINT Md3dDeviceControl::GetBackBufferCount()
{
	return m_d3dpp.BackBufferCount;
}

/**
* @brief	Get device multi sample type
* @return	return device multi sample type to D3DMULTISAMPLE_TYPE
* @see		SetMultiSampleType()
*/
D3DMULTISAMPLE_TYPE Md3dDeviceControl::GetMultiSampleType()
{
	return m_d3dpp.MultiSampleType;
}

/**
* @brief	Get device multi sample quality
* @return	return device multi sample quality to DWORD
* @see		SetMultiSampleQuality()
*/
DWORD Md3dDeviceControl::GetMultiSampleQuality()
{
	return m_d3dpp.MultiSampleQuality;
}

/**
* @brief	Get device swap effect
* @return	return device swap effect to D3DSWAPEFFECT
* @see		SetMultiSampleQuality()
*/
D3DSWAPEFFECT Md3dDeviceControl::GetSwapEffect()
{
	return m_d3dpp.SwapEffect;
}

/**
* @brief	Get device window handle
* @return	return device window handle to HWND
*/
HWND Md3dDeviceControl::GetHwnd()
{
	return m_d3dpp.hDeviceWindow;
}

/**
* @brief	Get device windowed mode
* @return	return device windowed mode width to UINT
*/
BOOL Md3dDeviceControl::GetWindowed()
{
	return m_d3dpp.Windowed;
}

/**
* @brief	Get device auto depth stencil mode enabled
* @return	return device auto depth stencil mode is enable to BOOL
*/
BOOL Md3dDeviceControl::GetEnalbeAutoDepthStencil()
{
	return m_d3dpp.EnableAutoDepthStencil;
}

/**
* @brief	Get device auto depth stencil format
* @return	return device auto depth stencil format to D3DFORMAT
* @see		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dformat
*/
D3DFORMAT Md3dDeviceControl::GetAutoDepthStencilFormat()
{
	return m_d3dpp.AutoDepthStencilFormat;
}

/**
* @brief	Get device flags
* @return	return device flags to D3DFORMAT
*/
DWORD Md3dDeviceControl::GetFlags()
{
	return m_d3dpp.Flags;
}

/**
* @brief	Get device full screen refresh rate in Hz
* @return	return device full screen refresh rate in Hz to UINT
*/
UINT Md3dDeviceControl::GetFullScreenRefreshRateInHz()
{
	return m_uFullScreenRefreshRateInHz;
}

/**
* @brief	Get device presentation interval
* @return	return device presentation interval UINT
*/
UINT Md3dDeviceControl::GetPresentationInterval()
{
	return m_d3dpp.PresentationInterval;
}

/**
	* @brief	Get device pointer
	* @return	return device to LPDIRECT3DDEVICE9
	*/
const LPDIRECT3DDEVICE9 Md3dDeviceControl::GetDevice()
{
	return m_pDevice;
}
