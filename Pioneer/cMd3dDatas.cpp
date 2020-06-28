#include "cMd3dDatas.h"


cMd3dDatas::cMd3dDatas()
{
	wchar_t buffer[256] = { 0 };
	std::wstring	filePath;
	filePath.clear();

	GetCurrentDirectoryW(256, buffer);
	filePath.assign(buffer);

	filePath.append(L"\\d3d.xml");
	XmlInitialize(filePath.data(), L"DirectX");

	m_deviceData = new cMd3dDatas_Device();
}

cMd3dDatas::~cMd3dDatas()
{
	delete m_deviceData;
}

void cMd3dDatas::LoadAll()
{
	LoadDeviceData();
}

void cMd3dDatas::SaveAll()
{
	SaveDeviceData();

	XmlWrite();
}

void cMd3dDatas::LoadDeviceData()
{
	cMioXml_Element*	deviceElement = nullptr;
	deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);

	m_deviceData->LoadFromXmlElement(deviceElement);
}

void cMd3dDatas::SaveDeviceData()
{
	cMioXml_Element*	deviceElement = nullptr;
	deviceElement = XmlGetRootElement()->GetElementNode(L"deviceControl", true);

	m_deviceData->SaveToXmlElement(deviceElement);
}

void cMd3dDatas::SetDeviceData(cMd3dDatas_Device * _data)
{
}

cMd3dDatas_Device * cMd3dDatas::GetDeviceData()
{
	return nullptr;
}

cMd3dDatas_Device::cMd3dDatas_Device()
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

cMd3dDatas_Device::~cMd3dDatas_Device()
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

void cMd3dDatas_Device::LoadFromXmlElement(cMioXml_Element * _element)
{
	m_initialized				= _element->GetSubElementNode(L"initalized", true)->GetValueToInt();
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

void cMd3dDatas_Device::SaveToXmlElement(cMioXml_Element * _element)
{
	_element->GetSubElementNode(L"initalized", true)->SetValue(m_initialized);
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
