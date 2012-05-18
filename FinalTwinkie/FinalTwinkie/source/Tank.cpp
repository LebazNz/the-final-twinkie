#include "Tank.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "Game.h"
CTank::CTank(void)
{
}
CTank::~CTank(void)
{
}
void CTank::Update(float fDt)
{
	tVector2D Up={0,-1};
	tVector2D Look=Vector2DRotate(Up,m_fRotation);
	tVector2D toTarget;
	toTarget.fX=(m_pPlayer->GetPosX()-GetPosX());
	toTarget.fY=(m_pPlayer->GetPosY()-GetPosY());
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
		SetPosX(GetPosX()+DX);
		SetPosY(GetPosY()+DY);
	}
	m_pTurret->SetPosX(GetPosX());
	m_pTurret->SetPosY(GetPosY());
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
void CTank::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)GetPosX()-GetWidth()/2, (int)GetPosY()-GetHeight()/2, 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
}
bool CTank::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CTank:: GetRect(void)
{
	RECT rect;
	rect.top=(LONG)(GetPosY()-m_fRotationHeight/2);
	rect.left=(LONG)(GetPosX()-m_fRotationWidth/2);
	rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2);
	rect.right=(LONG)(GetPosX()+m_fRotationWidth/2);
	return rect;
}