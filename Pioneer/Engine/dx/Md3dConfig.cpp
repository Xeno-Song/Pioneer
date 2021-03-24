#include "Md3dData.h"


Md3dData::Md3dData()
{
	wchar_t buffer[256] = { 0 };
	std::wstring	filePath;
	filePath.clear();

	GetCurrentDirectoryW(256, buffer);
	filePath.assign(buffer);

	filePath.append(L"\\d3d.xml");
	XmlInitialize(filePath, L"DirectX");

	m_deviceData = new Md3dDeviceData();
}

Md3dData::~Md3dData()
{
	delete m_deviceData;
}

void Md3dData::LoadAll()
{
	LoadDeviceData();
}

void Md3dData::SaveAll()
{
	SaveDeviceData();

	XmlWrite();
}

void Md3dData::LoadDeviceData()
{
	cMioXml_Element*	deviceElement = nullptr;
	deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);

	m_deviceData->LoadFromXmlElement(deviceElement);
}

void Md3dData::SaveDeviceData()
{
	cMioXml_Element*	deviceElement = nullptr;
	deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);

	m_deviceData->SaveToXmlElement(deviceElement);
}

void Md3dData::SetDeviceData(Md3dDeviceData * _data)
{
}

Md3dDeviceData * Md3dData::GetDeviceData()
{
	return nullptr;
}

Md3dDeviceData::Md3dDeviceData()
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

Md3dDeviceData::~Md3dDeviceData()
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

void Md3dDeviceData::LoadFromXmlElement(cMioXml_Element * _element)
{
	m_initialized				= _element->GetSubElementNode(L"initialized", true)->GetValueToInt();
	m_monitorNum				= _element->GetSubElementNode(L"monitorNum", true)->GetValueToInt();

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

void Md3dDeviceData::SaveToXmlElement(cMioXml_Element * _element) const
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
	_element->GetSubElementNode(L"fullScreenRefreshRateInHz", true)->SetValue((int)m_fullScreenRefreshRateInHz);
	_element->GetSubElementNode(L"presentationInterval", true)->SetValue((int)m_presentationInterval);
}

Md3dGlobalConfig::Md3dGlobalConfig()
	:m_useDx11(false)
{
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
