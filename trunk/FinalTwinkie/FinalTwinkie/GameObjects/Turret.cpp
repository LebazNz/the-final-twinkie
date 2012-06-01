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
using std::sqrt;



void CTurret::Update(float fDt)
{
	Camera* C=Camera::GetInstance();

	//TANK
	if(m_pOwner != nullptr && m_pOwner->GetType() != OBJ_PLAYER && m_pTarget != nullptr) // change target check to !=
	{
		

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
	else if(m_pOwner != nullptr && m_pOwner->GetType() == OBJ_PLAYER)  //PLAYER
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
		m_pFlamer->UpdateEmitterPos(GetPosX(), GetPosY());
	}
	else if(m_pOwner == nullptr && m_pTarget != nullptr)  //TURRET ON ITS OWN
	{

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
	
}
void CTurret::Render(void)
{
	Camera* C=Camera::GetInstance();

	if(m_pOwner != nullptr)
	{
		if(m_pOwner->GetType()!=OBJ_PLAYER)
			CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)((GetPosX()-GetWidth()/2)+C->GetPosX()),(int)((GetPosY()-GetHeight()/2-32)+C->GetPosY()),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
		else
			CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)(GetPosX()-GetWidth()/2),(int)(GetPosY()-GetHeight()/2-32),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
	}
	else if(m_pOwner == nullptr)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)((GetPosX()-GetWidth()/2)+C->GetPosX()),(int)((GetPosY()-GetHeight()/2-32)+C->GetPosY()),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
	}

		
	//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 255,0,0);
}

CTurret::CTurret(void)
{
	CEntity::m_nType = OBJ_TURRET;
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
	RECT rect={};
	if(m_pOwner != nullptr)
	{
	if(m_pOwner->GetType()==OBJ_PLAYER)
	{
		if(abs(m_fRotation)>=2.335)
		{
			rect.top=(LONG)(GetPosY()-m_fRotationHeight/2+32);
			rect.left=(LONG)(GetPosX()-m_fRotationWidth/2);
			rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2+32);
			rect.right=(LONG)(GetPosX()+m_fRotationWidth/2);
		}
		else if(m_fRotation>0.785)
		{
			rect.top=(LONG)(GetPosY()-m_fRotationHeight/2);
			rect.left=(LONG)(GetPosX()-m_fRotationWidth/2+32);
			rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2);
			rect.right=(LONG)(GetPosX()+m_fRotationWidth/2+32);
		}
		else if(m_fRotation<-0.785)
		{
			rect.top=(LONG)(GetPosY()-m_fRotationHeight/2);
			rect.left=(LONG)(GetPosX()-m_fRotationWidth/2-32);
			rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2);
			rect.right=(LONG)(GetPosX()+m_fRotationWidth/2-32);
		}
		else if(abs(m_fRotation)<=0.785)
		{
			rect.top=(LONG)(GetPosY()-m_fRotationHeight/2-32);
			rect.left=(LONG)(GetPosX()-m_fRotationWidth/2);
			rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2-32);
			rect.right=(LONG)(GetPosX()+m_fRotationWidth/2);
		}
	}
	}
	return rect;
}


void CTurret::TakeDamage(int nDamage)
{
	if(GetHealth() <= 0.0f)
	{
		CDestroyTurretMessage* pMst = new CDestroyTurretMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMst);
		pMst = nullptr;
	}
}