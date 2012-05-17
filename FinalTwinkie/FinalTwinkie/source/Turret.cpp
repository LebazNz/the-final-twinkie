#include "Turret.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "MessageSystem.h"
#include "CreateBulletMessage.h"
#include <math.h>
using std::sqrt;



void CTurret::Update(float fDt)
{
	if(m_pOwner != nullptr && m_pOwner->GetType() != OBJ_PLAYER && m_pTarget != nullptr) // change target check to !=
	{
		

		float xPos = GetPosX() - m_pTarget->GetPosX();
		float yPos = GetPosY() - m_pTarget->GetPosY();
		xPos *= xPos;
		yPos *= yPos;

		float distance = sqrt(float(xPos+yPos));

		if(distance <= m_fMaxDistance)
		{
			 tVector2D target = {float(m_pTarget->GetPosX()),float(m_pTarget->GetPosY())};
	 
			 tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
			

			 m_fRotation = AngleBetweenVectors(m_vUpVec,Vec);
			 m_vLookVec = Vec;

			 if(Steering(m_vUpVec,Vec) <= 0.0f)
				 m_fRotation = -m_fRotation;

			 if(m_fFireRate >= SHOT_DELAY)
			 {
				 m_fFireRate = 0.0f;

				CCreateBulletMessage* pMsg = new CCreateBulletMessage(MSG_CREATEBULLET,BUL_SHELL,this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			 }
		}
	}
	else if(m_pOwner != nullptr && m_pOwner->GetType() == OBJ_PLAYER)
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
		

			m_fRotation = AngleBetweenVectors(m_vUpVec,Vec);
			m_vLookVec = Vec;

			if(Steering(m_vUpVec,Vec) <= 0.0f)
				m_fRotation = -m_fRotation;


		}
		 

	}
	else if(m_pOwner == nullptr && m_pTarget == nullptr)
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
		

			m_fRotation = AngleBetweenVectors(m_vUpVec,Vec);

			m_vLookVec = Vec;

			if(Steering(m_vUpVec,Vec) <= 0.0f)
				m_fRotation = -m_fRotation;

			 if(m_fFireRate >= SHOT_DELAY)
			 {
				 m_fFireRate = 0.0f;

				CCreateBulletMessage* pMsg = new CCreateBulletMessage(MSG_CREATEBULLET,BUL_SHELL,this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			 }

		}


	}
	


	m_fFireRate += fDt;
}
void CTurret::Render(void)
{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(),(int)(GetPosX()-GetWidth()/2),(int)(GetPosY()-GetHeight()/2),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);
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