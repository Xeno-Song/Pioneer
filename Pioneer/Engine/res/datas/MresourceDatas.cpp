#include "MresourceDatas.h"

MResourceDatas::MResourceDatas()
{
}

MResourceDatas::~MResourceDatas()
{
}

void MResourceDatas::Initialize()
{
	m_dataSerializer->XmlSetFilePath(
		std::wstring(L"./"));
}

void MResourceDatas::Cleanup()
{
}

void MResourceDatas::LoadDatas()
{
}

void MResourceDatas::UnloadDatas()
{
}
