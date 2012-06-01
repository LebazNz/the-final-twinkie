#include "ObjectManager.h"
#include "../GameObjects/Entity.h"
#include "../World and Tile/TileManager.h"
#include "../GameObjects/Player.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Tank.h"

#include <math.h>
CObjectManager* CObjectManager::m_pInstance = nullptr;

struct point{float x, y;};

float getDistance(point &x, point &y)
{
    float distance, tempx, tempy;
    tempx = (y.x - x.x);
    tempx = pow(tempx, 2.0f);
    tempy = (y.y - x.y);
    tempy = pow(tempy, 2.0f);
    distance = tempx + tempy;
    distance = sqrt(distance);
    return distance;
}


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
			if(iCollider==iOtherObject)
				continue;

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


void CObjectManager::AreaEffect(float x, float y, int radius, int damage)
{
	CPlayer *pPlayer = CPlayer::GetInstance();
	
	// For arc we will need to take turret rotation into effect 
	
	Camera  *pCam = Camera::GetInstance();
	//x += pCam->GetPosX();
	//y += pCam->GetPosY();
	point pos; pos.x = x; pos.y = y;
	vector< IEntity* >::iterator iter;
	

	for(iter = m_vObjectList.begin(); iter != m_vObjectList.end(); iter++)
	{
		CEntity* m_pTarget = dynamic_cast<CEntity*>(*iter);
		if(m_pTarget->GetType() == OBJ_PLAYER)
			continue;

		if(m_pTarget->GetPosX()+pCam->GetPosX() >= -100 && m_pTarget->GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && m_pTarget->GetPosY()+pCam->GetPosY() >= -100 && m_pTarget->GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
		{
			RECT rect = m_pTarget->GetRect();
				point a, b, c, d;
				
				a.x = (float)rect.left; b.x = (float)rect.left;
				a.y = (float)rect.bottom; b.y = (float)rect.top;
				c.x = (float)rect.right; d.x = (float)rect.right;
				c.y = (float)rect.top; d.y = (float)rect.bottom;
				float e,f,g,h;
				e = getDistance(pos,a);
				f = getDistance(pos,b);
				g = getDistance(pos,c);
				h = getDistance(pos,d);

				if(e <= radius || f <= radius || g <= radius || h <= radius)
				{
					

					switch(m_pTarget->GetType())
					{
					case OBJ_ENEMY:
						{
							CEnemy* pEnemy = dynamic_cast<CEnemy*>(m_pTarget);
							pEnemy->TakeDamage(damage);
								if(pEnemy->GetHealth() <= 0.0f)
								{
									if(pEnemy->GetHasATuert())
									{
										CTurret* pTurret = dynamic_cast<CTank*>(pEnemy)->GetTurret();
										CDestroyTurretMessage* pMst = new CDestroyTurretMessage(pTurret);
										CMessageSystem::GetInstance()->SndMessage(pMst);
										pMst = nullptr;
									}
									CDestroyEnemyMessage* pMse = new CDestroyEnemyMessage(pEnemy);
									CMessageSystem::GetInstance()->SndMessage(pMse);
									pMse = nullptr;
								}
						}
						break;
					case OBJ_TURRET:
						{
							CTurret* pTurret = dynamic_cast<CTurret*>(m_pTarget);
							if(pTurret->GetOwner() == nullptr)
							{
								pTurret->TakeDamage(damage);
							}
						}
						break;
						
					case OBJ_BUILDING:
						{
							m_pTarget->TakeDamage(damage);
						}
						break;
						
					default:
						{} break;

					}
				}
		}
	
	}

}