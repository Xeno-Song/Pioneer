#pragma once

#ifndef __C_M_VECTOR3_H__
#define __C_M_VECTOR3_H__

#include <d3dx9math.h>

typedef class cMVector3
{
public:
	double x;
	double y;
	double z;

public:
	cMVector3();
	cMVector3(double _x, double _y, double _z);

	virtual ~cMVector3();

	cMVector3	GetUnitVector();
	double	GetLength();

	D3DXVECTOR3	GetDxVector3();

	cMVector3 operator +(cMVector3 _operand);
	cMVector3 operator -(cMVector3 _operand);
	cMVector3 operator *(double _operand);
	cMVector3 operator /(double _operand);
} MVector3;

#endif