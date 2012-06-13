#include "RobotBoss.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Event and Messages/DestroyTurretMessage.h"
RobotBoss::RobotBoss(void)
{
	m_pPlayer = CPlayer::GetInstance();
	m_nType = OBJ_ROBOTBOSS;
	m_nHPBARID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/HealthBar.png"));
}


RobotBoss::~RobotBoss(void)
{
	CTurret* pTurret = dynamic_cast<RobotBoss*>(this)->GetTurret();
	CDestroyTurretMessage* pMst = new CDestroyTurretMessage(pTurret);
	CMessageSystem::GetInstance()->SndMessage(pMst);
	pMst = nullptr;
}
void RobotBoss::Update(float fDt)
{
	if(m_bStop == false)
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	Camera* C=Camera::GetInstance();
	tVector2D Up={0,-1};
	tVector2D Look=Vector2DRotate(Up,m_fRotation);
	tVector2D toTarget;
	toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
	toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
	float length=Vector2DLength(toTarget);
	if(length<=m_fSight)
	{
		Camera* C=Camera::GetInstance();
		tVector2D Up={0,-1};
		tVector2D Look=Vector2DRotate(Up,m_fRotation);
		tVector2D toTarget;
		toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
		toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
		float length=Vector2DLength(toTarget);
		if(length<=m_fSight)
		{
			float Steer=Steering(toTarget, Look);
			if(Steer>0)
			{
				m_fRotation-=m_fRotationRate*fDt;
			}
			else if(Steer<0)
			{
				m_fRotation+=m_fRotationRate*fDt;
			}
  
			Look=Vector2DRotate(Up, m_fRotation);
			float DY=(Look.fY*GetVelY()*fDt);
			float DX=(Look.fX*GetVelX()*fDt);
			m_v2OldPos.fX = GetPosX();
			m_v2OldPos.fY = GetPosY();
			SetPosX(GetPosX()+DX);
			SetPosY(GetPosY()+DY);
		}
		m_pTurret->SetPosX(GetPosX()+16*Look.fX);
		m_pTurret->SetPosY(GetPosY()+16*Look.fY);
		CGame* game=CGame::GetInstance();
		if(abs(m_fRotation)>=2.335)
		{
			m_fRotationHeight=(float)GetHeight();
			m_fRotationWidth=(float)GetWidth();
		}
		else if(abs(m_fRotation)>0.785)
		{
			m_fRotationHeight=(float)GetWidth();
			m_fRotationWidth=(float)GetHeight();
		}
		else if(abs(m_fRotation)<=0.785)
		{
			m_fRotationHeight=(float)GetHeight();
			m_fRotationWidth=(float)GetWidth();
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
	}

	if(m_bSlowDown == true)
	{
		if(m_fSlowTimer > 0.0f)
			m_fSlowTimer -= fDt;
		else 
		{
			m_fSlowTimer = 0.0f;
			m_bSlowDown = false;
			SetVelX(35);
			SetVelY(35);
		}
	}
	static bool spawnsapper = false;
	static bool regenhealth = false;
	static bool regenagain = false;
	static bool speedboost = false;
	if(GetHealth() < GetMaxHealth()*0.8 && spawnsapper == false)
	{
		for(unsigned int i = 0; i < 5; i++)
		{
			CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, 0,GetPosX()+70, GetPosY()+135, rand()%3);
			CMessageSystem::GetInstance()->SndMessage(msg);
			spawnsapper = true;
		}
	}
	else if(GetHealth() < GetMaxHealth()*0.7 && regenhealth == false)
	{
		SetHealth(GetHealth() + (float)(GetMaxHealth()*0.3));
		regenhealth = true;
	}
	else if(GetHealth() < GetMaxHealth()*0.5 && regenagain == false)
	{
		SetHealth(GetHealth() + (float)(GetMaxHealth()*0.1));
		regenhealth = true;
		for(unsigned int i = 0; i < 5; i++)
		{
			CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, 3,GetPosX()+70, GetPosY()+135, rand()%3);
			CMessageSystem::GetInstance()->SndMessage(msg);
			regenagain = true;
		}
	}
	else if(GetHealth() < GetMaxHealth()*0.2 && speedboost == false)
	{
		SetHealth(GetHealth() + (float)(GetMaxHealth()*0.2));
		speedboost = true;
		SetRotationRate(0.5f);
		SetSight(2000);
		SetVelX(25);
		SetVelY(25);

	}
}
void RobotBoss::Render(void)
{
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetHealth() < GetMaxHealth())
	{
		//Health
		RECT rect;
		rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-75)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-75)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-75)+pCam->GetPosY(), 0.5f,0.5f,&rect);
	}

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	Camera* C=Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
	}

	RECT rect;
	rect.top=(LONG)348; rect.left=(LONG)6; rect.right=(LONG)(6+((127-6)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)363;
	CSGD_TextureManager::GetInstance()->Draw(m_nHPBARID, 145, 10,((LONG)(GetHealth()/GetMaxHealth())*4.0f),2.0, nullptr);
	
}
bool RobotBoss::CheckCollision(IEntity* pBase)
{
	if(pBase->GetType() == OBJ_TURRET)
		return false;

	if(pBase == this)
		return false;
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
				Camera *cam = Camera::GetInstance();
				CPlayer* pPlayer = CPlayer::GetInstance();

				pPlayer->SetPosX(pPlayer->GetOldPos().fX);
				pPlayer->SetPosY(pPlayer->GetOldPos().fY);
				cam->SetPosX(cam->GetOldPos().fX);
				cam->SetPosY(cam->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		case OBJ_BULLET:
			{	
				return true;
			}
			break;
		case OBJ_ENEMY:
			{
				CEnemy* pEnemy =dynamic_cast<CEnemy*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		case OBJ_PICKUP:
			{
			}
			break;
		case OBJ_BUILDING:
			{
				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		case OBJ_MINE:
			{
			}
			break;
		case OBJ_TANK:
			{
				RobotBoss* pEnemy =dynamic_cast<RobotBoss*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
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
RECT RobotBoss::GetRect(void)
{
	this->GetPosX();
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2);
	rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2);
	rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2);
	rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2);
	return rect;
}
void RobotBoss::SlowVel(float time, float vel)
{
	m_bSlowDown = true;
	m_fSlowTimer = time;
	SetVelX(vel);
	SetVelY(vel);
}