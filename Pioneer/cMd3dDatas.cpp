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

void cMd3dDatas_Device::SetParameters(cMd3dDeviceControl* _pDeviceControl)
{
	_pDeviceControl->SetBackBufferWidth(m_backBufferWidth);
	_pDeviceControl->SetBackBufferHeight(m_backBufferHeight);
	_pDeviceControl->SetBackBufferFormat(m_backBufferFormat);
	_pDeviceControl->SetBackBufferCount(m_backBufferCount);
	_pDeviceControl->SetMultiSampleType(m_multiSampleType);
	_pDeviceControl->SetMultiSampleQuality(m_multiSampleQuality);
	_pDeviceControl->SetSwapEffect(m_swapEffect);
	_pDeviceControl->SetWindowed(m_windowed);
	_pDeviceControl->SetEnableAutoDepthStencil(m_enableAutoDepthStencil);
	_pDeviceControl->SetAutoDepthStencilFormat(m_autoDepthStencilFormat);
	_pDeviceControl->SetFlags(m_flags);
	_pDeviceControl->SetFullScreenRefreshRateInHz(m_fullScreenRefreshRateInHz);
	_pDeviceControl->SetPresentationInterval(m_presentationInterval);
}

void cMd3dDatas_Device::GetParameters(cMd3dDeviceControl * _pDeviceControl)
{
	m_backBufferWidth			= _pDeviceControl->GetBackBufferWidth();
	m_backBufferHeight			= _pDeviceControl->GetBackBufferHeight();
	m_backBufferFormat			= _pDeviceControl->GetBackBufferFormat();
	m_backBufferCount			= _pDeviceControl->GetBackBufferCount();
	m_multiSampleType			= _pDeviceControl->GetMultiSampleType();
	m_multiSampleQuality		= _pDeviceControl->GetMultiSampleQuality();
	m_swapEffect				= _pDeviceControl->GetSwapEffect();
	m_windowed					= _pDeviceControl->GetWindowed();
	m_enableAutoDepthStencil	= _pDeviceControl->GetEnalbeAutoDepthStencil();
	m_autoDepthStencilFormat	= _pDeviceControl->GetAutoDepthStencilFormat();
	m_flags						= _pDeviceControl->GetFlags();
	m_fullScreenRefreshRateInHz = _pDeviceControl->GetFullScreenRefreshRateInHz();
	m_presentationInterval		= _pDeviceControl->GetPresentationInterval();
}
