#include "cMGravity.h"


int cMphyGravity::GravityCount(int time_ms)
{
	//���� m ���� ��
	int len = M_Gravity_Constant * ((time_ms * time_ms) / 1000000);
	int pixel_count = len / LenPerVector;
	return pixel_count;
}

