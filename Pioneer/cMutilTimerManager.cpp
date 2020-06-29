#include "cMutilTimerManager.h"
#include "cMsysManager.h"

cMutilTimerManager::cMutilTimerManager()
{
	m_lastTimerNum = 0;
	m_timerList.clear();
	m_timerThread = nullptr;
}

cMutilTimerManager::~cMutilTimerManager()
{
	Cleanup();
}

bool cMutilTimerManager::InitializeTimerManager()
{
	m_timerThread = MGetSystem()->GetThreadManager()->CreateThread();
	m_timerThread->CreateThread(&ThreadJob, this);

	return true;
}

void cMutilTimerManager::Cleanup()
{
	m_timerThread->StopThread(true, 100);

	for (auto timer : m_timerList)
	{
		timer.second->Stop();
		delete timer.second;
	}

	m_timerList.clear();
}

void cMutilTimerManager::LockAccessMutex()
{
	m_accessMutex.lock();
}

void cMutilTimerManager::UnlockAccessMutex()
{
	m_accessMutex.unlock();
}

cMutilTimer * cMutilTimerManager::CreateTimer()
{
	LockAccessMutex();

	cMutilTimer*	timer = nullptr;
	timer = new cMutilTimer(m_lastTimerNum);
	m_timerList.insert(std::make_pair(m_lastTimerNum, timer));
	m_lastTimerNum++;

	UnlockAccessMutex();

	return timer;
}

cMutilTimer * cMutilTimerManager::GetTimer(int _timerNum)
{
	auto result = m_timerList.find(_timerNum);
	if (result == m_timerList.end())
	{
		return nullptr;
	}

	return result->second;
}

void cMutilTimerManager::DeleteTimer(int _timerNum)
{
	LockAccessMutex();
	m_timerList.erase(_timerNum);
	UnlockAccessMutex();
}

void cMutilTimerManager::ThreadJob(void * _arg)
{
	cMutilTimerManager* parent = (cMutilTimerManager*)_arg;
	parent->CheckTimer();
}

void cMutilTimerManager::CheckTimer()
{
	for (auto timer : m_timerList)
	{
		if (timer.second->GetRemainingTime() <= 0)
		{
			timer.second->CallEventHandler();
		}
	}

	Sleep(1);
}
