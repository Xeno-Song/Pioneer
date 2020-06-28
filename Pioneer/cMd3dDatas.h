#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Mio.h"

class cMd3dDatas_Device
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
	cMd3dDatas_Device();
	virtual ~cMd3dDatas_Device();

	void	LoadFromXmlElement(cMioXml_Element* _element);
	void	SaveToXmlElement(cMioXml_Element* _element);
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

	void				SetDeviceData(cMd3dDatas_Device* _data);
	cMd3dDatas_Device*	GetDeviceData();
};

