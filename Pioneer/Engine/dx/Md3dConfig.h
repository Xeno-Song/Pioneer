#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include <Mio.h>

class Md3dDeviceConfig final
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
	Md3dDeviceConfig();
	~Md3dDeviceConfig();

	void	LoadFromXmlElement(cMioXml_Element* _element);
	void	SaveToXmlElement(cMioXml_Element* _element) const;
};

class Md3dGlobalConfig final
{
public:
	bool	m_useDx11;

public:
	Md3dGlobalConfig();
	~Md3dGlobalConfig();

	void LoadFromXmlElement(cMioXml_Element* element);
	void SaveToXmlElement(cMioXml_Element* element) const;
};

class Md3dConfig : public cMioXmlSerializer
{
public:
	Md3dGlobalConfig*	m_globalConfig;
	Md3dDeviceConfig*	m_deviceConfig;

public:
	Md3dConfig();
	virtual ~Md3dConfig();

	void	LoadAll();
	void	SaveAll();

	void	LoadDeviceData();
	void	SaveDeviceData();

	void	SetDeviceConfig(Md3dDeviceConfig* config);
	void	SetGlobalConfig(Md3dGlobalConfig* config);
	
	Md3dGlobalConfig*   GetGlobalConfig();
	Md3dDeviceConfig*	GetDeviceConfig();
};

