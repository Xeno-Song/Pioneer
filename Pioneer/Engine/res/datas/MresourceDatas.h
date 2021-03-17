#pragma once

#ifndef __M_RESOURCE_DATAS_H__
#define __M_RESOURCE_DATAS_H__

#include <vector>

class MResourceDatas
{
private:
	class MResDataElement
	{
	public:
		MResDataElement();
		virtual ~MResDataElement();

	public:
		
	};

public:
	MResourceDatas();
	virtual ~MResourceDatas();

public:
	void Initialize();
	void Cleanup();

	void LoadDatas();
	void UnloadDatas();

private:
	std::vector<MResDataElement*> m_dataList;
};

#endif