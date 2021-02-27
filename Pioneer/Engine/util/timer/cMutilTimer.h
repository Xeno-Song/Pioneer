#pragma once

typedef enum E_TIMER_STATUS
{
	MUTIL_TIMER_STATUS_STOP,
	MUTIL_TIMER_STATUS_PAUSE,
	MUTIL_TIMER_STATUS_RUN,
} MutilTimerStatus;

typedef enum E_TIMER_ACTIVATION_MODE
{
	MUTIL_TIMER_MODE_STOPWATCH,
	MUTIL_TIMER_MODE_TIMER
} MutilTimerActivateMode;

typedef enum E_TIMER_REPEAT_MODE
{
	MUTIL_TIMER_REPEAT_DISABLE,
	MUTIL_TIMER_REPEAT_ENABLE
} MutilTimerRepeatMode;

class cMutilTimer
{
protected:
	MutilTimerActivateMode	m_activateMode;
	MutilTimerRepeatMode	m_repeatMode;
	MutilTimerStatus		m_status;

	unsigned int			m_startTime;
	unsigned int			m_timerTime;
	unsigned int			m_totalElapsedTime;

	int						m_timerNum;
	void					(*m_eventHandler)(unsigned int);

public:
	cMutilTimer(int _timerNum);
	virtual ~cMutilTimer();

	void	Cleanup();

	void	Start();
	void	Start(MutilTimerActivateMode _mode);
	void	Stop(bool _reset = true);

	void	Pause();
	void	Resume();

	void	SetActivationMode(E_TIMER_ACTIVATION_MODE _mode);
	void	SetTimerTime(unsigned int _time);
	void	SetTimerRepeatMode(E_TIMER_REPEAT_MODE _mode);

	int	GetRemainingTime();
	unsigned int	GetElapsedTime();

	void	SetStopEventHandler(void(_eventHandler)(unsigned int));
	void	CallEventHandler();
};

