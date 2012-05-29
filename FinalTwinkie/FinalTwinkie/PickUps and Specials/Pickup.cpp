#include "Pickup.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyPickupMessage.h"



CPickup::CPickup(void)
{
	m_nType = OBJ_PICKUP;
	m_fAliveTime = 0.0f;
	m_nGiven = 0;
	m_nPickUpType = -1;
	m_fEndTime = 0.0f;
}

CPickup::~CPickup(void)
{
}

void CPickup::Update(float fDt)
{
	CEntity::Update(fDt);
	m_fEndTime += fDt;
	if(m_fEndTime >= m_fAliveTime)
	{
		CDestroyPickupMessage* pMsg = new CDestroyPickupMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}

void CPickup::Render(void)
{
	Camera* C=Camera::GetInstance();
	if(GetImageID() != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), int(GetPosX()-(GetWidth()/2)+C->GetPosX()), int(GetPosY()-(GetHeight()/2)+C->GetPosY()), 1.0f, 1.0f, nullptr, float(GetWidth()/2), float(GetHeight()/2), 0.0f, GetColor()); 
		//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 255,0,0);
	}
}

bool CPickup::CheckColision(IEntity* pBase)
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
			break;
		case OBJ_ENEMY:
			break;
		};
		return true;
	}
	else
		return false;
}