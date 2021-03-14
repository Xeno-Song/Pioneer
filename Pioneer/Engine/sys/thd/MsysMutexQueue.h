#pragma once

#ifndef __M_SYS_MUTEX_QUEUE_H__
#define __M_SYS_MUTEX_QUEUE_H__

#include <mutex>
#include <queue>

template <class dataType>
class MsysMutexQueue
{
public:
	MsysMutexQueue();
	virtual ~MsysMutexQueue();

public:
	int Push(dataType data);
	bool Pop(dataType* out);

	int GetCount();
	void Clear();
	
protected:
	void LockMutex();
	void UnlockMutex();

private:
	std::mutex accessLock;
	std::queue<dataType> queue;
};

#endif