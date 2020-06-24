#include "Mmath.h"

cMVector3::cMVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

cMVector3::cMVector3(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

cMVector3::~cMVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

cMVector3 cMVector3::GetUnitVector()
{
	double	dLength = GetLength();
	cMVector3 unitVector(x, y, z);
	
	unitVector.x /= dLength;
	unitVector.y /= dLength;
	unitVector.z /= dLength;

	return unitVector;
}

double cMVector3::GetLength()
{
	double	dLength = 0;

	dLength = pow(x, 2) + pow(y, 2) + pow(z, 2);
	dLength = sqrt(dLength);

	return dLength;
}

D3DXVECTOR3 cMVector3::GetDxVector3()
{
	return D3DXVECTOR3(x, y, z);
}

cMVector3 cMVector3::operator+(cMVector3 _operand)
{
	cMVector3 resultVector(x, y, z);

	resultVector.x += _operand.x;
	resultVector.y += _operand.y;
	resultVector.z += _operand.z;

	return resultVector;
}

cMVector3 cMVector3::operator-(cMVector3 _operand)
{
	cMVector3 resultVector(x, y, z);

	resultVector.x -= _operand.x;
	resultVector.y -= _operand.y;
	resultVector.z -= _operand.z;

	return resultVector;
}

cMVector3 cMVector3::operator*(double _operand)
{
	cMVector3 resultVector(x, y, z);

	resultVector.x *= _operand;
	resultVector.y *= _operand;
	resultVector.z *= _operand;

	return resultVector;
}

cMVector3 cMVector3::operator/(double _operand)
{
	cMVector3 resultVector(x, y, z);

	resultVector.x /= _operand;
	resultVector.y /= _operand;
	resultVector.z /= _operand;

	return resultVector;
}
