#include "Player.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "MessageSystem.h"
#include "CreateBulletMessage.h"

void CPlayer::Update(float fDt)
{
	tVector2D Up={0,-1};
	if(m_pDI->KeyDown(DIK_W))
	{
		Up=Vector2DRotate(Up, m_fRotation);
		float DX=(Up.fX*GetVelX()*fDt);
		SetPosX(GetPosX()+DX);
		SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));
	}
	else if(m_pDI->KeyDown(DIK_S))
	{
		Up=Vector2DRotate(Up, m_fRotation);
		float DX=(Up.fX*GetVelX()*fDt);
		SetPosX(GetPosX()-DX);
		SetPosY(GetPosY()-(Up.fY*GetVelY()*fDt));
	}

	if(m_pDI->KeyDown(DIK_D))
	{
		m_fRotation+=m_fRotationRate*fDt;
	}
	else if(m_pDI->KeyDown(DIK_A))
	{
		m_fRotation-=m_fRotationRate*fDt;
	}

	if(m_pDI->MouseButtonPressed(0) || m_pDI->KeyDown(DIK_SPACE))
	{
		CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
		CMessageSystem::GetInstance()->SndMessage(msg);
	}

	m_pTurret->SetPosX(GetPosX());
	m_pTurret->SetPosY(GetPosY()-32);

}
void CPlayer::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2), (int)(GetPosY()-GetHeight()/2),1.0f,1.0f,0,GetWidth()/2.0f,GetHeight()/2.0f,m_fRotation);
}
RECT CPlayer::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}
bool CPlayer::CheckCollision(IEntity* pBase)
{
	return false;
}
void CPlayer::Input(void)
{
	
}
CPlayer::CPlayer(void)
{
	m_pDI=CSGD_DirectInput::GetInstance();
	m_fRotationRate=1.5f;
	m_nType=OBJ_PLAYER;
}
CPlayer::~CPlayer(void)
{
}
