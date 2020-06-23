#include "cMd3dDevice.h"
#include "cMSystemManager.h"
#include "defines.h"

cMd3dDevice::cMd3dDevice()
{
	m_pD3d		= NULL;
	m_pDevice	= NULL;
}

cMd3dDevice::~cMd3dDevice()
{
}

bool cMd3dDevice::Cleanup()
{
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3d);

	return false;
}

bool cMd3dDevice::CreateDevice()
{
	m_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d == NULL)
	{
		
		return FALSE;
	}

	return false;
}

bool cMd3dDevice::DestroyDevice()
{
	return false;
}

LPDIRECT3DDEVICE9 cMd3dDevice::GetDevice()
{
	return LPDIRECT3DDEVICE9();
}
