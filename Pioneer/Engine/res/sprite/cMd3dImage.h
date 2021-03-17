#pragma once

#ifndef __M_D3D_IMAGE_H__
#define __M_D3D_IMAGE_H__

class cMd3dImage
{
public:
	cMd3dImage();
	virtual ~cMd3dImage();

public:
	void LoadImageFromFile();
	void LoadImageFromBuffer();
	void Cleanup();

	void Render();
};

#endif