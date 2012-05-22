#include "Sapper.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
CSapper::CSapper(void)
{
	m_nType=OBJ_ENEMY;
}
CSapper::~CSapper(void)
{
}
void CSapper::Update(float fDt)
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
		m_pExplosion->UpdateEmitterPos(GetPosX()+C->GetPosX(), GetPosY()+C->GetPosY());
	}
	if(length<=100)
	{
		m_pExplosion->ActivateEmitter();
		CDestroyEnemyMessage* msg=new CDestroyEnemyMessage(this);
		CMessageSystem::GetInstance()->SndMessage(msg);
	}
}
void CSapper::Render(void)
{
	Camera* C=Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
	//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 255,0,0);
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