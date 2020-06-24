#pragma once

#ifndef __C_M_RECT_H__
#define __C_M_RECT_H__

typedef class cMRect
{
public:
	int	left;
	int	right;
	int	top;
	int	bottom;

public:
	cMRect();
	cMRect(int _left, int _top, int _right, int _bottom);
	cMRect(cMRect* _rect);

	virtual ~cMRect();

	int	GetHeight();
	int	GetWidth();

	void	DeflateRect(int _left, int _top, int _right, int _bottom);
	void	InflateRect(int _left, int _top, int _right, int _bottom);

	void	MoveToX(int _delta);
	void	MoveToY(int _delta);
	void	MoveToXY(int _x, int _y);

	bool	IsOverlapped(cMRect _rect);
	bool	IsOverlapped(cMRect* _pRect);

	RECT	GetRect();
} MRect;

#endif