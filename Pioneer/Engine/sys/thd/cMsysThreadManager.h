#pragma once
#include "cMsysThread.h"
#include <map>

class MsysThreadManager
{
private:
	long long int		m_lastThreadNum;
	int					m_threadCleanupInterval;

	std::map<long long int, cMsysThread*>	m_threadMap;
	std::mutex								m_accessMutex;

private:
	cMsysThread*	m_cleanThread;

public:
	MsysThreadManager();
	virtual ~MsysThreadManager();

	void	Initialize();
	void	Cleanup();

	cMsysThread*	CreateThread();
	cMsysThread*	CreateThread(void(_threadFunc)(void*), void* _arg);

	cMsysThread*	GetThread(int _threadNum);

	void			CleanThreads();
	static void		ThreadJob(void* _arg);

	void			SetThreadCleanupInterval(unsigned int _interval);
	unsigned int	GetThreadCleanupInterval();

private:
	void	LockAccessMutex();
	void	UnlockAccessMutex();
};

