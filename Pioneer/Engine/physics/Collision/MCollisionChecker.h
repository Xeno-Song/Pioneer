#pragma once

#ifndef __M_COLLISION_CHECKER_H__
#define __M_COLLISION_CHECKER_H__

#include "../../sys/thd/MsysMutexQueue.h"
#include "../Object/MObject.h"
#include "../../Mtypes.h"
#include "../../sys/thd/MsysThreadManager.h"
#include <synchapi.h>
#include <utility>
#include <vector>

class MCollisionCheckerCircle
{
public:
	MCollisionCheckerCircle();
	MCollisionCheckerCircle(MsysMutexQueue<std::pair<UID, UID>>* resultQueue);
	virtual ~MCollisionCheckerCircle();

public:
	void StartCheckThread();
	void SuspendCheckThread();
	// count return count of stopped threads
	// if return false, it end with error
	bool GetStoppedThreadCount(int* count);
	// count return count of stopped threads
	// if return false, it end with error
	bool GetRunningThreadCount(int* count);

	void CheckThreadJob();
	void CheckCollision(UID first, UID second);

	void SetResultQueue(MsysMutexQueue<std::pair<UID, UID>>* resultQueue);

private:
	void Initialize();

private:
	MsysMutexQueue<std::pair<UID, UID>>* resultQueue;

	std::vector<std::pair<MsysThread*, HANDLE>> threadVector;
	//HANDLE threadEndEvent;
};

struct MCollisionCheckerAABBData
{
	unsigned int srcId;
};

class MCollisionCheckerAABB
{
public:
	MCollisionCheckerAABB();
	virtual ~MCollisionCheckerAABB();

public:
	void StartCheckThread();
	void SuspendCheckThread();
};

class MCollisionCheckerManager
{
public:
	MCollisionCheckerManager();
	virtual ~MCollisionCheckerManager();

public:
	void Initialize();
	void Cleanup();

public:
	void StartCollisionCheck();
	void SuspendCollisionCheck();
};

#endif