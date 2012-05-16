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
		

		int xPos = GetPosX() - m_pTarget->GetPosX();
		int yPos = GetPosY() - m_pTarget->GetPosY();
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

			
		int xPos = GetPosX() - CSGD_DirectInput::GetInstance()->MouseGetPosX();
		int yPos = GetPosY() - CSGD_DirectInput::GetInstance()->MouseGetPosY();
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

		int xPos = GetPosX() - CSGD_DirectInput::GetInstance()->MouseGetPosX();
		int yPos = GetPosY() - CSGD_DirectInput::GetInstance()->MouseGetPosY();
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
	
	if(m_pOwner != nullptr)
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(),m_pOwner->GetPosX(),m_pOwner->GetPosY(),1.0f,1.0f,0, m_fRotPosX, m_fRotPosY,m_fRotation);
	else
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(),GetPosX(),GetPosY(),1.0f,1.0f,0,m_fRotPosX, m_fRotPosY,m_fRotation);

		// This code will render a line in the look vectors direction from the object's position
		tVector2D target = {float(CSGD_DirectInput::GetInstance()->MouseGetPosX()),float(CSGD_DirectInput::GetInstance()->MouseGetPosY())};
	 
		tVector2D Vec = {target.fX - m_vLookVec.fX,target.fY - m_vLookVec.fY};
	
	
		CSGD_Direct3D::GetInstance()->DrawLine(GetPosX()+GetWidth()/2,GetPosY()+GetHeight()/2,Vec.fX+target.fX,Vec.fY+target.fY,0,0,255);
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