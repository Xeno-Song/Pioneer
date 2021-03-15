#pragma once

#ifndef __M_OBJECT_MANAGER_H__
#define __M_OBJECT_MANAGER_H__

#include <map>
#include <vector>
#include <mutex>
#include "MObject.h"

class MObjectManager
{
public:
	MObjectManager();
	virtual ~MObjectManager();

public:
	void RegisterNewObject(MObject* obj, UID uid);
	void UnregisterObject(UID uid);
	unsigned int CreateNewUID();
	void Cleanup();

	std::vector<UID>* GetUidVector();
	MObject* GetObjectByUID(UID uid);

	void LockDelMutex();
	void UnlockDelMutex();

private:
	std::map<UID, MObject*>	m_objectMap;
	unsigned int	m_uidCount;

	std::mutex	m_uidCountMutex;
	std::mutex	m_objMapDelMutex;
};

#endif