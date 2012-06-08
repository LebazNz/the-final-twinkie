#include "Sapper.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Headers/Game.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../GameObjects/Tank.h"


CSapper::CSapper(void)
{
	m_nType=OBJ_ENEMY;
	m_fStopTimer = 0.0f;
	m_bStop = false;

	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}
CSapper::~CSapper(void)
{
}
void CSapper::Update(float fDt)
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
				tVector2D Up={0,-1};
				tVector2D toTarget;
				toTarget.fX=((pTarget->GetPosX())/*-C->GetPosX())*/-GetPosX());
				toTarget.fY=((pTarget->GetPosY())/*-C->GetPosY())*/-GetPosY());
				float length=Vector2DLength(toTarget);
				if(length<=m_fSight)
				{
					if(pTarget->GetPosX()/*-C->GetPosX()*/>=GetPosX())
						m_fRotation=AngleBetweenVectors(toTarget, Up);
					else
						m_fRotation=-AngleBetweenVectors(toTarget, Up);
		
					Up=Vector2DRotate(Up, m_fRotation);
					m_v2OldPos.fX = GetPosX();
					m_v2OldPos.fY = GetPosY();
					SetPosX(GetPosX()+(Up.fX*GetVelX()*fDt));
					SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));
				}
				if(m_pExplosion!=nullptr)
				{
					m_pExplosion->UpdateEmitterPos(GetPosX(), GetPosY());
				}
				if(length<=100)
				{
					m_pExplosion->ActivateEmitter();
					CDestroyEnemyMessage* msg=new CDestroyEnemyMessage(this);
					CMessageSystem::GetInstance()->SndMessage(msg);
					CPlayer::GetInstance()->TakeDamage(30);
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
		else if(GetType() != OBJ_HELP && m_bStop == false)
		{

	
			Camera* C=Camera::GetInstance();
			tVector2D Up={0,-1};
			tVector2D toTarget;
			toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-GetPosX());
			toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-GetPosY());
			float length=Vector2DLength(toTarget);
			if(length<=m_fSight)
			{
				if(m_pPlayer->GetPosX()-C->GetPosX()>=GetPosX())
					m_fRotation=AngleBetweenVectors(toTarget, Up);
				else
					m_fRotation=-AngleBetweenVectors(toTarget, Up);
		
				Up=Vector2DRotate(Up, m_fRotation);
				m_v2OldPos.fX = GetPosX();
				m_v2OldPos.fY = GetPosY();
				SetPosX(GetPosX()+(Up.fX*GetVelX()*fDt));
				SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));
			}
			if(m_pExplosion!=nullptr)
			{
				m_pExplosion->UpdateEmitterPos(GetPosX(), GetPosY());
			}
			if(length<=100)
			{
				m_pExplosion->ActivateEmitter();
				CDestroyEnemyMessage* msg=new CDestroyEnemyMessage(this);
				CMessageSystem::GetInstance()->SndMessage(msg);
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
	else
	{
		if(m_fStopTimer > 0.0f)
		{
			m_fStopTimer -= fDt;
		}
		else
			m_bStop = false;
	}
	m_pOnFire->UpdateEmitterPos(GetPosX(), GetPosY());
}
void CSapper::Render(void)
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
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
	}
}
bool CSapper::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CSapper::GetRect(void)
{
	Camera* C=Camera::GetInstance();

	RECT rect;
	rect.top=(LONG)((GetPosY()+C->GetPosY())-GetHeight()/2);
	rect.bottom=(LONG)((GetPosY()+C->GetPosY())+GetHeight()/2);
	rect.left=(LONG)((GetPosX()+C->GetPosX())-GetWidth()/2);
	rect.right=(LONG)((GetPosX()+C->GetPosX())+GetWidth()/2);
	return rect;
}