#pragma once

#ifndef __M_OBJECT_MANAGER_H__
#define __M_OBJECT_MANAGER_H__

#include <map>
#include <mutex>
#include "MObject.h"

class MObjectManager
{
public:
	MObjectManager();
	virtual ~MObjectManager();

public:
	void RegisterNewObject(MObject* obj, int uid);
	void UnregisterObject(int uid);
	unsigned int CreateNewUID();

private:
	std::map<unsigned int, MObject*>	m_objectMap;
	unsigned int	m_uidCount;

	std::mutex	m_uidCountMutex;
	std::mutex	m_objMapDelMutex;
};

#endif