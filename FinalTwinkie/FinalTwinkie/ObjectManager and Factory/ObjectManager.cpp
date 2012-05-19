#include "ObjectManager.h"
#include "../GameObjects/Entity.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager* CObjectManager::GetInstance(void)
{
	if(m_pInstance == nullptr)
		m_pInstance = new CObjectManager;
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
	vector< IEntity* >::iterator iter;

	for(iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		(*iter)->Update(fDt);
	}
}

void CObjectManager::AddObject(IEntity* pObject)
{
	if( pObject == nullptr)
		return;

	pObject->AddRef();

	m_vObjectList.push_back(pObject);
}

void CObjectManager::RemoveObject(IEntity* pObject)
{
	if(pObject == nullptr)
		return;

	vector< IEntity* >::iterator iter;

	for(iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		if((*iter) == pObject)
		{
			(*iter)->Release();

			iter = m_vObjectList.erase(iter);
			break;
		}
	}

}

void CObjectManager::RemoveAllObjects(void)
{
	vector< IEntity* >::iterator iter;
	for( iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		(*iter)->Release();
	}

	m_vObjectList.clear();
}

void CObjectManager::CheckCollisions(void)
{
	vector< IEntity* >::iterator iCollider;
	vector< IEntity* >::iterator iOtherObject;

	for(iCollider = m_vObjectList.begin(); iCollider != m_vObjectList.end(); iCollider++)
	{
		for( iOtherObject = m_vObjectList.begin(); iOtherObject != m_vObjectList.end(); ++iOtherObject )
		{
			if( (*iCollider)->GetType() == (*iOtherObject)->GetType() )
				continue;

			if( (*iCollider)->CheckCollision( (*iOtherObject) ) )
			{
				break;
			}
		}
	}
}

void CObjectManager::RenderAllObjects(void)
{
	vector< IEntity* >::iterator iter;

	for(iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		(*iter)->Render();
	}
}