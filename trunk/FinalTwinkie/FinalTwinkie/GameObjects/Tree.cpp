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
	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
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

	if(GetHealth() < GetMaxHealth())
	{
		//Health
		RECT rect;
		rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+C->GetPosX(), (GetPosY()-40)+C->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+C->GetPosX(), (GetPosY()-40)+C->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+C->GetPosX(), (GetPosY()-40)+C->GetPosY(), 0.5f,0.5f,&rect);
	}

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