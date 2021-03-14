#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

class MsysThread
{
private:
	long long int				m_threadNum;

	std::thread		m_thread;
	bool			m_waitThread;
	bool			m_stopThread;
	bool			m_dead;

	std::mutex						m_waitCheckMutex;
	std::unique_lock<std::mutex>	m_waitCheckuniquelock;
	std::condition_variable			m_waitCheckCondition;

	std::mutex						m_stopCheckMutex;
	std::unique_lock<std::mutex>	m_stopCheckuniquelock;
	std::condition_variable			m_stopCheckCondition;

protected:
	static void ThreadMain(MsysThread* _mothod, void(_threadFunc)(void*), void* _arg);
	
public:
	MsysThread(long long int _threadNum);
	virtual ~MsysThread();

	void	CreateThread(void(_threadFunc)(void*), void* _arg);
	void	StopThread(bool _waitForStop = false, int _timeout = 100);
	
	void	WaitThread(bool _waitForThreadWait = false, int _timeout = 100);
	void	ResumeThread();

	bool	WaitForThreadStop(int _timeout = 100);
	bool	WaitForThreadWait(int _timeout = 100);

	bool	GetDead();

	const long long int	GetThreadNum();
};

