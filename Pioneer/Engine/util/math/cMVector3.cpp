#include "Mmath.h"

cMmathVector3::cMmathVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

cMmathVector3::cMmathVector3(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

cMmathVector3::~cMmathVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

cMmathVector3 cMmathVector3::GetUnitVector()
{
	double	dLength = GetLength();
	cMmathVector3 unitVector(x, y, z);
	
	unitVector.x /= dLength;
	unitVector.y /= dLength;
	unitVector.z /= dLength;

	return unitVector;
}

double cMmathVector3::GetLength()
{
	double	dLength = 0;

	dLength = pow(x, 2) + pow(y, 2) + pow(z, 2);
	dLength = sqrt(dLength);

	return dLength;
}

D3DXVECTOR3 cMmathVector3::GetDxVector3()
{
	return D3DXVECTOR3((float)x, (float)y, (float)z);
}

cMmathVector3 cMmathVector3::operator+(cMmathVector3 _operand)
{
	cMmathVector3 resultVector(x, y, z);

	resultVector.x += _operand.x;
	resultVector.y += _operand.y;
	resultVector.z += _operand.z;

	return resultVector;
}

cMmathVector3 cMmathVector3::operator-(cMmathVector3 _operand)
{
	cMmathVector3 resultVector(x, y, z);

	resultVector.x -= _operand.x;
	resultVector.y -= _operand.y;
	resultVector.z -= _operand.z;

	return resultVector;
}

cMmathVector3 cMmathVector3::operator*(double _operand)
{
	cMmathVector3 resultVector(x, y, z);

	resultVector.x *= _operand;
	resultVector.y *= _operand;
	resultVector.z *= _operand;

	return resultVector;
}

cMmathVector3 cMmathVector3::operator/(double _operand)
{
	cMmathVector3 resultVector(x, y, z);

	resultVector.x /= _operand;
	resultVector.y /= _operand;
	resultVector.z /= _operand;

	return resultVector;
}

void cMmathVector3::operator+=(cMmathVector3 _operand)
{
	x += _operand.x;
	y += _operand.y;
	z += _operand.z;
}

void cMmathVector3::operator-=(cMmathVector3 _operand)
{
	x -= _operand.x;
	y -= _operand.y;
	z -= _operand.z;
}

void cMmathVector3::operator*=(double _operand)
{
	x *= _operand;
	y *= _operand;
	z *= _operand;
}

void cMmathVector3::operator/=(double _operand)
{
	x /= _operand;
	y /= _operand;
	z /= _operand;
}
