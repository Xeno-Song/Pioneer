#include "cMutilTimerManager.h"
#include "../../sys/cMsysManager.h"

MutilTimerManager::MutilTimerManager()
{
	m_lastTimerNum = 0;
	m_timerList.clear();
	m_timerThread = nullptr;
}

MutilTimerManager::~MutilTimerManager()
{
	Cleanup();
}

bool MutilTimerManager::InitializeTimerManager()
{
	m_timerThread = MGetSystem()->GetThreadManager()->CreateThread();
	m_timerThread->CreateThread(&ThreadJob, this);

	return true;
}

void MutilTimerManager::Cleanup()
{
	m_timerThread->StopThread(true, 100);

	for (auto timer : m_timerList)
	{
		timer.second->Stop();
		delete timer.second;
	}

	m_timerList.clear();
}

void MutilTimerManager::LockAccessMutex()
{
	m_accessMutex.lock();
}

void MutilTimerManager::UnlockAccessMutex()
{
	m_accessMutex.unlock();
}

cMutilTimer * MutilTimerManager::CreateTimer()
{
	LockAccessMutex();

	cMutilTimer*	timer = nullptr;
	timer = new cMutilTimer(m_lastTimerNum);
	m_timerList.insert(std::make_pair(m_lastTimerNum, timer));
	m_lastTimerNum++;

	UnlockAccessMutex();

	return timer;
}

cMutilTimer * MutilTimerManager::GetTimer(int _timerNum)
{
	auto result = m_timerList.find(_timerNum);
	if (result == m_timerList.end())
	{
		return nullptr;
	}

	return result->second;
}

void MutilTimerManager::DeleteTimer(int _timerNum)
{
	LockAccessMutex();
	m_timerList.erase(_timerNum);
	UnlockAccessMutex();
}

void MutilTimerManager::ThreadJob(void * _arg)
{
	MutilTimerManager* parent = (MutilTimerManager*)_arg;
	parent->CheckTimer();
}

void MutilTimerManager::CheckTimer()
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
