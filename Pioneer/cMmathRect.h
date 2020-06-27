#pragma once

#ifndef __C_M_RECT_H__
#define __C_M_RECT_H__

typedef class cMmathRect
{
public:
	int	left;
	int	right;
	int	top;
	int	bottom;

public:
	cMmathRect();
	cMmathRect(int _left, int _top, int _right, int _bottom);
	cMmathRect(cMmathRect* _rect);

	virtual ~cMmathRect();

	int	GetHeight();
	int	GetWidth();

	void	DeflateRect(int _left, int _top, int _right, int _bottom);
	void	InflateRect(int _left, int _top, int _right, int _bottom);

	void	MoveToX(int _delta);
	void	MoveToY(int _delta);
	void	MoveToXY(int _x, int _y);

	bool	IsOverlapped(cMmathRect _rect);
	bool	IsOverlapped(cMmathRect* _pRect);

	RECT	GetRect();
} MRect;

#endif