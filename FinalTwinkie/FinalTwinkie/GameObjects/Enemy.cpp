#include "Enemy.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Headers/Game.h"
#include "../Headers/Camera.h"

CEnemy::CEnemy(void)
{
	m_nType = OBJ_ENEMY;
	m_fMaxDist = 0;
	m_fMinDist = 0;
	m_nMainBulletType = BUL_SHELL;
	m_nMachineGunBulletType = BUL_MACHINEGUN;
	m_fFireRate = 0;
	CEventSystem::GetInstance()->RegisterClient("play_explode",this);
	SetHealth(3000);
}

CEnemy::~CEnemy(void)
{
	CEventSystem::GetInstance()->UnregisterClient("play_explode",this);
}

void CEnemy::Update(float fDt)
{
	float nY = GetPosY();
	nY++;
	SetPosY(nY);
	m_pTail->UpdateEmitterPos(GetPosX(), GetPosY());	float hp = GetHealth();
	if(hp > 0)
	{
		SetHealth(hp-5);
	}
	else
	{
		CDestroyEnemyMessage* pMsg = new CDestroyEnemyMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}

void CEnemy::Render(void)
{
	if(GetImageID() != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw( GetImageID(), 
					int(GetPosX()), int(GetPosY()), 1.0f, 1.0f, nullptr, 
					GetWidth()/2.0f, GetHeight()/2.0f, 0, 
					DWORD(GetColor()) );
	}
}

bool CEnemy::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
			}
			break;
		case OBJ_BULLET:
			{				
					CDestroyEnemyMessage* pMsg = new CDestroyEnemyMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
			}
			break;
		case OBJ_ENEMY:
			{
			}
			break;
		};
		return true;
	}
	else
		return false;
}

void CEnemy::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetParam() != this)
		return;

	if(pEvent->GetEventID() == "play_explode")
	{
		CGame::GetInstance()->system->playSound(FMOD_CHANNEL_FREE,CGame::GetInstance()->sound,false,&CGame::GetInstance()->channel);
	}
}

RECT CEnemy::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.bottom=(GetPosY()+C->GetPosY())-GetHeight();
	rect.top=(GetPosY()+C->GetPosY())+GetHeight();
	rect.left=(GetPosX()+C->GetPosX())-GetWidth();
	rect.right=(GetPosX()+C->GetPosX())+GetWidth();
	return rect;
}
