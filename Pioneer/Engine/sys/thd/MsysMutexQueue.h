#pragma once

#ifndef __M_SYS_MUTEX_QUEUE_H__
#define __M_SYS_MUTEX_QUEUE_H__

#include <mutex>
#include <queue>

template <typename DataType>
class MsysMutexQueue
{
public:
	MsysMutexQueue()
	{
		Clear();
	}
	virtual ~MsysMutexQueue()
	{
		Clear();
	}

public:
	int Push(const DataType& data)
	{
		LockMutex();
		queue.push(data);
		UnlockMutex();

		return 0;
	}
	bool Pop(DataType* out)
	{
		DataType* data = nullptr;

		LockMutex();
		data = queue.pop();
		UnlockMutex();

		if (data == nullptr)
			return false;

		return true;
	}

	int GetCount()
	{
		int cnt = 0;

		LockMutex();
		cnt = queue.size();
		UnlockMutex();

		return cnt;
	}
	void Clear()
	{
		while (!queue.empty()) queue.pop();
	}
	
protected:
	void LockMutex() { accessLock.lock(); }
	void UnlockMutex() { accessLock.unlock(); }

private:
	std::mutex accessLock;
	std::queue<DataType> queue;
};

#endif