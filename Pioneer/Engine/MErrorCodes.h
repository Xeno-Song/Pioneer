#pragma once

#ifndef __M_ERROR_CODES_H__
#define __M_ERROR_CODES_H__

typedef enum E_D3DERR
{
	D3DERR_NONE,

	D3DERR_DIRECT3D9_CREATE_FAILED,

	D3DERR_DEVICE_NOT_CREATED,
	D3DERR_DEVICE_CANNOT_LOAD_ADAPTER_LIST,
	D3DERR_DEVICE_WINDOW_IS_NOT_CREATED,
	D3DERR_DEVICE_CREATE_FAILED,

	D3DERR_SPRITE_NOT_CREATED,
	D3DERR_SPRITE_CREATE_FAILED,
	D3DERR_SPRITE_BEGIN_FAILED,
	D3DERR_SPRITE_END_FAILED,
	D3DERR_SPRITE_DRAW_FAILED,
	D3DERR_SPRITE_TRANSFORM_MATRIX_SET_FAILED,
	D3DERR_SPRITE_TRANSFORM_MATRIX_GET_FAILED,

} E_D3DERR;

#endif 