#include "Bullet.h"
#include "Game.h"
#include "MessageSystem.h"
#include "EventSystem.h"
#include "DestroyBulletMessage.h"
#include "DestroyEnemyMessage.h"
#include "OptionsState.h"
#include "Camera.h"

CBullet::CBullet(void)
{
	m_nType = OBJ_BULLET;
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	m_bWhoFired = false;
	CEventSystem::GetInstance()->RegisterClient("play_explode",this);
	m_fRotation = 0.0f;
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
	if(rSelf.bottom < -C->GetPosY()|| rSelf.top > pGame->GetHeight()-C->GetPosY() || rSelf.right < -C->GetPosX() || rSelf.left > pGame->GetWidth()-C->GetPosX() )
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
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), int(GetPosX()+(GetWidth()/2)+C->GetPosX()), int(GetPosY()+(GetHeight()/2)+C->GetPosY()), 0.75f, 0.75f, nullptr, float(GetWidth()/2), float(GetHeight()/2), m_fRotation, GetColor()); 
	}
}
