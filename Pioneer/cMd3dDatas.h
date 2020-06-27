#pragma once
#include "Mio.h"
#include "cMd3dDeviceControl.h"

class cMd3dDatas_Device
{
public:
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
	cMd3dDatas_Device();
	virtual ~cMd3dDatas_Device();

	void	LoadFromXmlElement(cMioXml_Element* _element);
	void	SaveToXmlElement(cMioXml_Element* _element);

	void	SetParameters(cMd3dDeviceControl* _pDeviceControl);
	void	GetParameters(cMd3dDeviceControl* _pDeviceControl);
};

class cMd3dDatas : public cMioXmlSerializer
{
public:
	cMd3dDatas_Device*	m_deviceData;

public:
	cMd3dDatas();
	virtual ~cMd3dDatas();

	void	LoadAll();
	void	SaveAll();

	void	LoadDeviceData();
	void	SaveDeviceData();
};

