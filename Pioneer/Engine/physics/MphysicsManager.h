#pragma once

#ifndef __M_PHYSICS_MANAGER_H__

#include "Object/MObjectManager.h"
#include "Collision/MCollisionChecker.h"

class MphysicsManager
{
public:
	MphysicsManager();
	virtual ~MphysicsManager();

public:
	void Initialize();
	void Cleanup();

	MObjectManager* GetObjectManager();
	MCollisionCheckerManager* GetCollisionManager();

private:
	MObjectManager* objectManager;
	MCollisionCheckerManager* collisionCheckManager;
};

#endif