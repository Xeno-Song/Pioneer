#pragma once

#ifndef __CM_D3D_11_TEXTURE_H__
#define __CM_D3D_11_TEXTURE_H__

#include "../../Mdefines.h"

#ifdef __DX_VERSION_11__

#include <d3d11.h>
#include <d3dx11.h>
#include "../../util/math/Mmath.h"

class TextureClass {
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device* device, WCHAR* filename);
	void Cleanup();

	ID3D11ShaderResourceView*	GetTexture() const;

private:
	ID3D11ShaderResourceView*	m_texture;
};

#endif
#endif