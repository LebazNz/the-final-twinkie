#include "ObjectManager.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager* CObjectManager::GetInstance(void)
{
	if(m_pInstance == nullptr)
		m_pInstance = new CObjectManager();
	return m_pInstance;
}
void CObjectManager::DeleteInstance(void)
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}


CObjectManager::CObjectManager(void)
{
}


CObjectManager::~CObjectManager(void)
{
}


void CObjectManager::UpdateAllObjects(float fDt)
{

}
void CObjectManager::AddObjects(IEntity* pObjects)
{

}
void CObjectManager::RemoveObject(IEntity* pObject)
{
}
void CObjectManager::RemoveAllObjects(void)
{
}
void CObjectManager::CheckCollisions(void)
{
}