#include "Tree.h"
#include "../GameObjects/Player.h"
#include "../Event and Messages/MessageSystem.h"
#include "../GameObjects/Enemy.h"
#include "../Event and Messages/DestroyTreeMessage.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../GameObjects/Tank.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
CTree::CTree(void)
{
	m_nType = OBJ_TREE;
	m_bHit = false;
	m_nSound = -1;
	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}


CTree::~CTree(void)
{
}



bool CTree::CheckCollision(IEntity* pObject)
{
	
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
				if(m_bHit == true)
					pPlayer->SlowVel(0.5f,(pPlayer->GetStartVelX()-20));
				else
				{
					if(m_nSound != -1)
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSound);
					pPlayer->SlowVel(0.5f,(pPlayer->GetStartVelX()/2));
					m_bHit = true;
					SetHit(true);
					SetWidth(32);
					SetHeight(32);
				}
			}
			break;
		case OBJ_ENEMY:
			{
				if(m_bHit == false)
				{
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObject);
					pEnemy->SetPosX(pEnemy->GetOldPos().fX);
					pEnemy->SetPosY(pEnemy->GetOldPos().fY);
				}
			}
			break;

		case OBJ_TANK:
			{
				// MAKE ENEMY SLOW DOWN
					CTank* pTank = dynamic_cast<CTank*>(pObject);
					if(m_bHit == true)
						pTank->SlowVel(0.5f,pTank->GetStartVelX()-15);
					else
					{
						if(m_nSound != -1)
							CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSound);
						pTank->SlowVel(0.5f,pTank->GetStartVelX()/2);
						m_bHit = true;
						SetHit(true);
						SetWidth(32);
						SetHeight(32);
					}
			}
			break;

		case OBJ_PICKUP:
			{
				return false;
			}
			break;

		default:
			{

			}
			break;
		};
		return false;
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
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+C->GetPosX()), (int)((GetPosY()-40)+C->GetPosY()), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+C->GetPosX()), (int)((GetPosY()-40)+C->GetPosY()), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+C->GetPosX()), (int)((GetPosY()-40)+C->GetPosY()), 0.5f,0.5f,&rect);
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
