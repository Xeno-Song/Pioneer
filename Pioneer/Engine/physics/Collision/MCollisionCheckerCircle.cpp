#include "MCollisionChecker.h"
#include "../Object/MObjectManager.h"
#include "../../MEngine.h"

MCollisionCheckerCircle::MCollisionCheckerCircle()
{
	Initialize();
}

MCollisionCheckerCircle::MCollisionCheckerCircle(MsysMutexQueue<std::pair<unsigned int, unsigned int>>* resultQueue)
{
	Initialize();
	SetResultQueue(resultQueue);
}

MCollisionCheckerCircle::~MCollisionCheckerCircle()
{
	
}

void MCollisionCheckerCircle::StartCheckThread()
{
}

void MCollisionCheckerCircle::SuspendCheckThread()
{
}

bool MCollisionCheckerCircle::GetStoppedThreadCount(int* count)
{
	// Check status pointer is valid
	if (count == nullptr) return false;

	(*count) = 0;

	for (auto iter : threadVector)
	{
		DWORD result;
		result = WaitForSingleObject(iter.second, 0);

		if (result == WAIT_OBJECT_0) *(count)++;
		else if (result != WAIT_TIMEOUT) return false;
	}

	return true;
}

bool MCollisionCheckerCircle::GetRunningThreadCount(int* count)
{
	// Check status pointer is valid
	if (count == nullptr) return false;

	(*count) = 0;

	for (auto iter : threadVector)
	{
		DWORD result;
		result = WaitForSingleObject(iter.second, 0);

		if (result == WAIT_TIMEOUT) *(count)++;
		else if (result != WAIT_OBJECT_0) return false;
	}

	return true;
}

void MCollisionCheckerCircle::CheckThreadJob()
{
}

void MCollisionCheckerCircle::CheckCollision(UID first, UID second)
{
	MObject* firstObj = MGetObjectManager()->GetObjectByUID(first);
	MObject* secondObj = MGetObjectManager()->GetObjectByUID(second);

	MVector3 firstPos = firstObj->GetPosition();
	MVector3 secondPos = secondObj->GetPosition();
	double firstObjCollRadius = firstObj->GetCollisionCircleRadius();
	double secondObjCollRadius = secondObj->GetCollisionCircleRadius();

	MVector3 distance = firstPos - secondPos;
	// Collision detected with Circle collision detection algorithm
	if (firstObjCollRadius + secondObjCollRadius >= distance.GetLength())
		resultQueue->Push(std::pair<UID, UID>(first, second));
}

void MCollisionCheckerCircle::SetResultQueue(MsysMutexQueue<std::pair<unsigned int, unsigned int>>* resultQueue)
{
	this->resultQueue = resultQueue;
}

void MCollisionCheckerCircle::Initialize()
{

}
