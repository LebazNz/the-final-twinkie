#include "Bullet.h"
#include "Game.h"
#include "MessageSystem.h"
#include "EventSystem.h"
#include "DestroyBulletMessage.h"
#include "DestroyEnemyMessage.h"


CBullet::CBullet(void)
{
	m_nType = OBJ_BULLET;
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	m_bWhoFired = false;
	CEventSystem::GetInstance()->RegisterClient("play_explode",this);
}

CBullet::~CBullet(void)
{
	CEventSystem::GetInstance()->UnregisterClient("play_explode",this);
}

void CBullet::Update(float fDT)
{
	CEntity::Update(fDT);

	RECT rSelf = GetRect();
	CGame* pGame = CGame::GetInstance();
	if(rSelf.bottom < 0 || rSelf.top > pGame->GetHeight() || rSelf.right < 0 || rSelf.left > pGame->GetWidth())
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
				else
					break;
			}
			break;
		case OBJ_BULLET:
			break;
		case OBJ_ENEMY:
			{
				CEventSystem::GetInstance()->SendEvent("play_explode",this);

				if(GetWhoFired() == false)
				{
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				else
					break;
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
	}
}
