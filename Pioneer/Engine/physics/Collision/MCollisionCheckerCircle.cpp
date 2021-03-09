#include "MCollisionChecker.h"
#include "../Object/MObjectManager.h"

MCollisionCheckerCircle::MCollisionCheckerCircle()
{
}

MCollisionCheckerCircle::MCollisionCheckerCircle(MsysMutexQueue<std::pair<unsigned int, unsigned int>>* resultQueue)
{
	SetResultQueue(resultQueue);
}

MCollisionCheckerCircle::~MCollisionCheckerCircle()
{
	
}

void MCollisionCheckerCircle::CheckThreadJob()
{
}

void MCollisionCheckerCircle::CheckCollision(UID first, UID second)
{
	
}

void MCollisionCheckerCircle::SetResultQueue(MsysMutexQueue<std::pair<unsigned int, unsigned int>>* resultQueue)
{
	this->resultQueue = resultQueue;
}
