#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "../io/Mio.h"

class Md3dDeviceDatas
{
public:
	int		m_initialized;
	int		m_monitorNum;

	UINT				m_backBufferWidth;
	UINT				m_backBufferHeight;
	D3DFORMAT			m_backBufferFormat;
	UINT				m_backBufferCount;
	D3DMULTISAMPLE_TYPE	m_multiSampleType;
	DWORD				m_multiSampleQuality;
	D3DSWAPEFFECT		m_swapEffect;
	BOOL				m_windowed;
	BOOL				m_enableAutoDepthStencil;
	D3DFORMAT			m_autoDepthStencilFormat;
	DWORD				m_flags;
	UINT				m_fullScreenRefreshRateInHz;
	UINT				m_presentationInterval;

public:
	Md3dDeviceDatas();
	virtual ~Md3dDeviceDatas();

	void	LoadFromXmlElement(cMioXml_Element* _element);
	void	SaveToXmlElement(cMioXml_Element* _element);
};

class cMd3dDatas : public cMioXmlSerializer
{
public:
	Md3dDeviceDatas*	m_deviceData;

public:
	cMd3dDatas();
	virtual ~cMd3dDatas();

	void	LoadAll();
	void	SaveAll();

	void	LoadDeviceData();
	void	SaveDeviceData();

	void				SetDeviceData(Md3dDeviceDatas* _data);
	Md3dDeviceDatas*	GetDeviceData();
};

