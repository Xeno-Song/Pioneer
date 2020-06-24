#include "Mmath.h"

cMRect::cMRect()
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

cMRect::cMRect(int _left, int _top, int _right, int _bottom)
{
	left = min(_left, _right);
	right = _right;
	top = _top;
	bottom = _bottom;
}

cMRect::cMRect(cMRect * _rect)
{
	left = (*_rect).left;
	top = (*_rect).top;
	right = (*_rect).right;
	bottom = (*_rect).bottom;
}

cMRect::~cMRect()
{
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}

int cMRect::GetHeight()
{
	return bottom - top;
}

int cMRect::GetWidth()
{
	return right - left;
}

void cMRect::DeflateRect(int _left, int _top, int _right, int _bottom)
{
	left += _left;
	top += _top;
	right -= _right;
	bottom -= _bottom;
}

void cMRect::InflateRect(int _left, int _top, int _right, int _bottom)
{
	left -= _left;
	top -= _top;
	right += _right;
	bottom += _bottom;
}

void cMRect::MoveToX(int _delta)
{
	left += _delta;
	right += _delta;
}

void cMRect::MoveToY(int _delta)
{
	top += _delta;
	bottom += _delta;
}

void cMRect::MoveToXY(int _x, int _y)
{
	left += _x;
	right += _x;
	top += _y;
	bottom += _y;
}

bool cMRect::IsOverlapped(cMRect _rect)
{
	if (left < _rect.right &&
		right > _rect.left &&
		top < _rect.bottom &&
		bottom > _rect.top)
		return true;

	return false;
}

bool cMRect::IsOverlapped(cMRect * _pRect)
{
	if (left < _pRect->right &&
		right > _pRect->left &&
		top < _pRect->bottom &&
		bottom > _pRect->top)
		return true;

	return false;
}

RECT cMRect::GetRect()
{
	RECT rc;
	rc.left = left;
	rc.top = top;
	rc.right = right;
	rc.bottom = bottom;

	return rc;
}
