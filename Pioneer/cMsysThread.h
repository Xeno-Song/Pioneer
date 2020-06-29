#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

class cMsysThread
{
private:
	int				m_threadNum;

	std::thread		m_thread;
	bool			m_waitThread;
	bool			m_stopThread;

	std::mutex						m_waitCheckMutex;
	std::unique_lock<std::mutex>	m_waitCheckuniquelock;
	std::condition_variable			m_waitCheckCondition;

	std::mutex						m_stopCheckMutex;
	std::unique_lock<std::mutex>	m_stopCheckuniquelock;
	std::condition_variable			m_stopCheckCondition;

protected:
	void ThreadMain(cMsysThread* _mothod, void(_threadFunc)(void*), void* _arg);
	
public:
	cMsysThread();
	virtual ~cMsysThread();

	void	CreateThread(void(_threadFunc)(void*), void* _arg);
	void	StopThread(bool _waitForStop = false, int _timeout = 100);
	
	void	WaitThread(bool _waitForThreadWait = false, int _timeout = 100);
	void	RunThread();

	bool	WaitForThreadStop(int _timeout = 100);
	bool	WaitForThreadWait(int _timeout = 100);

	const int		GetThreadNum();
};

