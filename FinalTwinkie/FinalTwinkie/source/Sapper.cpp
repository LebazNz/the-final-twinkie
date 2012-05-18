#include "Sapper.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "DestroyEnemyMessage.h"
#include "MessageSystem.h"
CSapper::CSapper(void)
{
}
CSapper::~CSapper(void)
{
}
void CSapper::Update(float fDt)
{
	tVector2D Up={0,-1};
	tVector2D toTarget;
	toTarget.fX=(m_pPlayer->GetPosX()-GetPosX());
	toTarget.fY=(m_pPlayer->GetPosY()-GetPosY());
	float length=Vector2DLength(toTarget);
	if(length<=m_fSight)
	{
		if(m_pPlayer->GetPosX()>=GetPosX())
			m_fRotation=AngleBetweenVectors(toTarget, Up);
		else
			m_fRotation=-AngleBetweenVectors(toTarget, Up);
		
		Up=Vector2DRotate(Up, m_fRotation);
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
}
void CSapper::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)GetPosX()-GetWidth()/2, (int)GetPosY()-GetHeight()/2, 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
}
bool CSapper::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CSapper::GetRect(void)
{
	RECT rect;
	rect.top=(LONG)(GetPosY()+GetHeight()/2);
	rect.bottom=(LONG)(GetPosY()-GetHeight()/2);
	rect.left=(LONG)(GetPosX()-GetWidth()/2);
	rect.right=(LONG)(GetPosX()+GetWidth()/2);
	return rect;
}