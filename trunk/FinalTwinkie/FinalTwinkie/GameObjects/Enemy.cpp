#include "Enemy.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Event and Messages/SoldierFireMessage.h"
#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Headers/Game.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../GameObjects/Tank.h"
#include "../GameObjects/Turret.h"
#include "../GameObjects/Sapper.h"

CEnemy::CEnemy(void)
{
	m_nType = OBJ_ENEMY;
	m_nMainBulletType = BUL_SHELL;
	m_nMachineGunBulletType = BUL_MACHINEGUN;
	m_fFireRate = 0;
	CEventSystem::GetInstance()->RegisterClient("explode",this);
	SetHealth(35);
	m_bHasATurret = false;
	m_fRotation=0;
	m_pOnFire=nullptr;
	m_fTimer=0;
	m_fStopTimer = 0.0f;
	m_bStop = false;
	m_bOnFire=false;

	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}

CEnemy::~CEnemy(void)
{
	CEventSystem::GetInstance()->UnregisterClient("explode",this);
}

void CEnemy::Update(float fDt)
{
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
		if(GetType() == OBJ_HELP)
		{
			m_pTarget = CObjectManager::GetInstance()->GetTarget(this);

			CEntity* pTarget;
			if(m_pTarget!=nullptr)
			{
				if(m_pTarget->GetType() == OBJ_TANK)
					pTarget = dynamic_cast<CTank*>(m_pTarget);
				else if(m_pTarget->GetType() == OBJ_TURRET)
					pTarget = dynamic_cast<CTurret*>(m_pTarget);
				else if(m_pTarget->GetType() == OBJ_ENEMY)
					pTarget = dynamic_cast<CEnemy*>(m_pTarget);
				else if(m_pTarget->GetType() == OBJ_PLAYER)
					pTarget = dynamic_cast<CPlayer*>(m_pTarget);
				

				Camera* C=Camera::GetInstance();
				tVector2D Up = {0,-1};
				tVector2D toTarget;
				toTarget.fX=((pTarget->GetPosX())/*-C->GetPosX())*/-(GetPosX()));
				toTarget.fY=((pTarget->GetPosY())/*-C->GetPosY())*/-(GetPosY()));


				if(m_nEType==RIFLE||m_nEType==ROCKET)
				{
					tVector2D Up={0,-1};
					tVector2D toTarget;
					toTarget.fX=((pTarget->GetPosX())/*-C->GetPosX())*/-(GetPosX()));
					toTarget.fY=((pTarget->GetPosY())/*-C->GetPosY())*/-(GetPosY()));
					m_fRotation=AngleBetweenVectors(toTarget, Up);
					if(pTarget->GetPosX()<(GetPosX()+C->GetPosX()))
					{
						m_fRotation=-m_fRotation;
					}
					tVector2D Look=Vector2DRotate(Up, m_fRotation);
					if(Vector2DLength(toTarget)>m_fMinDist)
					{
						float DY=(Look.fY*GetVelY()*fDt);
						float DX=(Look.fX*GetVelX()*fDt);
						m_v2OldPos.fX = GetPosX();
						m_v2OldPos.fY = GetPosY();
						SetPosX(GetPosX()+DX);
						SetPosY(GetPosY()+DY);
					}
					if(m_nEType==RIFLE)
					{
						if(Vector2DLength(toTarget)<=m_fMaxDist)
						{
							if(m_fTimer>=m_fShotTimer)
							{
								SoldierFireMessage* msg=new SoldierFireMessage(MSG_SOLDIERFIRE, BUL_SHELL, this);
								CMessageSystem::GetInstance()->SndMessage(msg);
								m_fTimer=0;
							}
							else
								m_fTimer+=fDt;
						}
					}
					else if(m_nEType==ROCKET)
					{
						if(m_fTimer>=m_fShotTimer)
						{
							SoldierFireMessage* msg=new SoldierFireMessage(MSG_SOLDIERFIRE, BUL_ROCKET, this);
							CMessageSystem::GetInstance()->SndMessage(msg);
							m_fTimer=0;
						}
						else
							m_fTimer+=fDt;
					}
					if(m_bOnFire)
					{
						m_fFireTimer-=fDt;
						if(m_fFireTimer<=0)
						{
							TakeDamage(3);
							m_bOnFire=false;
							m_pOnFire->DeactivateEmitter();
						}
						if(m_fFireTimer<=2&&!m_bHurt2)
						{
							TakeDamage(3);
							m_bHurt2=true;
						}
						if(m_fFireTimer<=4&&!m_bHurt1)
						{
							TakeDamage(3);
							m_bHurt1=true;
						}
					}
				}
			}
		}		
		else if(GetType() != OBJ_HELP && m_bStop == false)
		{
			Camera* C=Camera::GetInstance();
			tVector2D Up = {0,-1};
			tVector2D toTarget;
			toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
			toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));


			if(m_nEType==RIFLE||m_nEType==ROCKET)
			{
				tVector2D Up={0,-1};
				tVector2D toTarget;
				toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
				toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
				m_fRotation=AngleBetweenVectors(toTarget, Up);
				if(m_pPlayer->GetPosX()<(GetPosX()+C->GetPosX()))
				{
					m_fRotation=-m_fRotation;
				}
				tVector2D Look=Vector2DRotate(Up, m_fRotation);
				if(Vector2DLength(toTarget)>m_fMinDist)
				{
					float DY=(Look.fY*GetVelY()*fDt);
					float DX=(Look.fX*GetVelX()*fDt);
					m_v2OldPos.fX = GetPosX();
					m_v2OldPos.fY = GetPosY();
					SetPosX(GetPosX()+DX);
					SetPosY(GetPosY()+DY);
				}
				if(m_nEType==RIFLE)
				{
					if(Vector2DLength(toTarget)<=m_fMaxDist)
					{
						if(m_fTimer>=m_fShotTimer)
						{
							SoldierFireMessage* msg=new SoldierFireMessage(MSG_SOLDIERFIRE, BUL_SHELL, this);
							CMessageSystem::GetInstance()->SndMessage(msg);
							m_fTimer=0;
						}
						else
							m_fTimer+=fDt;
					}
				}
				else if(m_nEType==ROCKET)
				{
					if(m_fTimer>=m_fShotTimer)
						{
							SoldierFireMessage* msg=new SoldierFireMessage(MSG_SOLDIERFIRE, BUL_ROCKET, this);
							CMessageSystem::GetInstance()->SndMessage(msg);
							m_fTimer=0;
						}
						else
							m_fTimer+=fDt;
				}
				if(m_bOnFire)
				{
					m_fFireTimer-=fDt;
					if(m_fFireTimer<=0)
					{
						TakeDamage(3);
						m_bOnFire=false;
						m_pOnFire->DeactivateEmitter();
					}
					if(m_fFireTimer<=2&&!m_bHurt2)
					{
						TakeDamage(3);
						m_bHurt2=true;
					}
					if(m_fFireTimer<=4&&!m_bHurt1)
					{
						TakeDamage(3);
						m_bHurt1=true;
					}
				}
			}
		}
	}
	else
	{
		if(m_fStopTimer > 0.0f)
		{
			m_fStopTimer -= fDt;
		}
		else
		{
			m_bStop = false;
		
		}
	}
	m_pOnFire->UpdateEmitterPos(GetPosX(), GetPosY());
}

void CEnemy::Render(void)
{
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetHealth() < GetMaxHealth())
	{
		//Health
		RECT rect;
		rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+pCam->GetPosX()), (int)((GetPosY()-40)+pCam->GetPosY()), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+pCam->GetPosX()), (int)((GetPosY()-40)+pCam->GetPosY()), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (int)((GetPosX()-41)+pCam->GetPosX()), (int)((GetPosY()-40)+pCam->GetPosY()), 0.5f,0.5f,&rect);
	}

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
		Camera* C=Camera::GetInstance();
		if(GetImageID() != -1)
		{
			CSGD_TextureManager::GetInstance()->Draw( GetImageID(), int((GetPosX()+C->GetPosX())-GetWidth()/2), int((GetPosY()+C->GetPosY())-GetHeight()/2), 1.0f, 1.0f, nullptr, GetWidth()/2.0f, GetHeight()/2.0f, m_fRotation, DWORD(GetColor()) );
		}
	}
}

bool CEnemy::CheckCollision(IEntity* pBase)
{
	Camera* pCam =Camera::GetInstance();
	CGame *pGame = CGame::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
				CDestroyEnemyMessage* pMse = new CDestroyEnemyMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMse);
				pMse = nullptr;
			}
			break;
		case OBJ_ENEMY:
			{
				SetPosX(GetOldPos().fX);
				SetPosY(GetOldPos().fY);
			}
			break;
		};
		return true;
	}
	else
		return false;
	}
	else
		return false;
}

void CEnemy::HandleEvent(CEvent* pEvent)
{
	if(pEvent->GetParam() != this)
		return;

	if(pEvent->GetEventID() == "explode")
	{
		CGame::GetInstance()->system->playSound(FMOD_CHANNEL_FREE,CGame::GetInstance()->sound,false,&CGame::GetInstance()->channel);
	}
}

RECT CEnemy::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.bottom=(LONG)(GetPosY()+C->GetPosY()+GetHeight()/2);
	rect.top=(LONG)(GetPosY()+C->GetPosY()-GetHeight()/2);
	rect.left=(LONG)(GetPosX()+C->GetPosX()-GetWidth()/2);
	rect.right=(LONG)(GetPosX()+C->GetPosX()+GetWidth()/2);
	return rect;
}

void CEnemy::SetOnFire()
{
	m_bOnFire=true;
	m_fFireTimer=6.0f;
	m_bHurt1=false;
	m_bHurt2=false;
	m_pOnFire->ActivateEmitter();
}
