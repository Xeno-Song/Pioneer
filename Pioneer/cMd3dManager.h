#pragma once

#ifndef __M_C_D3DMANAGER_H__
#define __M_C_D3DMANAGER_H__

#include "ErrorCodes.h"

class cMd3dManager
{
public:
	cMd3dManager();
	virtual ~cMd3dManager();

private:
	E_D3dError		m_lastError;

public:
	bool GetLastError(E_D3dError* _pError);
	void SetLastError(E_D3dError _pError);
};

#endif