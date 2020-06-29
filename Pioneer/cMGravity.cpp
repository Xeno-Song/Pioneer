#include "cMGravity.h"


int cMphyGravity::GravityCount(int time_ms)
{
	//실제 m 길이 값
	int len = M_Gravity_Constant * ((time_ms * time_ms) / 1000000);
	int pixel_count = len / LenPerVector;
	return pixel_count;
}

