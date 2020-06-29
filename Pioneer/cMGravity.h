#pragma once

class cMphyGravity
{
private:
	float		M_Gravity_Constant = 9.8;
	int			LenPerVector = 10; // ( cm / vector_count ) ÇÑÇÈ¼¿´ç cm

public:
	int			GravityCount(int time_ms);

	void		GravityEnable();
	void		GravityDisable();



};

