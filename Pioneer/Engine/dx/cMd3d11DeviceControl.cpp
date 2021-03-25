#include "cMd3d11DeviceControl.h"
#include "../MEngine.h"

Md3dDeviceControl::Md3dDeviceControl()
{
}

Md3dDeviceControl::~Md3dDeviceControl()
{
}

bool Md3dDeviceControl::Cleanup()
{
}

bool Md3dDeviceControl::CreateDevice()
{
	HWND	hwnd = NULL;
	hwnd = MGetSystem()->GetWindowManager()->GetWindowHandle();

	//m_screenWidth = MGetSystem()->GetWindowManager()->Get
	
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;

}

bool Md3dDeviceControl::DestroyDevice()
{
}

bool Md3dDeviceControl::GetAdapterList()
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result)) {
		return false;
	}

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result)) {
		return false;
	}

	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result)) {
		return false;
	}

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result)) {
		return false;
	}

	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList) {
		return false;
	}

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	for (i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == (unsigned int)m_screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)m_screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}
}

void Md3dDeviceControl::SetDefaultParameter()
{
}

void Md3dDeviceControl::SetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp)
{
}

void Md3dDeviceControl::GetDeviceParameter(D3DPRESENT_PARAMETERS* _pD3dpp)
{
}

void Md3dDeviceControl::SetBackBufferWidth(UINT _uValue)
{
}

void Md3dDeviceControl::SetBackBufferHeight(UINT _uValue)
{
}

void Md3dDeviceControl::SetBackBufferFormat(D3DFORMAT _format)
{
}

void Md3dDeviceControl::SetBackBufferCount(UINT _uValue)
{
}

void Md3dDeviceControl::SetMultiSampleType(D3DMULTISAMPLE_TYPE _sampleType)
{
}

void Md3dDeviceControl::SetMultiSampleQuality(DWORD _dwQuality)
{
}

void Md3dDeviceControl::SetSwapEffect(D3DSWAPEFFECT _value)
{
}

void Md3dDeviceControl::SetHDeviceWindow(HWND _value)
{
}

void Md3dDeviceControl::SetWindowed(BOOL _value)
{
}

void Md3dDeviceControl::SetEnableAutoDepthStencil(BOOL _value)
{
}

void Md3dDeviceControl::SetAutoDepthStencilFormat(D3DFORMAT _value)
{
}

void Md3dDeviceControl::SetFlags(DWORD _value)
{
}

void Md3dDeviceControl::SetFullScreenRefreshRateInHz(UINT _value)
{
}

void Md3dDeviceControl::SetPresentationInterval(UINT _value)
{
}

UINT Md3dDeviceControl::GetBackBufferWidth()
{
}

UINT Md3dDeviceControl::GetBackBufferHeight()
{
}

D3DFORMAT Md3dDeviceControl::GetBackBufferFormat()
{
}

UINT Md3dDeviceControl::GetBackBufferCount()
{
}

D3DMULTISAMPLE_TYPE Md3dDeviceControl::GetMultiSampleType()
{
}

DWORD Md3dDeviceControl::GetMultiSampleQuality()
{
}

D3DSWAPEFFECT Md3dDeviceControl::GetSwapEffect()
{
}

HWND Md3dDeviceControl::GetHwnd()
{
}

BOOL Md3dDeviceControl::GetWindowed()
{
}

BOOL Md3dDeviceControl::GetAutoDepthStencilEnable()
{
}

D3DFORMAT Md3dDeviceControl::GetAutoDepthStencilFormat()
{
}

DWORD Md3dDeviceControl::GetFlags()
{
}

UINT Md3dDeviceControl::GetFullScreenRefreshRateInHz()
{
}

UINT Md3dDeviceControl::GetPresentationInterval()
{
}

const LPDIRECT3DDEVICE9 Md3dDeviceControl::GetDevice()
{
}
