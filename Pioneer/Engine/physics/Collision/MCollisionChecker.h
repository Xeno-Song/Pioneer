#pragma once

#ifndef __M_COLLISION_CHECKER_H__
#define __M_COLLISION_CHECKER_H__

#include "../../sys/thd/cMsysMutexQueue.h"
#include "../Object/MObject.h"
#include "../../Mtypes.h"
#include <utility>
#include <vector>


class MCollisionCheckerCircle
{
public:
	MCollisionCheckerCircle();
	MCollisionCheckerCircle(MsysMutexQueue<std::pair<UID, UID>>* resultQueue);
	virtual ~MCollisionCheckerCircle();

public:
	void CheckThreadJob();
	void CheckCollision(UID first, UID second);

	void SetResultQueue(MsysMutexQueue<std::pair<UID, UID>>* resultQueue);

private:
	MsysMutexQueue<std::pair<unsigned int, unsigned int>>* resultQueue;
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