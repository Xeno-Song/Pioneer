#pragma once

#ifndef __M_RESOURCE_MANAGER_H__
#define __M_RESOURCE_MANAGER_H__

#include <map>
#include "../dx/sprite/cMd3d9Sprite.h"
#include "sprite/cMd3dImage.h"
#include "../ResourceList.h"

#define MCreateImageResourcePair(num, ptr) std::pair<ResourceNumber::ImageResourceNumber, cMd3dImage*>((ResourceNumber::ImageResourceNumber)num, ptr)

class MResourceManager
{
public:
	MResourceManager();
	virtual ~MResourceManager();

public:
	void Initialize();
	
	void LoadResourceDatas();

	void LoadResource(ResourceNumber::ImageResourceNumber imageResNum);
	void UnloadResource(ResourceNumber::ImageResourceNumber imageResNum);
	cMd3dImage* GetResource(ResourceNumber::ImageResourceNumber imageResNum);

	void LoadAllImageResource();


private:
	cMd3dSprite* m_sprite;
	std::map<ResourceNumber::ImageResourceNumber, cMd3dImage*> m_imageResourceMap;
};

#endif