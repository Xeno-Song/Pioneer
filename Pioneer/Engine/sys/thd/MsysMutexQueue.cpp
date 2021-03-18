#include "MsysMutexQueue.h"

template<typename dataType>
inline MsysMutexQueue<dataType>::MsysMutexQueue()
{
	Clear();
}

template<typename dataType>
inline MsysMutexQueue<dataType>::~MsysMutexQueue()
{
	Clear();
}

template<typename dataType>
inline int MsysMutexQueue<dataType>::Push(const dataType& data)
{
	LockMutex();
	queue.push(data);
	UnlockMutex();

	return 0;
}

template<typename dataType>
inline bool MsysMutexQueue<dataType>::Pop(dataType* out)
{
	dataType* data = nullptr;

	LockMutex();
	data = queue.pop();
	UnlockMutex();

	if (data == nullptr)
		return false;

	return true;
}

template<typename dataType>
inline int MsysMutexQueue<dataType>::GetCount()
{
	int cnt = 0;

	LockMutex();
	cnt = queue.size();
	UnlockMutex();

	return cnt;
}

template<typename dataType>
inline void MsysMutexQueue<dataType>::Clear()
{
	while (!queue.empty()) queue.pop();
}

template<typename dataType>
inline void MsysMutexQueue<dataType>::LockMutex()
{
	accessLock.lock();
}

template<typename dataType>
inline void MsysMutexQueue<dataType>::UnlockMutex()
{
	accessLock.unlock();
}
