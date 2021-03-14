#include "MsysThreadManager.h"
#include "../../Mdefines.h"
#include <vector>
#include <Windows.h>

MsysThreadManager::MsysThreadManager()
{
	m_threadMap.clear();

	m_lastThreadNum = 0;
	m_threadCleanupInterval = 1000;
}

MsysThreadManager::~MsysThreadManager()
{
	Cleanup();
}

void MsysThreadManager::Initialize()
{
	m_cleanThread = CreateThread(ThreadJob, this);
}

void MsysThreadManager::Cleanup()
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

MsysThread * MsysThreadManager::CreateThread()
{
	LockAccessMutex();

	MsysThread* thread = nullptr;
	thread = new MsysThread(m_lastThreadNum);
	m_threadMap.insert(std::make_pair(m_lastThreadNum, thread));
	m_lastThreadNum++;

	UnlockAccessMutex();

	return thread;
}

MsysThread * MsysThreadManager::CreateThread(void(_threadFunc)(void *), void * _arg)
{
	LockAccessMutex();

	MsysThread* thread = nullptr;
	thread = new MsysThread(m_lastThreadNum);

	thread->CreateThread(_threadFunc, _arg);
	m_threadMap.insert(std::make_pair(m_lastThreadNum, thread));
	m_lastThreadNum++;

	UnlockAccessMutex();

	return thread;
}

MsysThread * MsysThreadManager::GetThread(int _threadNum)
{
	auto result = m_threadMap.find(_threadNum);
	if (result == m_threadMap.end())
	{
		return nullptr;
	}

	return result->second;
}

void MsysThreadManager::SetThreadCleanupInterval(unsigned int _interval)
{
	m_threadCleanupInterval = _interval;
}

unsigned int MsysThreadManager::GetThreadCleanupInterval()
{
	return m_threadCleanupInterval;
}

void MsysThreadManager::CleanThreads()
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

void MsysThreadManager::ThreadJob(void* _arg)
{
	((MsysThreadManager*)_arg)->CleanThreads();
}

void MsysThreadManager::LockAccessMutex()
{
	m_accessMutex.lock();
}

void MsysThreadManager::UnlockAccessMutex()
{
	m_accessMutex.unlock();
}
