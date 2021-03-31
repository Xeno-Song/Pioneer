#include "../Mdefines.h"

#ifdef __DX_VERSION_11__
#include "../MEngine.h"
#include "cMd3d11DeviceControl.h"

Md3dDeviceControl::Md3dDeviceControl()
{
	m_config = nullptr;
	m_vSync = false;
	m_fullScreen = false;

	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilBuffer = nullptr;
	m_depthStencilState = nullptr;
	m_depthStencilView = nullptr;
	m_rasterState = nullptr;
	m_projectionMatrix = D3DMATRIX();
	m_worldMatrix = D3DMATRIX();
	m_orthoMatrix = D3DMATRIX();

	m_gpuList.clear();
	m_monitorList.clear();

	m_initialized = false;
	m_monitorNum = 0;
	m_fullScreenRefreshRateInHz = 0;
	m_numerator = 0;
	m_denominator = 0;
	m_videoCardMemory = 0;
	m_screenWidth = 0;
	m_screenHeight = 0;
}

Md3dDeviceControl::~Md3dDeviceControl()
{
	Cleanup();
}

bool Md3dDeviceControl::Cleanup()
{
	DestroyDevice();

	m_config = nullptr;
	m_vSync = false;
	m_fullScreen = false;

	m_swapChain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_renderTargetView = nullptr;
	m_depthStencilBuffer = nullptr;
	m_depthStencilState = nullptr;
	m_depthStencilView = nullptr;
	m_rasterState = nullptr;
	m_projectionMatrix = D3DMATRIX();
	m_worldMatrix = D3DMATRIX();
	m_orthoMatrix = D3DMATRIX();

	m_gpuList.clear();
	m_monitorList.clear();

	m_initialized = false;
	m_monitorNum = 0;
	m_fullScreenRefreshRateInHz = 0;
	m_numerator = 0;
	m_denominator = 0;
	m_videoCardMemory = 0;
	m_screenWidth = 0;
	m_screenHeight = 0;
	
	return true;
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
	
	if (m_vSync) {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = m_numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = m_denominator;
	}
	else {
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (m_fullScreen) {
		swapChainDesc.Windowed = false;
	}
	else {
		swapChainDesc.Windowed = true;
	}
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	featureLevel = D3D_FEATURE_LEVEL_11_0;
	auto result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, nullptr, &m_deviceContext);
	if (FAILED(result))
		return false;

	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
		return false;

	result = m_device->CreateRenderTargetView(backBufferPtr, nullptr, &m_renderTargetView);
	if(FAILED(result))
		return false;
	backBufferPtr->Release();
	backBufferPtr = nullptr;

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = m_screenWidth;
	depthBufferDesc.Height = m_screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer);
	if (FAILED(result))
		return false;

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	// Write stencil buffer description
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result)) return false;

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	// Write depth-stencil view's description
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	// Create depth-stencil buffer
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result)) return false;

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result)) return false;
	m_deviceContext->RSSetState(m_rasterState);

	viewport.Width = (float)m_screenWidth;
	viewport.Height = (float)m_screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	m_deviceContext->RSSetViewports(1, &viewport);

	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)m_screenWidth / (float)m_screenHeight;
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, DX_SCREEN_NEAR_CONST, DX_SCREEN_DEPTH_CONST);

	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixOrthoLH(&m_orthoMatrix, (float)m_screenWidth, (float)m_screenHeight, DX_SCREEN_NEAR_CONST, DX_SCREEN_DEPTH_CONST);

	return true;
}

bool Md3dDeviceControl::DestroyDevice()
{
	if (m_swapChain != nullptr)
		m_swapChain->SetFullscreenState(false, nullptr);
	
	SAFE_RELEASE(m_rasterState);
	SAFE_RELEASE(m_depthStencilView);
	SAFE_RELEASE(m_depthStencilState);
	SAFE_RELEASE(m_depthStencilBuffer);
	SAFE_RELEASE(m_renderTargetView);
	SAFE_RELEASE(m_deviceContext);
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_swapChain);
	
	return false;
}

bool Md3dDeviceControl::GetAdapterList()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes;
	DXGI_ADAPTER_DESC adapterDesc;
	
	auto result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result)) return false;

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))	return false;

	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))	return false;

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
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
	
	m_videoCardMemory = adapterDesc.DedicatedVideoMemory / (1024 * 1024);
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
	m_numerator = config->m_numerator;
	m_denominator = config->m_denominator;
}

void Md3dDeviceControl::SaveData(Md3dDeviceConfig* config) const
{
	config->m_vSync = m_vSync;
	config->m_fullScreen = m_fullScreen;
	config->m_numerator = m_numerator;
	config->m_denominator = m_denominator;
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
	return 0;
}

UINT Md3dDeviceControl::GetBackBufferHeight()
{
	return 0;
}

D3DFORMAT Md3dDeviceControl::GetBackBufferFormat()
{
	return D3DFORMAT();
}

UINT Md3dDeviceControl::GetBackBufferCount()
{
	return 0;
}

D3DMULTISAMPLE_TYPE Md3dDeviceControl::GetMultiSampleType()
{
	return D3DMULTISAMPLE_TYPE();
}

DWORD Md3dDeviceControl::GetMultiSampleQuality()
{
	return 0;
}

D3DSWAPEFFECT Md3dDeviceControl::GetSwapEffect()
{
	return D3DSWAPEFFECT();
}

HWND Md3dDeviceControl::GetHwnd()
{
	return 0;
}

BOOL Md3dDeviceControl::GetWindowed()
{
	return 0;
}

BOOL Md3dDeviceControl::GetAutoDepthStencilEnable()
{
	return 0;
}

D3DFORMAT Md3dDeviceControl::GetAutoDepthStencilFormat()
{
	return D3DFORMAT();
}

DWORD Md3dDeviceControl::GetFlags()
{
	return 0;
}

UINT Md3dDeviceControl::GetFullScreenRefreshRateInHz()
{
	return 0;
}

UINT Md3dDeviceControl::GetPresentationInterval()
{
	return 0;
}

//const LPDIRECT3DDEVICE9 Md3dDeviceControl::GetDevice()
//{
//}

#endif