#include "cDx11Device.h"

namespace pioEngine
{
    cDx11Device::cDx11Device()
    {
        m_displayModeList = nullptr;
        m_swapChain = 0;
        m_device = 0;
        m_deviceContext = 0;
        m_renderTargetView = 0;
        m_depthStencilBuffer = 0;
        m_depthStencilState = 0;
        m_depthStencilView = 0;
        m_rasterState = 0;
    }

    cDx11Device::cDx11Device(const cDx11Device&)
    {
    }

    cDx11Device::~cDx11Device()
    {
    }

    bool cDx11Device::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear)
    {
        HRESULT result;
        unsigned int numerator, denominator;
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

        m_vsyncEnable = vsync;

        if (LoadGraphicCardInfo() == false)
            return false;
        if (FindRefreshFrequency(screenWidth, screenHeight, numerator, denominator) == false)
            return false;

        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
        swapChainDesc.BufferCount = 1;

        swapChainDesc.BufferDesc.Width = screenWidth;
        swapChainDesc.BufferDesc.Height = screenHeight;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        if (m_vsyncEnable)
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
        }
        else
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        }

        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hwnd;

        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;

        if (fullScreen)
            swapChainDesc.Windowed = false;
        else
            swapChainDesc.Windowed = true;

        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags = 0;

        featureLevel = D3D_FEATURE_LEVEL_11_0;

        result = D3D11CreateDeviceAndSwapChain(
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            0,
            &featureLevel,
            1,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &m_swapChain,
            &m_device,
            NULL,
            &m_deviceContext
        );
        if (FAILED(result))
            return false;

        result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
        if (FAILED(result))
            return false;

        result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
        if (FAILED(result))
            return false;

        backBufferPtr->Release();
        backBufferPtr = nullptr;

        ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
        depthBufferDesc.Width = screenWidth;
        depthBufferDesc.Height = screenHeight;
        depthBufferDesc.MipLevels = 1;
        depthBufferDesc.ArraySize = 1;
        depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.SampleDesc.Count = 1;
        depthBufferDesc.SampleDesc.Quality = 0;
        depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthBufferDesc.CPUAccessFlags = 0;
        depthBufferDesc.MiscFlags = 0;

        result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
        if (FAILED(result))
            return false;

        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

        // Write stencil state description
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
        if (FAILED(result))
            return false;

        m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        result = m_device->CreateDepthStencilView(
            m_depthStencilBuffer,
            &depthStencilViewDesc,
            &m_depthStencilView
        );
        if (FAILED(result))
            return false;

        m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

        //Raterizer state setting
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
        if(FAILED(result))
            return false;
        m_deviceContext->RSSetState(m_rasterState);

        viewport.Width = (float)screenWidth;
        viewport.Height = (float)screenHeight;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;
        m_deviceContext->RSSetViewports(1, &viewport);

        //FOV, Screen aspect ratio (like 4:3, 16:9)
        fieldOfView = (float)D3DX_PI / 4.0f;
        screenAspect = (float)screenWidth / (float)screenHeight;
        D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

        D3DXMatrixIdentity(&m_worldMatrix);
        D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

        return true;
    }

    void cDx11Device::Cleanup()
    {
        if (m_displayModeList != nullptr)
        {
            delete[] m_displayModeList;
            m_displayModeList = NULL;
        }

        if (m_swapChain != nullptr)
        {
            m_swapChain->SetFullscreenState(false, NULL);
        }

        SAFE_RELEASE(m_rasterState);
        SAFE_RELEASE(m_depthStencilView);
        SAFE_RELEASE(m_depthStencilState);
        SAFE_RELEASE(m_depthStencilBuffer);
        SAFE_RELEASE(m_renderTargetView);
        SAFE_RELEASE(m_deviceContext);
        SAFE_RELEASE(m_device);
        SAFE_RELEASE(m_swapChain);
    }

    void cDx11Device::BeginScene(float red, float green, float blue, float alpha)
    {
        float color[4];

        color[0] = red;
        color[1] = green;
        color[2] = blue;
        color[3] = alpha;

        m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
        m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

        return;
    }

    void cDx11Device::EndScene()
    {
        if (m_vsyncEnable)
        {
            m_swapChain->Present(1, 0);
        }
        else
        {
            m_swapChain->Present(0, 0);
        }

        return;
    }

    ID3D11Device* cDx11Device::GetDevice()
    {
        return m_device;
    }

    ID3D11DeviceContext* cDx11Device::GetDeviceContext()
    {
        return m_deviceContext;
    }

    void cDx11Device::GetProjectionMatrix(D3DMATRIX& projectionMatrix)
    {
        projectionMatrix = m_projectionMatrix;
    }

    void cDx11Device::GetWorldMatrix(D3DMATRIX& worldMatrix)
    {
        worldMatrix = m_worldMatrix;
    }

    void cDx11Device::GetOrthoMatrix(D3DMATRIX& orthoMatrix)
    {
        orthoMatrix = m_orthoMatrix;
    }

    void cDx11Device::GetVideoCardInfo(char* cardName, int& memory)
    {
        strcpy_s(cardName, 128, m_videoCardDescription);
        memory = m_videoCardMemory;
        return;
    }

    bool cDx11Device::LoadGraphicCardInfo()
    {
        HRESULT result;
        IDXGIFactory* factory;
        IDXGIAdapter* adapter;
        IDXGIOutput* adapterOutput;
        unsigned int numModes, i, numerator, denominator;
        size_t stringLength;
        DXGI_ADAPTER_DESC adapterDesc;

        result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        if (FAILED(result))
            return false;

        result = factory->EnumAdapters(0, &adapter);
        if (FAILED(result))
            return false;

        result = adapter->EnumOutputs(0, &adapterOutput);
        if (FAILED(result))
            return false;

        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
        if (FAILED(result))
            return false;

        m_displayModeNum = numModes;
        m_displayModeList = new DXGI_MODE_DESC[numModes];
        if (m_displayModeList == nullptr)
            return false;

        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, m_displayModeList);
        if (FAILED(result))
            return false;

        result = adapter->GetDesc(&adapterDesc);
        if (FAILED(result))
            return false;

        int error;
        m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
        error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);

        adapterOutput->Release();
        adapter->Release();
        factory->Release();

        adapterOutput = nullptr;
        adapter = nullptr;
        factory = 0;

        return true;
    }

    bool cDx11Device::FindRefreshFrequency(int screenWidth, int screenHeight, unsigned int& numerator, unsigned int& denominator)
    {
        bool result = false;

        if (m_displayModeList == nullptr)
        {
            result = LoadGraphicCardInfo();
            if (result == false)
                return false;
        }

        for (unsigned int i = 0; i < m_displayModeNum; i++)
        { 
            if (m_displayModeList[i].Width == (unsigned int)screenWidth)
            {
                if (m_displayModeList[i].Height == (unsigned int)screenHeight)
                {
                    numerator = m_displayModeList[i].RefreshRate.Numerator;
                    denominator = m_displayModeList[i].RefreshRate.Denominator;

                    return true;
                }
            }
        }

        return false;
    }
}