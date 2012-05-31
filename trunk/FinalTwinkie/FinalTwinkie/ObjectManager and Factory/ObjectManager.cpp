#include "ObjectManager.h"
#include "../GameObjects/Entity.h"
#include "../World and Tile/TileManager.h"
#include "../GameObjects/Player.h"
#include "../source/Camera.h"
#include "../source/Game.h"
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
	m_pTile = CTileManager::GetInstance();
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
			/*if( (*iCollider)->GetType() == (*iOtherObject)->GetType() )
				continue;*/

			if( (*iCollider)->CheckCollision( (*iOtherObject) ) )
			{
				break;
			}
		}
		m_pTile->CheckCollision(*iCollider);
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


void CObjectManager::AreaEffect(int x, int y, int radius, int damage, bool arc)
{
	CPlayer *pPlayer = CPlayer::GetInstance();
	
	// For arc we will need to take turret rotation into effect 

	Camera  *pCam = Camera::GetInstance();
	int playerX = pCam->GetPosX() + CGame::GetInstance()->GetWidth()/2;
	int playerY = pCam->GetPosY() + CGame::GetInstance()->GetHeight()/2;

	/*float xPos = GetPosX() - (m_pTarget->GetPosX()-C->GetPosX());
	float yPos = GetPosY() - (m_pTarget->GetPosY()-C->GetPosY());
	xPos *= xPos;
	yPos *= yPos;

	float distance = sqrt(float(xPos+yPos));*/


	vector< IEntity* >::iterator iter;

	for(iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		CEntity* m_pTarget = dynamic_cast<CEntity*>(*iter);
		if(m_pTarget->GetPosX() >= 0 && m_pTarget->GetPosX() <= CGame::GetInstance()->GetWidth() && m_pTarget->GetPosY() >= 0 && m_pTarget->GetPosY() <= CGame::GetInstance()->GetHeight())
		{

			/*float xPos = ((pTarget->GetPosX()) - ((m_vTiles[i][j].GetPosX()+cam->GetPosX())+m_vTiles[i][j].GetWidth()/2));
			float yPos = ((pTarget->GetPosY()) - ((m_vTiles[i][j].GetPosY()+cam->GetPosY())+m_vTiles[i][j].GetHeight()/2));
			xPos *= xPos;
			yPos *= yPos;

			float distance = sqrt(xPos+yPos);

			if(pBase->GetType() != OBJ_PLAYER)
				continue;*/


		}
	
	}

}