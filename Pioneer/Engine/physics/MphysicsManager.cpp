#include "MphysicsManager.h"
#include "../Mdefines.h"

MphysicsManager::MphysicsManager()
{
    objectManager = nullptr;
    collisionCheckManager = nullptr;
}

MphysicsManager::~MphysicsManager()
{
    Cleanup();
}

void MphysicsManager::Initialize()
{
    objectManager = new MObjectManager();
    collisionCheckManager = new MCollisionCheckerManager();
}

void MphysicsManager::Cleanup()
{
    SAFE_DELETE(objectManager);
    SAFE_DELETE(collisionCheckManager);
}

MObjectManager* MphysicsManager::GetObjectManager()
{
    return objectManager;
}

MCollisionCheckerManager* MphysicsManager::GetCollisionManager()
{
    return collisionCheckManager;
}
