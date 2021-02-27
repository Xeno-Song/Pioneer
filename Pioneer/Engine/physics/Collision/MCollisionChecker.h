#pragma once

#ifndef __M_COLLISION_CHECKER_H__
#define __M_COLLISION_CHECKER_H__

#include <queue>
#include "../../Object/MObject.h"

class MCollisionCheckerCircle
{
public:
	MCollisionCheckerCircle();
	virtual ~MCollisionCheckerCircle();

public:
	void CheckThreadJob();
	void CheckCollision();
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

private:
	
};

#endif