#include "cMsysThread.h"
#include <Windows.h>
#include <chrono>

cMsysThread::cMsysThread()
{
}

cMsysThread::~cMsysThread()
{
}

void cMsysThread::ThreadMain(cMsysThread* _mothod, void(_threadFunc)(void *), void * _arg)
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
	return;
}

void cMsysThread::CreateThread(void(_threadFunc)(void *), void * _arg)
{
}

void cMsysThread::StopThread(bool _waitForStop, int _timeout)
{
	m_stopThread = true;

	if (_waitForStop == true)
	{
		WaitForThreadStop(_timeout);
	}
}

bool cMsysThread::WaitForThreadStop(int _timeout)
{
	std::cv_status status = std::cv_status::no_timeout;
	status = m_stopCheckCondition.wait_for(m_stopCheckuniquelock, std::chrono::milliseconds(1) * _timeout);

	if (status == std::cv_status::timeout)
	{
		return false;
	}

	return true;
}

bool cMsysThread::WaitForThreadWait(int _timeout)
{
	std::cv_status status = std::cv_status::no_timeout;
	status = m_waitCheckCondition.wait_for(m_waitCheckuniquelock, std::chrono::milliseconds(1) * _timeout);

	if (status == std::cv_status::timeout)
	{
		return false;
	}

	return true;
}

void cMsysThread::WaitThread(bool _waitForThreadWait, int _timeout)
{
	m_waitThread = true;

	if (_waitForThreadWait == true)
	{
		WaitForThreadWait(_timeout);
	}
}

void cMsysThread::RunThread()
{
	m_waitThread = false;
}

const int cMsysThread::GetThreadNum()
{
	return 0;
}
