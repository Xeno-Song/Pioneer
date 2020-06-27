#pragma once

#ifndef __C_M_VECTOR3_H__
#define __C_M_VECTOR3_H__

#include <d3dx9math.h>

typedef class cMmathVector3
{
public:
	double x;
	double y;
	double z;

public:
	cMmathVector3();
	cMmathVector3(double _x, double _y, double _z);

	virtual ~cMmathVector3();

	cMmathVector3	GetUnitVector();
	double	GetLength();

	D3DXVECTOR3	GetDxVector3();

	cMmathVector3 operator +(cMmathVector3 _operand);
	cMmathVector3 operator -(cMmathVector3 _operand);
	cMmathVector3 operator *(double _operand);
	cMmathVector3 operator /(double _operand);
} MVector3;

#endif