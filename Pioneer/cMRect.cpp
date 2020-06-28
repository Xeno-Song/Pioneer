#include "Mmath.h"

cMmathRect::cMmathRect()
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

cMmathRect::cMmathRect(int _left, int _top, int _right, int _bottom)
{
	left = min(_left, _right);
	right = _right;
	top = _top;
	bottom = _bottom;
}

cMmathRect::cMmathRect(cMmathRect * _rect)
{
	left = (*_rect).left;
	top = (*_rect).top;
	right = (*_rect).right;
	bottom = (*_rect).bottom;
}

cMmathRect::~cMmathRect()
{
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

int cMmathRect::GetHeight()
{
	return bottom - top;
}

int cMmathRect::GetWidth()
{
	return right - left;
}

void cMmathRect::DeflateRect(int _left, int _top, int _right, int _bottom)
{
	left += _left;
	top += _top;
	right -= _right;
	bottom -= _bottom;
}

void cMmathRect::InflateRect(int _left, int _top, int _right, int _bottom)
{
	left -= _left;
	top -= _top;
	right += _right;
	bottom += _bottom;
}

void cMmathRect::MoveToX(int _delta)
{
	left += _delta;
	right += _delta;
}

void cMmathRect::MoveToY(int _delta)
{
	top += _delta;
	bottom += _delta;
}

void cMmathRect::MoveToXY(int _x, int _y)
{
	left += _x;
	right += _x;
	top += _y;
	bottom += _y;
}

bool cMmathRect::IsOverlapped(cMmathRect _rect)
{
	if (left < _rect.right &&
		right > _rect.left &&
		top < _rect.bottom &&
		bottom > _rect.top)
		return true;

	return false;
}

bool cMmathRect::IsOverlapped(cMmathRect * _pRect)
{
	if (left < _pRect->right &&
		right > _pRect->left &&
		top < _pRect->bottom &&
		bottom > _pRect->top)
		return true;

	return false;
}

RECT cMmathRect::GetRect()
{
	RECT rc;
	rc.left = left;
	rc.top = top;
	rc.right = right;
	rc.bottom = bottom;

	return rc;
}
