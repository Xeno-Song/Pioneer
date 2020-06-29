#include "cMutilTimer.h"
#include <Windows.h>

cMutilTimer::cMutilTimer(int _timerNum)
{
	m_timerNum = _timerNum;

	m_startTime = 0;
	m_timerTime = 0;
	m_totalElapsedTime = 0;

	m_activateMode = MUTIL_TIMER_MODE_TIMER;
	m_repeatMode = MUTIL_TIMER_REPEAT_DISABLE;
	m_status = MUTIL_TIMER_STATUS_STOP;
}

cMutilTimer::~cMutilTimer()
{
	Cleanup();
}

void cMutilTimer::Cleanup()
{
	Stop(true);

	m_startTime = 0;
	m_timerTime = 0;
	m_totalElapsedTime = 0;
}

void cMutilTimer::Start(MutilTimerActivateMode _mode)
{
	m_startTime = GetTickCount();
	m_activateMode = _mode;
}

void cMutilTimer::Stop(bool _reset)
{
	unsigned int currentTime = GetTickCount();
	m_status = MUTIL_TIMER_STATUS_STOP;

	if (_reset)
	{
		m_totalElapsedTime = 0;
	}
	else
	{
		m_totalElapsedTime += currentTime - m_startTime;
	}
}

void cMutilTimer::Pause()
{
	unsigned int currentTime = GetTickCount();
	m_status = MUTIL_TIMER_STATUS_PAUSE;
	m_totalElapsedTime += currentTime - m_startTime;
}

void cMutilTimer::Resume()
{
	m_startTime = GetTickCount();
	m_status = MUTIL_TIMER_STATUS_RUN;
}

void cMutilTimer::SetTimerTime(unsigned int _time)
{
	m_timerTime = _time;
}

void cMutilTimer::SetActivationMode(E_TIMER_ACTIVATION_MODE _mode)
{
	m_activateMode = _mode;
}

void cMutilTimer::SetTimerRepeatMode(E_TIMER_REPEAT_MODE _mode)
{
	m_repeatMode = _mode;
}

unsigned int cMutilTimer::GetRemainingTime()
{
	unsigned int	remainingTime = 0;
	remainingTime = m_timerTime - GetElapsedTime();

	return remainingTime;
}

unsigned int cMutilTimer::GetElapsedTime()
{
	unsigned int currentTime = 0;
	currentTime = GetTickCount();

	return m_totalElapsedTime + (currentTime + m_startTime);
}

void cMutilTimer::SetStopEventHandler(void(_eventHandler)(unsigned int))
{
	m_eventHandler = _eventHandler;
}

void cMutilTimer::CallEventHandler()
{
	m_eventHandler(m_timerNum);
}
