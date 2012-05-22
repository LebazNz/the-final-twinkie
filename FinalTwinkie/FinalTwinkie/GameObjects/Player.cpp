#include "Player.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
void CPlayer::Update(float fDt)
{
	tVector2D Up={0,-1};

	if(m_pDI->KeyDown(DIK_W) || m_pDI->KeyDown(DIK_S))
	{
		m_bIsMoving = true;
	}
	else m_bIsMoving = false;

	if(!m_pDI->KeyDown(DIK_W) && !m_pDI->KeyDown(DIK_S))
	{
		SetMoveUp(false);
		SetMoveDown(false);
	}

	if(Camera::GetInstance()->GetPlayerCannotMove() == false)
	{
		if(m_pDI->KeyDown(DIK_W))
		{
			Up=Vector2DRotate(Up, m_fRotation);
			float DX=(Up.fX*GetVelX()*fDt);
			m_v2OldPos.fX = GetPosX();
			m_v2OldPos.fY = GetPosY();
			SetPosX(GetPosX()+DX);
			SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));

			SetMoveUp(true);
			SetMoveDown(false);
		}
		else if(m_pDI->KeyDown(DIK_S))
		{
			Up=Vector2DRotate(Up, m_fRotation);
			float DX=(Up.fX*GetVelX()*fDt);
			m_v2OldPos.fX = GetPosX();
			m_v2OldPos.fY = GetPosY();
			SetPosX(GetPosX()-DX);
			SetPosY(GetPosY()-(Up.fY*GetVelY()*fDt));

			SetMoveUp(false);
			SetMoveDown(true);
		}
		else
		{
			SetMoveUp(false);
			SetMoveDown(false);
		}
	}
	if(m_pDI->KeyDown(DIK_D))
	{
		m_fRotation+=m_fRotationRate*fDt;

		SetMoveRight(true);
		SetMoveLeft(false);
	}
	else if(m_pDI->KeyDown(DIK_A))
	{
		m_fRotation-=m_fRotationRate*fDt;

		SetMoveRight(false);
		SetMoveLeft(true);
	}

	if(m_pDI->MouseButtonPressed(0))
	{
		CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
		CMessageSystem::GetInstance()->SndMessage(msg);
	}
	if(m_pDI->MouseButtonDown(1))
	{
		if(m_fFireRate >= 0.15f)
		{
			m_fFireRate = 0.0f;
			CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_MACHINEGUN, m_pTurret);
			CMessageSystem::GetInstance()->SndMessage(msg);
		}
		else
			m_fFireRate += fDt;
	}

	m_pTurret->SetPosX(GetPosX());
	m_pTurret->SetPosY(GetPosY());
	if(GetPosX()-GetHeight()/2<0)
	{
		m_v2OldPos.fX = GetPosX();
		SetPosX((float)(GetHeight()/2));
	}
	if(GetPosY()-GetHeight()/2<0)
	{
		m_v2OldPos.fY = GetPosY();
		SetPosY((float)(GetHeight()/2));
	}
	CGame* game=CGame::GetInstance();
	if(GetPosX()+GetHeight()/2>game->GetWidth())
	{
		m_v2OldPos.fX = GetPosX();
		SetPosX(float(game->GetWidth()-GetHeight()/2));
	}
	if(GetPosY()+GetHeight()/2>game->GetHeight())
	{
		m_v2OldPos.fY = GetPosY();
		SetPosY(float(game->GetHeight()-GetHeight()/2));
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
void CPlayer::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2), (int)(GetPosY()-GetHeight()/2),1.0f,1.0f,0,GetWidth()/2.0f,GetHeight()/2.0f,m_fRotation);
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(),255,0,0);
}
RECT CPlayer::GetRect(void)
{
	RECT rect;
	rect.top=(LONG)(GetPosY()-m_fRotationHeight/2);
	rect.left=(LONG)(GetPosX()-m_fRotationWidth/2);
	rect.bottom=(LONG)(GetPosY()+m_fRotationHeight/2);
	rect.right=(LONG)(GetPosX()+m_fRotationWidth/2);
	return rect;
}
bool CPlayer::CheckCollision(IEntity* pBase)
{
	return false;
}
CPlayer::CPlayer(void)
{
	m_pDI=CSGD_DirectInput::GetInstance();
	m_fRotationRate=1.5f;
	m_nType=OBJ_PLAYER;

	m_bIsMoving		= false;
	m_bMoveRight	= false;
	m_bMoveLeft		= false;
	m_bMoveUp		= false;
	m_bMoveDown		= false;

	m_fFireRate = 0.0f;
}
CPlayer::~CPlayer(void)
{
}
