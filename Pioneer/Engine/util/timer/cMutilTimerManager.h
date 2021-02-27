#pragma once
#include "cMutilTimer.h"
#include "../../sys/thd/cMsysThread.h"
#include <map>
#include <mutex>

class MutilTimerManager
{
public:
	int							m_lastTimerNum;
	std::map<int, cMutilTimer*>	m_timerList;

	std::mutex		m_accessMutex;
	cMsysThread*	m_timerThread;

public:
	MutilTimerManager();
	virtual ~MutilTimerManager();

	bool	InitializeTimerManager();
	void	Cleanup();

	cMutilTimer*	CreateTimer();
	cMutilTimer*	GetTimer(int _timerNum);
	void			DeleteTimer(int _timerNum);
	
	static void		ThreadJob(void* _arg);
	void			CheckTimer();

private:
	void	LockAccessMutex();
	void	UnlockAccessMutex();
};

