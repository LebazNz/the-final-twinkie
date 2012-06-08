#include "Turret.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include <math.h>
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
using std::sqrt;



void CTurret::Update(float fDt)
{
	Camera* C=Camera::GetInstance();

	Camera* pCam =Camera::GetInstance();
	
	CGame *pGame = CGame::GetInstance();

	//TANK
	if(m_pOwner != nullptr && m_pOwner != CPlayer::GetInstance()/*m_pOwner->GetType() != OBJ_PLAYER && m_pTarget != nullptr*/)
	{
		if(m_bStop == false)
		{
			if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
			{
				Camera* C=Camera::GetInstance();

				float xPos = GetPosX() - (m_pTarget->GetPosX()-C->GetPosX());
				float yPos = GetPosY() - (m_pTarget->GetPosY()-C->GetPosY());
				xPos *= xPos;
				yPos *= yPos;

				float distance = sqrt(float(xPos+yPos));

				if(distance <= m_fMaxDistance)
				{
					tVector2D target = {float(m_pTarget->GetPosX()-C->GetPosX()),float(m_pTarget->GetPosY()-C->GetPosY())};
  
					tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
   

					m_vLookVec=Vector2DRotate(m_vUpVec, m_fRotation);

					if(Steering(m_vLookVec,Vec) < -1)
					m_fRotation -= m_fRotationRate*fDt;
					else if(Steering(m_vLookVec,Vec) > 1)
					m_fRotation += m_fRotationRate*fDt;

					if(m_fFireRate >= SHOT_DELAY)
					{
						m_fFireRate = 0.0f;

					CCreateBulletMessage* pMsg = new CCreateBulletMessage(MSG_CREATEBULLET,BUL_SHELL,this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
					}
					else
						m_fFireRate+=fDt;
				}
			}
		}
	}
	else if(m_pOwner == CPlayer::GetInstance() /*&& m_pOwner->GetType() == OBJ_PLAYER*/)  //PLAYER
	{   
			float xPos = GetPosX() - CSGD_DirectInput::GetInstance()->MouseGetPosX();
			float yPos = GetPosY() - CSGD_DirectInput::GetInstance()->MouseGetPosY();
			xPos *= xPos;
			yPos *= yPos;

			float distance = sqrt(float(xPos+yPos));

			if(distance <= m_fMaxDistance)
			{
				tVector2D target = {float(CSGD_DirectInput::GetInstance()->MouseGetPosX()),float(CSGD_DirectInput::GetInstance()->MouseGetPosY())};
  
				tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
  

				//m_fRotation = AngleBetweenVectors(m_vUpVec,Vec);
				//m_vLookVec = Vec;
				tVector2D Up={0,-1};

				m_vLookVec=Vector2DRotate(Up, m_fRotation);

				if(Steering(m_vLookVec,Vec) < -1)
				m_fRotation -= m_fRotationRate*fDt;
				else if(Steering(m_vLookVec,Vec) > 1)
				m_fRotation += m_fRotationRate*fDt;
   

			}

			m_pFlamer->UpdateEmitterDirecton(m_vLookVec);
			m_pFlamer->UpdateEmitterPos(GetPosX()-GetWidth()/2+32+98*m_vLookVec.fX-C->GetPosX(), GetPosY()-GetHeight()/2+64+98*m_vLookVec.fY-C->GetPosY());
	}
	else if(m_pOwner == nullptr && m_pTarget != nullptr)  //TURRET ON ITS OWN
	{
		if(m_bStop == false)
		{
			float xPos = GetPosX() - (m_pTarget->GetPosX()-C->GetPosX());
			float yPos = GetPosY() - (m_pTarget->GetPosY()-C->GetPosY());
			xPos *= xPos;
			yPos *= yPos;
			
			if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
			{
			float distance = sqrt(float(xPos+yPos));

			if(distance <= m_fMaxDistance)
			{
				tVector2D target = {float(m_pTarget->GetPosX()-C->GetPosX()),float(m_pTarget->GetPosY()-C->GetPosY())};
   
  
				tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
  

				m_vLookVec=Vector2DRotate(m_vUpVec, m_fRotation);

				if(Steering(m_vLookVec,Vec) < -1)
					m_fRotation -= m_fRotationRate*fDt;
				else if(Steering(m_vLookVec,Vec) > 1)
					m_fRotation += m_fRotationRate*fDt;

				if(m_fFireRate >= SHOT_DELAY)
				{
					m_fFireRate = 0.0f;

					CCreateBulletMessage* pMsg = new CCreateBulletMessage(MSG_CREATEBULLET,BUL_SHELL,this);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				else
					m_fFireRate+=fDt;

				}
			}
		}
	}
	
	
	if(abs(m_fRotation)>=2.335)
	{
		m_fRotationHeight=128;
		m_fRotationWidth=64;
	}
	else if(abs(m_fRotation)>0.785)
	{
		m_fRotationHeight=64;
		m_fRotationWidth=128;
	}
	else if(abs(m_fRotation)<=0.785)
	{
		m_fRotationHeight=128;
		m_fRotationWidth=64;
	}
	
	if(m_fStopTimer > 0.0f)
	{
		m_fStopTimer -= fDt;
	}
	else
		m_bStop = false;
}

void CTurret::Render(void)
{
	Camera* C=Camera::GetInstance();
	Camera* pCam =Camera::GetInstance();
	CGame *pGame = CGame::GetInstance();

	
	if(m_pOwner != nullptr)
	{
		this;
		if(m_pOwner->GetType()!=OBJ_PLAYER)
		{
			if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
				CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)((GetPosX()-GetWidth()/2)+C->GetPosX()),(int)((GetPosY()-GetHeight()/2-32)+C->GetPosY()),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
		}
		else
		{
			this;
			CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)(GetPosX()-GetWidth()/2),(int)(GetPosY()-GetHeight()/2-32),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
		}
	}
	else if(m_pOwner == nullptr)
	{
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
			CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)((GetPosX()-GetWidth()/2)+C->GetPosX()),(int)((GetPosY()-GetHeight()/2-32)+C->GetPosY()),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
	this;
	}
}

CTurret::CTurret(void)
{
	m_nType = OBJ_TURRET;
	m_pOwner = nullptr;
	m_pTarget = nullptr;
	m_vLookVec.fX = 0.0f;
	m_vLookVec.fY = 0.0f;
	SetPosX(0);
	SetPosY(0);
	m_fRotPosX, m_fRotPosY = 0.0f;
	m_fRotation = 0.0f;
	m_fRotationRate = 0.0f;
	m_fFireRate = 0.0f;
	m_fMaxDistance = 300.0f;
	m_vUpVec.fX = 0.0;
	m_vUpVec.fY = -1.0f;
	m_fStopTimer = 0.0f;
	m_bStop = false;
	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}

CTurret::~CTurret(void)
{
}

void CTurret::SetUpVec(float x, float y)
{
	m_vUpVec.fX = x;
	m_vUpVec.fY = y;
}

RECT CTurret::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect={};
	if(abs(m_fRotation)>=2.335)
	{
		rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2+32);
		rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2);
		rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2+32);
		rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2);
	}
	else if(m_fRotation>0.785)
	{
		rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2);
		rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2+32);
		rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2);
		rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2+32);
	}
	else if(m_fRotation<-0.785)
	{
		rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2);
		rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2-32);
		rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2);
		rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2-32);
	}
	else if(abs(m_fRotation)<=0.785)
	{
		rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2-32);
		rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2);
		rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2-32);
		rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2);
	}
	return rect;
}

void CTurret::TakeDamage(int nDamage)
{
	if(GetOwner() != nullptr)
		return;

	int health = (int)(GetHealth() - nDamage);
	SetHealth((float)health);

	if(health <= 0.0f)
	{
		CDestroyTurretMessage* pMst = new CDestroyTurretMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMst);
		pMst = nullptr;
	}
}