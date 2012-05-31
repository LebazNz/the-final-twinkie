#include "Bullet.h"
#include "../Headers/Game.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Event and Messages/DestroyBulletMessage.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include "../Event and Messages/DestroyBuildingMessage.h"
#include "../GameStates/OptionsState.h"
#include "../Headers/Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Turret.h"
#include "Tank.h"
#include "Building.h"

#include "../SGD Wrappers/CSGD_DirectInput.h"

CBullet::CBullet(void)
{
	m_nType = OBJ_BULLET;
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	m_bWhoFired = false;
	CEventSystem::GetInstance()->RegisterClient("play_explode",this);
	m_fRotation = 0.0f;
	m_fDamage = 0.0f;
}

CBullet::~CBullet(void)
{
	CEventSystem::GetInstance()->UnregisterClient("play_explode",this);
}

void CBullet::Update(float fDT)
{
	CEntity::Update(fDT);
	Camera* C=Camera::GetInstance();
	RECT rSelf = GetRect();
	CGame* pGame = CGame::GetInstance();
	if(rSelf.bottom-C->GetPosY() < -C->GetPosY()|| rSelf.top-C->GetPosY() > pGame->GetHeight()-C->GetPosY() || rSelf.right-C->GetPosX() < -C->GetPosX() || rSelf.left-C->GetPosX() > pGame->GetWidth()-C->GetPosX() )
	{
		CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}

bool CBullet::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
				if(GetWhoFired() == false)
				{
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(pBase);
					pPlayer->TakeDamage((int)this->m_fDamage);
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
			}
			break;
		case OBJ_BULLET:
			break;
		case OBJ_ENEMY:
			{
				if(GetWhoFired() == true)
				{
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pBase);
					pEnemy->TakeDamage((int)this->m_fDamage);
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
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
			}
			break;
			case OBJ_BUILDING:
			{
				if(GetWhoFired()==true)
				{
					CBuilding* pBuilding = dynamic_cast<CBuilding*>(pBase);
					pBuilding->TakeDamage((int)this->m_fDamage);
					if(pBuilding->GetHealth()<=0)
					{
						CDestroyBuildingMessage* pMst=new CDestroyBuildingMessage(pBuilding);
						CMessageSystem::GetInstance()->SndMessage(pMst);
						pMst=nullptr;
					}
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
			}
			break;
		};
		return true;
	}
	else
		return false;
}

void CBullet::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetParam() != this)
		return;

	if(pEvent->GetEventID() == "play_explode")
	{
		
		CGame::GetInstance()->system->playSound(FMOD_CHANNEL_FREE,CGame::GetInstance()->sound,false,&CGame::GetInstance()->channel);
		CGame::GetInstance()->channel->setVolume(COptionsState::GetInstance()->GetSFXVolume());

	}
}

void CBullet::Render(void)
{
	Camera* C=Camera::GetInstance();
	if(GetImageID() != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), int(GetPosX()-(GetWidth()/2)+C->GetPosX()), int(GetPosY()-(GetHeight()/2)+C->GetPosY()), 1.0f, 1.0f, nullptr, float(GetWidth()/2), float(GetHeight()/2), m_fRotation, GetColor()); 
		CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 255,0,0);
	}
}
