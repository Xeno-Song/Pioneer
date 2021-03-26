#include "Md3dConfig.h"


Md3dConfig::Md3dConfig()
{
	wchar_t buffer[256] = { 0 };
	std::wstring	filePath;
	filePath.clear();

	GetCurrentDirectoryW(256, buffer);
	filePath.assign(buffer);

	filePath.append(L"\\d3d.xml");
	XmlInitialize(filePath, L"DirectX");

	m_deviceConfig = new Md3dDeviceConfig();
	m_globalConfig = new Md3dGlobalConfig();
}

Md3dConfig::~Md3dConfig()
{
	delete m_deviceConfig;
}

void Md3dConfig::LoadAll()
{
	LoadDeviceData();
}

void Md3dConfig::SaveAll()
{
	SaveDeviceData();

	XmlWrite();
}

void Md3dConfig::LoadDeviceData()
{
	cMioXml_Element* deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);
	m_deviceConfig->LoadFromXmlElement(deviceElement);
}

void Md3dConfig::SaveDeviceData()
{
	cMioXml_Element* deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);
	m_deviceConfig->SaveToXmlElement(deviceElement);
}

void Md3dConfig::SetDeviceConfig(Md3dDeviceConfig * config)
{
	m_deviceConfig = config;
}

Md3dDeviceConfig * Md3dConfig::GetDeviceConfig() const
{
	return m_deviceConfig;
}

Md3dDeviceConfig::Md3dDeviceConfig()
{
	m_initialized = false;

	m_monitorNum = 0;
	m_backBufferWidth = NULL;
	m_backBufferHeight = NULL;
	m_backBufferFormat = D3DFORMAT();
	m_backBufferCount = NULL;
	m_multiSampleType = D3DMULTISAMPLE_TYPE();
	m_multiSampleQuality = NULL;
	m_swapEffect = D3DSWAPEFFECT();
	m_windowed = NULL;
	m_enableAutoDepthStencil = NULL;
	m_autoDepthStencilFormat = D3DFORMAT();
	m_flags = NULL;
	m_vSync = NULL;
	m_fullScreenRefreshRateInHz = NULL;
	m_fullScreen = NULL;
	m_presentationInterval = NULL;
}

Md3dDeviceConfig::~Md3dDeviceConfig()
{
	m_backBufferWidth = NULL;
	m_backBufferHeight = NULL;
	m_backBufferFormat = D3DFORMAT();
	m_backBufferCount = NULL;
	m_multiSampleType = D3DMULTISAMPLE_TYPE();
	m_multiSampleQuality = NULL;
	m_swapEffect = D3DSWAPEFFECT();
	m_windowed = NULL;
	m_enableAutoDepthStencil = NULL;
	m_autoDepthStencilFormat = D3DFORMAT();
	m_flags = NULL;
	m_fullScreenRefreshRateInHz = NULL;
	m_presentationInterval = NULL;
}

void Md3dDeviceConfig::LoadFromXmlElement(cMioXml_Element * _element)
{
	m_initialized				= _element->GetSubElementNode(L"initialized", true)->GetValueToInt();
	m_monitorNum				= _element->GetSubElementNode(L"monitorNum", true)->GetValueToInt();

	m_vSync						= _element->GetSubElementNode(L"vSync", true)->GetValueToInt();
	m_fullScreen				= _element->GetSubElementNode(L"fullScreen", true)->GetValueToInt();
	m_backBufferWidth			= _element->GetSubElementNode(L"backBufferWidth", true)->GetValueToInt();
	m_backBufferHeight			= _element->GetSubElementNode(L"backBufferHeight", true)->GetValueToInt();
	m_backBufferFormat			= (D3DFORMAT)_element->GetSubElementNode(L"backBufferFormat", true)->GetValueToInt();
	m_backBufferCount			= _element->GetSubElementNode(L"backBufferCount", true)->GetValueToInt();
	m_multiSampleType			= (D3DMULTISAMPLE_TYPE)_element->GetSubElementNode(L"multiSampleType", true)->GetValueToInt();
	m_multiSampleQuality		= _element->GetSubElementNode(L"multiSampleQuality", true)->GetValueToInt();
	m_swapEffect				= (D3DSWAPEFFECT)_element->GetSubElementNode(L"swapEffect", true)->GetValueToInt();
	m_windowed					= _element->GetSubElementNode(L"windowed", true)->GetValueToInt();
	m_enableAutoDepthStencil	= _element->GetSubElementNode(L"enableAutoDepthStencil", true)->GetValueToInt();
	m_autoDepthStencilFormat	= (D3DFORMAT)_element->GetSubElementNode(L"autoDepthStencilFormat", true)->GetValueToInt();
	m_flags						= _element->GetSubElementNode(L"flags", true)->GetValueToInt();
	m_fullScreenRefreshRateInHz	= _element->GetSubElementNode(L"fullScreenRefreshRateInHz", true)->GetValueToInt();
	m_presentationInterval		= _element->GetSubElementNode(L"presentationInterval", true)->GetValueToInt();


}

void Md3dDeviceConfig::SaveToXmlElement(cMioXml_Element * _element) const
{
	_element->GetSubElementNode(L"initialized", true)->SetValue(m_initialized);
	_element->GetSubElementNode(L"monitorNum", true)->SetValue(m_monitorNum);

	_element->GetSubElementNode(L"backBufferWidth", true)->SetValue((int)m_backBufferWidth);
	_element->GetSubElementNode(L"backBufferHeight", true)->SetValue((int)m_backBufferHeight);
	_element->GetSubElementNode(L"backBufferFormat", true)->SetValue((int)m_backBufferFormat);
	_element->GetSubElementNode(L"backBufferCount", true)->SetValue((int)m_backBufferCount);
	_element->GetSubElementNode(L"multiSampleType", true)->SetValue((int)m_multiSampleType);
	_element->GetSubElementNode(L"multiSampleQuality", true)->SetValue((int)m_multiSampleQuality);
	_element->GetSubElementNode(L"swapEffect", true)->SetValue((int)m_swapEffect);
	_element->GetSubElementNode(L"windowed", true)->SetValue((int)m_windowed);
	_element->GetSubElementNode(L"enableAutoDepthStencil", true)->SetValue((int)m_enableAutoDepthStencil);
	_element->GetSubElementNode(L"autoDepthStencilFormat", true)->SetValue((int)m_autoDepthStencilFormat);
	_element->GetSubElementNode(L"flags", true)->SetValue((int)m_flags);
	_element->GetSubElementNode(L"vSync", true)->SetValue((int)m_vSync);
	_element->GetSubElementNode(L"fullScreen", true)->SetValue((int)m_fullScreen);
	_element->GetSubElementNode(L"fullScreenRefreshRateInHz", true)->SetValue((int)m_fullScreenRefreshRateInHz);
	_element->GetSubElementNode(L"presentationInterval", true)->SetValue((int)m_presentationInterval);
}

Md3dGlobalConfig::Md3dGlobalConfig()
{
	m_useDx11 = false;
}

Md3dGlobalConfig::~Md3dGlobalConfig()
{
	m_useDx11 = false;
}

void Md3dGlobalConfig::LoadFromXmlElement(cMioXml_Element* element)
{
	m_useDx11 = element->GetSubElementNode(L"useDx11", true)->GetValueToInt();
}

void Md3dGlobalConfig::SaveToXmlElement(cMioXml_Element* element) const
{
	element->GetSubElementNode(L"useDx11", true)->SetValue(m_useDx11);
}
