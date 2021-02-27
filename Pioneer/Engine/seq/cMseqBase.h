#pragma once

class cMseqBase
{
public:
	bool	m_waitForChangeSequence;

public:
	int		Initialize();
	int		Update();
	int		Render();
	int		Cleanup();

public:
	virtual int	OnInitialize() = 0;
	virtual int	OnUpdate() = 0;
	virtual int	OnRender() = 0;
	virtual int	OnCleanup() = 0;
};

