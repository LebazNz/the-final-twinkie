#include "BossTurret.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Event and Messages/BossFireMessage.h"
#include "../Event and Messages/MessageSystem.h"
CBossTurret::CBossTurret(void)
{
	m_fRotation=0;
	m_fFireRate=0;
}

CBossTurret::~CBossTurret(void)
{
}

void CBossTurret::Update(float fDt)
{
	Camera* C=Camera::GetInstance();
	//Cannon
	if(m_nState==0)
	{
#pragma region State 0
		if(m_nTurretType==CANNON)
		{
			float xPos = GetPosX() - (m_pTarget->GetPosX()-C->GetPosX());
			float yPos = GetPosY() - (m_pTarget->GetPosY()-C->GetPosY());
			xPos *= xPos;
			yPos *= yPos;

			float distance = sqrt(float(xPos+yPos));

			tVector2D target = {float(m_pTarget->GetPosX()-C->GetPosX()),float(m_pTarget->GetPosY()-C->GetPosY())};
  
			tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
   
			tVector2D Up={0,-1};
			tVector2D m_vLookVec=Vector2DRotate(Up, m_fRotation+m_fBossRot);

			if(Steering(m_vLookVec,Vec) < -1)
			m_fRotation -= 0.3*fDt;
			else if(Steering(m_vLookVec,Vec) > 1)
			m_fRotation += 0.3*fDt;

			if(m_fRotation>(0.785f))
				m_fRotation=.785;
			if(m_fRotation<(-0.785f))
				m_fRotation=-.785;
			if(m_fFireRate >= 5.0)
			{
				m_fFireRate = 0.0f;

				CBossFireMessage* pMsg = new CBossFireMessage(MSG_BOSSFIRE,BUL_SHELL,this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			else
				m_fFireRate+=fDt;
		}
		else
		{
			m_fRotation=0;
		}
#pragma endregion
	}
	//MG's
	else if(m_nState==1)
	{
#pragma region State 1
		if(m_nTurretType==MG1||m_nTurretType==MG2)
		{
			float xPos = GetPosX() - (m_pTarget->GetPosX()-C->GetPosX());
			float yPos = GetPosY() - (m_pTarget->GetPosY()-C->GetPosY());
			xPos *= xPos;
			yPos *= yPos;

			float distance = sqrt(float(xPos+yPos));

			tVector2D target = {float(m_pTarget->GetPosX()-C->GetPosX()),float(m_pTarget->GetPosY()-C->GetPosY())};
  
			tVector2D Vec = {target.fX - GetPosX(),target.fY - GetPosY()};
   
			tVector2D Up={0,-1};
			tVector2D m_vLookVec=Vector2DRotate(Up, m_fRotation+m_fBossRot);

			if(Steering(m_vLookVec,Vec) < -1)
			m_fRotation -= 1.0*fDt;
			else if(Steering(m_vLookVec,Vec) > 1)
			m_fRotation += 1.0*fDt;

			if(m_fFireRate >= 0.25)
			{
				m_fFireRate = 0.0f;

				CBossFireMessage* pMsg = new CBossFireMessage(MSG_BOSSFIRE,BUL_MACHINEGUN,this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			else
				m_fFireRate+=fDt;
		}
		else
		{
			m_fRotation=0;
		}
#pragma endregion
	}
	//Charge
	else if(m_nState==2)
	{
#pragma region State 2
		if(m_fRotation!=0)
		{
			tVector2D Up={0,-1};
			tVector2D m_vLookVec=Vector2DRotate(Up, m_fRotation+m_fBossRot);
			if(Steering(m_vLookVec,Up) < -1)
			m_fRotation -= 1.0*fDt;
			else if(Steering(m_vLookVec,Up) > 1)
			m_fRotation += 1.0*fDt;
		}
#pragma endregion
	}
	//Berzerk
	else if(m_nState==3)
	{
#pragma region State 3
		if(m_nTurretType==MG1||m_nTurretType==MG2)
		{
			if(m_nTurretType==MG1)
			{
				m_fRotation-=5.0*fDt;
			}

			else if(m_nTurretType==MG2)
			{
				m_fRotation+=5.0*fDt;
			}
			if(m_fFireRate >= 0.06125)
			{
				m_fFireRate = 0.0f;

				CBossFireMessage* pMsg = new CBossFireMessage(MSG_BOSSFIRE,BUL_MACHINEGUN,this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			}
			else
				m_fFireRate+=fDt;
		}
#pragma endregion
	}
}


void CBossTurret::Render(void)
{
	this;
	Camera* C=Camera::GetInstance();
	RECT rect={0,0,0,0};
	if(m_nTurretType==CANNON)
	{
		rect.top=36; rect.bottom=139; rect.left=224; rect.right=267;
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (GetPosX()+C->GetPosX())-GetWidth()/2, (GetPosY()+C->GetPosY())-GetHeight()/2, 1.0, 1.0, &rect, GetWidth()/2,82, m_fRotation+m_fBossRot);
	}
	if(m_nTurretType==MG1)
	{
		rect.top=113; rect.bottom=158; rect.left=427; rect.right=472;
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (PlatePosX+C->GetPosX())-GetWidth()/2, (PlatePosY+C->GetPosY())-GetHeight()/2, 1.0, 1.0, &rect, GetWidth()/2, GetHeight()/2, m_fBossRot);
		rect.top=88; rect.bottom=145; rect.left=333; rect.right=375;
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (GetPosX()+C->GetPosX())-9, (GetPosY()+C->GetPosY())-48, 1.0, 1.0, &rect, 9, 48, m_fRotation+m_fBossRot);
	}
	if(m_nTurretType==MG2)
	{
		rect.top=113; rect.bottom=158; rect.left=427; rect.right=472;
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (PlatePosX+C->GetPosX())-GetWidth()/2, (PlatePosY+C->GetPosY())-GetHeight()/2, 1.0, 1.0, &rect, GetWidth()/2, GetHeight()/2, m_fBossRot);
		rect.top=88; rect.bottom=145; rect.left=333; rect.right=375;
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (GetPosX()+C->GetPosX())-9, (GetPosY()+C->GetPosY())-48, 1.0, 1.0, &rect, 9, 48, m_fRotation+m_fBossRot);
	}
}

void CBossTurret::UpdatePos(float PosX, float PosY)
{
	SetPosX(PosX);
	SetPosY(PosY);
}

void CBossTurret::UpdatePlatePos(float PosX, float PosY)
{
	PlatePosX=PosX;
	PlatePosY=PosY;
}