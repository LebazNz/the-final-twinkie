#include "Tree.h"
#include "../GameObjects/Player.h"
#include "../Event and Messages/MessageSystem.h"
#include "../GameObjects/Enemy.h"
#include "../Event and Messages/DestroyTreeMessage.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CTree::CTree(void)
{
	m_nType = OBJ_TREE;
	m_bHit = false;
}


CTree::~CTree(void)
{
}



bool CTree::CheckCollision(IEntity* pObject)
{
	if(m_bHit == true)
		return false;

	if(CEntity::CheckCollision(pObject) == true)
	{
		switch(pObject->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{	
				CPlayer* pPlayer = CPlayer::GetInstance();
				// MAKE PLAYER SLOW DOWN
			

				m_bHit = true;
			}
			break;
		case OBJ_ENEMY:
			{
				if(pObject->GetType() == OBJ_TANK)
				{
					// MAKE ENEMY SLOW DOWN

					m_bHit = true;
				}
				else
				{
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObject);
					pEnemy->SetPosX(pEnemy->GetOldPos().fX);
					pEnemy->SetPosY(pEnemy->GetOldPos().fY);
				}
			}
			break;

		default:
			{

			}
			break;
		};
		return true;
	}
	else
		return false;
}


void CTree::Render(void)
{
	Camera* C = Camera::GetInstance();
	if(m_bHit == false)
	{
		if(GetImageID() != -1)
		{
			CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2);
		}
	}
	else if(m_bHit == true)
	{
		if(hitImageID != -1)
		{
			CSGD_TextureManager::GetInstance()->Draw(hitImageID, (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2);
		}
	}
}