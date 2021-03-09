#include "cMsysMutexQueue.h"

template<class dataType>
inline MsysMutexQueue<dataType>::MsysMutexQueue()
{
	Clear();
}

template<class dataType>
inline MsysMutexQueue<dataType>::~MsysMutexQueue()
{
	Clear();
}

template<class dataType>
inline int MsysMutexQueue<dataType>::Push(dataType data)
{
	LockMutex();
	queue.push(data);
	UnlockMutex();

	return 0;
}

template<class dataType>
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

template<class dataType>
inline int MsysMutexQueue<dataType>::GetCount()
{
	int cnt = 0;

	LockMutex();
	cnt = queue.size();
	UnlockMutex();

	return cnt;
}

template<class dataType>
inline void MsysMutexQueue<dataType>::Clear()
{
	while (!queue.empty()) queue.pop();
}

template<class dataType>
inline void MsysMutexQueue<dataType>::LockMutex()
{
	accessLock.lock();
}

template<class dataType>
inline void MsysMutexQueue<dataType>::UnlockMutex()
{
	accessLock.unlock();
}
