#pragma once

#include "cMSystemManager.h"

//!Get M-Engine main system manager
#define MGetSystem()	cMSystemManager::GetManager()

//DxControls
/**
* @brief	Get M-Engine DirectX Maanger
* @return	cMd3dManager*
*/
#define MDxGetManager()			cMSystemManager::GetD3dManager()

//!Get DirectX device control
#define MDxGetDeviceControl()	MDxGetManager()->GetDeviceControl()
//!Get DirectX device
#define MDxGetDevice()			MDxGetManager()->GetDevice()

//!Get DirectX sprite control
#define MDxGetSpriteControl()	MDxGetManager()->GetSpriteControl()
//!Get DirectX sprite
#define MDxGetSprite()			MDxGetManager()->GetSprite()

//!Begin to use dx sprite
//!Before using MDxSpriteDraw, call this function
#define MDxSpriteBegin()		MDxGetSpriteControl()->Begin()
//!Sprite use end
#define MDxSpriteEnd()			MDxGetSpriteControl()->End()

//!Draw texture with dx sprite
//!	LPDIRECT3DTEXTURE9	_pTexture
//!	cMRect*			_pRect
//!	cMVector3*	_pCenter
//!	cMVector3*	_pPosition
//!	D3DCOLOR	_colorKey
#define MDxSpriteDraw(_pTexture, _pRect, _pCenter, _pPosition, _colorKey) \
		MDxGetSpriteControl()->Draw(_pTexture, _pRect, _pCenter, _pPosition, _colorKey)

//!Get last occured error in Direct X
//!	E_D3DERR*		_pError
//!	HRESULT*		_pResult
#define MDxGetGetLastError(_pError, _pResult)	MDxGetManager()->GetLastError(_pError, _pResult)
//!Clear last error in DirectX
#define	MDxClearLastError()		MDxGetManager()->ClearError()
