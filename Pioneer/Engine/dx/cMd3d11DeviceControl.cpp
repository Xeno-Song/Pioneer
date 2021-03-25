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
	auto *windowManager = MGetSystem()->GetWindowManager();
	auto hwnd = windowManager->GetWindowHandle();
	
	m_screenWidth = windowManager->GetScreenWidth();
	m_screenHeight = windowManager->GetScreenHeight();
	
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

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = m_screenWidth;
	swapChainDesc.BufferDesc.Height = m_screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
	if () {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (fullscreen) {
		swapChainDesc.Windowed = false;
	}
	else {
		swapChainDesc.Windowed = true;
	}
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
}

bool Md3dDeviceControl::DestroyDevice()
{
}

bool Md3dDeviceControl::GetAdapterList()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, stringLength, numerator, denominator;
	DXGI_ADAPTER_DESC adapterDesc;
	
	auto result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result)) return false;

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))	return false;

	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))	return false;

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))	return false;

	auto *displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList) return false;

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
		return false;

	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == m_screenWidth)
		{
			if (displayModeList[i].Height == m_screenHeight)
			{
				m_numerator = displayModeList[i].RefreshRate.Numerator;
				m_denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result)) return false;
	
	m_videoCardMemory = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	m_gpuList.emplace_back(std::wstring(adapterDesc.Description));

	SAFE_DELETE_ARR(displayModeList);
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);

	return true;
}

void Md3dDeviceControl::SetDefaultParameter()
{
}

void Md3dDeviceControl::LoadData(Md3dDeviceConfig* config)
{
	m_vSync = config->m_vSync;
	m_fullScreen = config->m_fullScreen;
}

void Md3dDeviceControl::SaveData(Md3dDeviceConfig* config) const
{
	config->m_vSync = m_vSync;
	config->m_fullScreen = m_fullScreen;
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
