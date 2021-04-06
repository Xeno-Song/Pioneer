#pragma once

#ifndef __M_C_D3D11_MODEL_H__
#define __M_C_D3D11_MODEL_H__

#include "../../Mdefines.h"
#ifdef __DX_VERSION_11__

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10math.h>

class Md3d11Model
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
	
public:
	Md3d11Model();
	Md3d11Model(const Md3d11Model&);
	~Md3d11Model();

	bool	Initialize(ID3D11Device* device);
	void	Cleanup();
	void	Render(ID3D11DeviceContext* deviceContext);

	int		GetIndexCount() const;

private:
	bool	InitializeBuffers(ID3D11Device* device);
	void	CleanupBuffers();
	void	RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	ID3D11Buffer*	m_vertexBuffer;
	ID3D11Buffer*	m_indexBuffer;
	int				m_vertexCount;
	int				m_indexCount;
};

#endif
#endif