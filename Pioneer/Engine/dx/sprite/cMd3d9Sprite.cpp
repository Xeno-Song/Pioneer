#include "cMd3d9Sprite.h"
#include "../../sys/cMsysManager.h"

#ifndef __DX_VERSION_11__

cMd3dSprite::cMd3dSprite()
{
	m_pSprite = NULL;
}

cMd3dSprite::~cMd3dSprite()
{
	Cleanup();
}
/**
* @brief	Create directx sprite object
* @details	Sprite object is used to draw images
* @return	If success to create object, return true, otherwise return false
*/
bool cMd3dSprite::Create()
{
	HRESULT hResult = S_OK;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = MGetSystem()->GetD3dManager()->GetDevice();

	hResult = D3DXCreateSprite(pDevice, &m_pSprite);
	if (FAILED(hResult))
	{
		MGetSystem()->GetD3dManager()->SetLastError(E_D3DERR::D3DERR_SPRITE_CREATE_FAILED, hResult);
		return false;
	}

	return true;
}

/**
* @brief	Delete directx sprite object
* @details	If sprite object created, delete object
*/
void cMd3dSprite::Cleanup()
{
	SAFE_RELEASE(m_pSprite);
}

bool cMd3dSprite::SetTransform(D3DXMATRIX* _matrix)
{
	if (!CheckSpriteCreated())	return false;

	HRESULT hResult;
	hResult = m_pSprite->SetTransform(_matrix);

	if (FAILED(hResult))
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_SPRITE_TRANSFORM_MATRIX_SET_FAILED, hResult);
		return false;
	}

	return true;
}

D3DMATRIX cMd3dSprite::GetTransform()
{
	if (!CheckSpriteCreated())	return D3DXMATRIX();

	HRESULT hResult = S_OK;
	D3DXMATRIX matrix;
	hResult = m_pSprite->GetTransform(&matrix);

	if (FAILED(hResult))
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_SPRITE_TRANSFORM_MATRIX_GET_FAILED, hResult);
		return D3DXMATRIX();
	}

	return matrix;
}

bool cMd3dSprite::Begin()
{
	if (!CheckSpriteCreated())	return false;
	
	HRESULT hResult;
	hResult = m_pSprite->Begin(
		D3DXSPRITE_ALPHABLEND || 
		D3DXSPRITE_SORT_TEXTURE ||
		D3DXSPRITE_SORT_DEPTH_FRONTTOBACK
	);

	if (hResult != S_OK)
	{
		MGetSystem()->GetD3dManager()->SetLastError(E_D3DERR::D3DERR_SPRITE_BEGIN_FAILED, hResult);
		return false;
	}

	return true;
}

bool cMd3dSprite::End()
{
	if (!CheckSpriteCreated())	return false;

	HRESULT hResult;
	hResult = m_pSprite->End();

	if (hResult != S_OK)
	{
		MGetSystem()->GetD3dManager()->SetLastError(E_D3DERR::D3DERR_SPRITE_END_FAILED, hResult);
		return false;
	}

	return true;
}

bool cMd3dSprite::Draw(LPDIRECT3DTEXTURE9 _pTex, MRect * _pRect, MVector3 * _pCenter, MVector3 * _pPosition, D3DCOLOR _color)
{
	if (!CheckSpriteCreated())	return false;

	D3DXVECTOR3 vecCenter = _pCenter->GetDxVector3();
	D3DXVECTOR3 vecPos = _pPosition->GetDxVector3();
	RECT		rcRect = _pRect->GetRect();

	HRESULT hResult = m_pSprite->Draw(_pTex, &rcRect, &vecCenter, &vecPos, _color);
	if (FAILED(hResult))
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_SPRITE_DRAW_FAILED, hResult);
		return false;
	}

	return true;
}

const LPD3DXSPRITE cMd3dSprite::GetSprite()
{
	if (!CheckSpriteCreated())	return NULL;

	return m_pSprite;
}

bool cMd3dSprite::CheckSpriteCreated()
{
	if (m_pSprite == NULL)
	{
		MGetSystem()->GetD3dManager()->SetLastError(D3DERR_SPRITE_NOT_CREATED, NULL);
		return false;
	}
	return true;
}

#endif