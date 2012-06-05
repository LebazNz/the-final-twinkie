#include "Bullet.h"
#include "../Headers/Game.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Event and Messages/DestroyBulletMessage.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include "../Event and Messages/DestroyBuildingMessage.h"
#include "../Event and Messages/DestroyTreeMessage.h"
#include "../GameStates/OptionsState.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"
#include "Enemy.h"
#include "Player.h"
#include "Turret.h"
#include "Tank.h"
#include "Building.h"
#include "Tree.h"

#include "../SGD Wrappers/CSGD_DirectInput.h"

CBullet::CBullet(void)
{
	m_nType = OBJ_BULLET;
	// bool for who fired the bullet
	// true		= player fired
	// false	= enemy fired
	m_bWhoFired = false;
	CEventSystem::GetInstance()->RegisterClient("play_explode",this);
	m_fRotation = 0.0f;
	m_fDamage = 0.0f;
	m_nType=0;
	m_fFlameTimer=0.0f;
	SetRect(&m_rTarget,0,0,0,0);
	m_fMissileTimer = 0.0f;
}

CBullet::~CBullet(void)
{
	CEventSystem::GetInstance()->UnregisterClient("play_explode",this);
}

void CBullet::Update(float fDT)
{
	Camera* C=Camera::GetInstance();
	RECT rSelf = GetRect();
	CGame* pGame = CGame::GetInstance();
	if((rSelf.bottom-C->GetPosY() < -C->GetPosY()|| rSelf.top-C->GetPosY() > pGame->GetHeight()-C->GetPosY() || rSelf.right-C->GetPosX() < -C->GetPosX() || rSelf.left-C->GetPosX() > pGame->GetWidth()-C->GetPosX() )&&m_nBulletType!=BUL_ROCKET)
	{
		CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
	if(m_nBulletType==BUL_FLAME)
	{
		m_fFlameTimer-=fDT;
		if(m_fFlameTimer<=0.0f)
		{
			CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
			CMessageSystem::GetInstance()->SndMessage(pMsg);
			pMsg = nullptr;
		}
	}
	if(m_nBulletType == BUL_ROCKET)
	{
		tVector2D Up={0,-1};
		tVector2D toTarget;
		this;
		toTarget.fX=((m_v2TargetPos.fX/*-C->GetPosX())*/-GetPosX()));
		toTarget.fY=((m_v2TargetPos.fY/*-C->GetPosY())*/-GetPosY()));
		tVector2D Look=Vector2DRotate(Up, m_fRotation);
		float Steer=Steering(toTarget, Look);
		if(Steer>0)
		{
			m_fRotation-=7.0f*fDT;
		}
		else if(Steer<0)
		{
			m_fRotation+=7.0f*fDT;
		}
		float vely=GetVelY();
		float DY=(Look.fY*GetVelY()*fDT);
		float DX=(Look.fX*GetVelX()*fDT);
		SetPosX(GetPosX()+DX);
		SetPosY(GetPosY()+DY);
		


		if(rSelf.bottom-C->GetPosY() < m_rTarget.bottom && rSelf.top-C->GetPosY() > m_rTarget.top 
			&& rSelf.right-C->GetPosX() < m_rTarget.right && rSelf.left-C->GetPosX() > m_rTarget.left )
		{
			CObjectManager::GetInstance()->AreaEffect(m_v2TargetPos.fX,m_v2TargetPos.fY,50,(int)m_fDamage);
			CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
			CMessageSystem::GetInstance()->SndMessage(pMsg);
			pMsg = nullptr;
		}
	}
	if(m_nBulletType == BUL_ARTILLERY)
	{
		if(rSelf.bottom-C->GetPosY() < m_rTarget.bottom-C->GetPosY() && rSelf.top-C->GetPosY() > m_rTarget.top-C->GetPosY() 
			&& rSelf.right-C->GetPosX() < m_rTarget.right-C->GetPosX() && rSelf.left-C->GetPosX() > m_rTarget.left-C->GetPosX() )
		{
			CObjectManager::GetInstance()->AreaEffect(m_v2TargetPos.fX,m_v2TargetPos.fY,100,(int)m_fDamage);
			CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
			CMessageSystem::GetInstance()->SndMessage(pMsg);
			pMsg = nullptr;
		}
	}
	if(m_nBulletType != BUL_ROCKET)
	{
		CEntity::Update(fDT);
	}
}

bool CBullet::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		if(m_nBulletType == BUL_ARTILLERY)
			return false;

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
					CPlayer::GetInstance()->SetDamageTaken((int)CPlayer::GetInstance()->GetDamageTaken()+m_fDamage);
				}
			}
			break;
		case OBJ_BULLET:
			break;
		case OBJ_TANK:
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
						CPlayer::GetInstance()->SetUnitsKilled(CPlayer::GetInstance()->GetUnitsKilled()+1);
						CPlayer::GetInstance()->SetScore(CPlayer::GetInstance()->GetScore()+100);
					}

					
				}
				CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			break;
		case OBJ_TURRET:
			{
				CTurret* pEnemy = dynamic_cast<CTurret*>(pBase);
				if(pEnemy->GetOwner() != nullptr)
					break;

				pEnemy->TakeDamage((int)this->m_fDamage);

				CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;

			}
			break;
			case OBJ_BUILDING:
			{
				if(GetWhoFired()==true)
				{
					CBuilding* pBuilding = dynamic_cast<CBuilding*>(pBase);
					pBuilding->TakeDamage((int)this->m_fDamage);
				}
				CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			break;
			case OBJ_ENEMY:
			{
				if(GetWhoFired()==true)
				{
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pBase);
					pEnemy->TakeDamage((int)this->m_fDamage);
					if(pEnemy->GetHealth() <= 0.0f)
					{
						CDestroyEnemyMessage* pMse = new CDestroyEnemyMessage(pEnemy);
						CMessageSystem::GetInstance()->SndMessage(pMse);
						pMse = nullptr;
						CPlayer::GetInstance()->SetScore(CPlayer::GetInstance()->GetScore()+50);
					}
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
					if(m_nBulletType==BUL_FLAME)
					{
						pEnemy->SetOnFire();
					}
				}
			}
			break;

			case OBJ_TREE:
				{
					CTree* pTree = dynamic_cast<CTree*>(pBase);
					//destroy tree
					CDestroyTreeMessage* pMsg = new CDestroyTreeMessage(pTree);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;

					CDestroyBulletMessage* pmsg = new CDestroyBulletMessage(this);
					CMessageSystem::GetInstance()->SndMessage(pmsg);
					pmsg = nullptr;
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
		CSGD_Direct3D::GetInstance()->DrawRect(m_rTarget, 255,0,0);
	}
}
