#include "MObjectManager.h"

MObjectManager::MObjectManager()
{
    m_uidCount = 0;
    Cleanup();
}

MObjectManager::~MObjectManager()
{
    Cleanup();
}

void MObjectManager::RegisterNewObject(MObject* obj, UID uid)
{
    m_objectMap.insert(std::make_pair(uid, obj));
}

void MObjectManager::UnregisterObject(UID uid)
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

void MObjectManager::Cleanup()
{
    m_objectMap.clear();
}

std::map<UID, MObject*>::iterator MObjectManager::GetBeginIterator()
{
    return m_objectMap.begin();
}

void MObjectManager::LockDelMutex()
{
    m_objMapDelMutex.lock();
}

void MObjectManager::UnlockDelMutex()
{
    m_objMapDelMutex.unlock();
}