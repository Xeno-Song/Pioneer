#pragma once

#include "../../Mdefines.h"

#ifndef __DX_VERSION_11__

#include <d3d9.h>
#include <d3dx9.h>
#include "../../util/math/Mmath.h"

class cMd3dSprite
{
protected:
	LPD3DXSPRITE	m_pSprite;

public:
	cMd3dSprite();
	virtual ~cMd3dSprite();

	bool	Create();
	void	Cleanup();

	bool		SetTransform(D3DXMATRIX* _matrix);
	D3DMATRIX	GetTransform();

	bool	Begin();
	bool	End();
	bool	Draw(LPDIRECT3DTEXTURE9 _pTex, MRect* _pRect, MVector3* _pCenter, MVector3* _pPosition, D3DCOLOR _color);

	const LPD3DXSPRITE	GetSprite();

private:
	bool	CheckSpriteCreated();
};

#endif
