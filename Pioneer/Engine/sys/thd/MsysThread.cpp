#include "MsysThread.h"
#include "../../sys/cMsysManager.h"
#include <Windows.h>
#include <chrono>

MsysThread::MsysThread(long long int _threadNum)
{
	m_threadNum = _threadNum;
	m_waitThread = false;
	m_stopThread = false;
	m_dead = false;
}

MsysThread::~MsysThread()
{
	StopThread(true, 100);
}

void MsysThread::ThreadMain(MsysThread* _mothod, void(_threadFunc)(void *), void * _arg)
{
	while (true)
	{
		if (_mothod->m_stopThread == true)	return;
		if (_mothod->m_waitThread == true)
		{
			Sleep(1);
			continue;
		}

		_threadFunc(_arg);

	}

	_mothod->m_dead = true;
}

void MsysThread::CreateThread(void(_threadFunc)(void *), void * _arg)
{
	m_thread = std::thread(ThreadMain, this, _threadFunc, _arg);
}

void MsysThread::StopThread(bool _waitForStop, int _timeout)
{
	m_stopThread = true;

	if (_waitForStop == true)
	{
		WaitForThreadStop(_timeout);
	}
}

bool MsysThread::WaitForThreadStop(int _timeout)
{
	std::cv_status status = std::cv_status::no_timeout;
	status = m_stopCheckCondition.wait_for(m_stopCheckuniquelock, std::chrono::milliseconds(1) * _timeout);

	if (status == std::cv_status::timeout)
	{
		std::terminate_handler(m_thread.native_handle());
		return false;
	}

	return true;
}

bool MsysThread::WaitForThreadWait(int _timeout)
{
	std::cv_status status = std::cv_status::no_timeout;
	status = m_waitCheckCondition.wait_for(m_waitCheckuniquelock, std::chrono::milliseconds(1) * _timeout);

	if (status == std::cv_status::timeout)
	{
		return false;
	}

	return true;
}

bool MsysThread::GetDead()
{
	return m_dead;
}

void MsysThread::WaitThread(bool _waitForThreadWait, int _timeout)
{
	m_waitThread = true;

	if (_waitForThreadWait == true)
	{
		WaitForThreadWait(_timeout);
	}
}

void MsysThread::ResumeThread()
{
	m_waitThread = false;
}

const long long int MsysThread::GetThreadNum()
{
	return m_threadNum;
}
