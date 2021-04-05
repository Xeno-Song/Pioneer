#include "cMd3d11Texture.h"
#include "../../sys/cMsysManager.h"

#ifdef __DX_VERSION_11__

TextureClass::TextureClass()
{
	m_texture = nullptr;
}

TextureClass::TextureClass(const TextureClass&)
{
}

TextureClass::~TextureClass()
{
	Cleanup();
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result = D3DX11CreateShaderResourceViewFromFileW(device, filename, nullptr, nullptr, &m_texture, nullptr);
	if (FAILED(result)) return false;

	return true;
}

void TextureClass::Cleanup()
{
	SAFE_RELEASE(m_texture);
}

ID3D11ShaderResourceView* TextureClass::GetTexture() const
{
	return m_texture;
}

#endif