#include "MObjectManager.h"

MObjectManager::MObjectManager()
{
    m_uidCount = 0;
    m_objectMap.clear();
}

MObjectManager::~MObjectManager()
{
}

void MObjectManager::RegisterNewObject(MObject* obj, int uid)
{
    m_objectMap.insert(std::make_pair(uid, obj));
}

void MObjectManager::UnregisterObject(int uid)
{
    m_objMapDelMutex.lock();
    m_objectMap.erase(uid);
    m_objMapDelMutex.unlock();
}

// Unique ID create with vertification
unsigned int MObjectManager::CreateNewUID()
{
    unsigned int uidValue;

    m_uidCountMutex.lock();
    
    while (m_objectMap.count(m_uidCount) != 0)
        m_uidCount++;
    uidValue = m_uidCount++;

    m_uidCountMutex.unlock();

    return uidValue;
}
