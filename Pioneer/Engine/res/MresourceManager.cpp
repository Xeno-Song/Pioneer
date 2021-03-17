#include "MresourceManager.h"

MResourceManager::MResourceManager()
{
}

MResourceManager::~MResourceManager()
{
}

void MResourceManager::Initialize()
{
    const int IMG_MAX = ResourceNumber::IMG_RES_MAX;

    // Create empty map to load index anywhere
    for (int i = 0; i < IMG_MAX; i++)
        m_imageResourceMap.emplace(MCreateImageResourcePair(i, nullptr));

    m_sprite = new cMd3dSprite();
    m_sprite->Create();
}

void MResourceManager::LoadResourceDatas()
{
}

void MResourceManager::LoadResource(ResourceNumber::ImageResourceNumber imageResNum)
{
    cMd3dImage* image = new cMd3dImage();
    
}

void MResourceManager::UnloadResource(ResourceNumber::ImageResourceNumber imageResNum)
{
}

cMd3dImage* MResourceManager::GetResource(ResourceNumber::ImageResourceNumber imageResNum)
{
    if (imageResNum >= ResourceNumber::IMG_RES_MAX)
        return nullptr;

    return m_imageResourceMap.find(imageResNum)->second;
}

void MResourceManager::LoadAllImageResource()
{
    const int IMG_MAX = ResourceNumber::IMG_RES_MAX;

    for (int i = 0; i < IMG_MAX; i++)
        LoadResource((ResourceNumber::ImageResourceNumber)i);
}
