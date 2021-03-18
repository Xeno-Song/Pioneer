#pragma once

#ifndef __M_RESOURCE_DATAS_H__
#define __M_RESOURCE_DATAS_H__

#include <vector>
#include "../../io/xml/cMioXmlSerializer.h"

class MResourceDatas
{
public:
	MResourceDatas();
	virtual ~MResourceDatas();

public:
	void Initialize();
	void Cleanup();

	void LoadDatas();
	void UnloadDatas();

private:
	cMioXmlSerializer* m_dataSerializer;
};

#endif