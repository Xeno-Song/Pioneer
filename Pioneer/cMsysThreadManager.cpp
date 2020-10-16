#include "cMsysThreadManager.h"
#include "Mdefines.h"
#include <vector>
#include <Windows.h>

cMsysThreadManager::cMsysThreadManager()
{
	m_threadMap.clear();

	m_lastThreadNum = 0;
	m_threadCleanupInterval = 1000;
}

cMsysThreadManager::~cMsysThreadManager()
{
	Cleanup();
}

void cMsysThreadManager::Initialize()
{
	m_cleanThread = CreateThread(ThreadJob, this);
}

void cMsysThreadManager::Cleanup()
{
	m_cleanThread->StopThread(true, 1100);

	for (auto thread : m_threadMap)
	{
		thread.second->StopThread();
	}

	for (auto thread : m_threadMap)
	{
		thread.second->WaitForThreadStop(100);
	}

	m_threadMap.clear();
}

cMsysThread * cMsysThreadManager::CreateThread()
{
	LockAccessMutex();

	cMsysThread* thread = nullptr;
	thread = new cMsysThread(m_lastThreadNum);
	m_threadMap.insert(std::make_pair(m_lastThreadNum, thread));
	m_lastThreadNum++;

	UnlockAccessMutex();

	return thread;
}

cMsysThread * cMsysThreadManager::CreateThread(void(_threadFunc)(void *), void * _arg)
{
	LockAccessMutex();

	cMsysThread* thread = nullptr;
	thread = new cMsysThread(m_lastThreadNum);

	thread->CreateThread(_threadFunc, _arg);
	m_threadMap.insert(std::make_pair(m_lastThreadNum, thread));
	m_lastThreadNum++;

	UnlockAccessMutex();

	return thread;
}

cMsysThread * cMsysThreadManager::GetThread(int _threadNum)
{
	auto result = m_threadMap.find(_threadNum);
	if (result == m_threadMap.end())
	{
		return nullptr;
	}

	return result->second;
}

void cMsysThreadManager::SetThreadCleanupInterval(unsigned int _interval)
{
	m_threadCleanupInterval = _interval;
}

unsigned int cMsysThreadManager::GetThreadCleanupInterval()
{
	return m_threadCleanupInterval;
}

void cMsysThreadManager::CleanThreads()
{
	Sleep(GetThreadCleanupInterval());

	std::vector<long long int>	removeIndex;
	removeIndex.clear();

	LockAccessMutex();

	for (auto thread : m_threadMap)
	{
		if (thread.second->GetDead())
		{
			removeIndex.push_back(thread.first);
		}
	}

	for (auto index : removeIndex)
	{
		m_threadMap.erase(index);
	}

	UnlockAccessMutex();

	m_threadMap.clear();
}

void cMsysThreadManager::ThreadJob(void* _arg)
{
	((cMsysThreadManager*)_arg)->CleanThreads();
}

void cMsysThreadManager::LockAccessMutex()
{
	m_accessMutex.lock();
}

void cMsysThreadManager::UnlockAccessMutex()
{
	m_accessMutex.unlock();
}
