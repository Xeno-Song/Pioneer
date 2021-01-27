#pragma once

#ifndef __C_DX11_DEVICE_H__
#define __C_DX11_DEVICE_H__

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <DXGI.h>
#include <D3Dcommon.h>
#include <D3D11.h>
#include <D3DX10math.h>

#define SAFE_RELEASE(p) { if(p != nullptr){ p->Release(); p = nullptr; }}

namespace pioEngine
{
	class cDx11Device
	{
	public:
		cDx11Device();
		cDx11Device(const cDx11Device&);
		~cDx11Device();

		bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullScreen, float screenDepth, float screenNear);
		void Cleanup();

		void BeginScene(float red, float green, float blue, float alpha);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void GetProjectionMatrix(D3DMATRIX&);
		void GetWorldMatrix(D3DMATRIX&);
		void GetOrthoMatrix(D3DMATRIX&);

		void GetVideoCardInfo(char* cardName, int& memory);

	private:
		bool LoadGraphicCardInfo();
		bool FindRefreshFrequency(int screenWidth, int screenHeight, unsigned int& numerator, unsigned int& denominator);

	private:
		bool	m_vsyncEnable;
		int		m_videoCardMemory;
		char	m_videoCardDescription[128];
		int				m_displayModeNum;
		DXGI_MODE_DESC* m_displayModeList;
		IDXGISwapChain*	m_swapChain;
		ID3D11Device*	m_device;
		ID3D11DeviceContext*	m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D*		m_depthStencilBuffer;
		ID3D11DepthStencilState*	m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState*	m_rasterState;
		D3DXMATRIX	m_projectionMatrix;
		D3DXMATRIX	m_worldMatrix;
		D3DXMATRIX	m_orthoMatrix;
	};
}

#endif