#include "Player.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "MessageSystem.h"
#include "CreateBulletMessage.h"
#include "Camera.h"
#include "Game.h"
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
			SetPosX(GetPosX()+DX);
			SetPosY(GetPosY()+(Up.fY*GetVelY()*fDt));

			SetMoveUp(true);
			SetMoveDown(false);
		}
		else if(m_pDI->KeyDown(DIK_S))
		{
			Up=Vector2DRotate(Up, m_fRotation);
			float DX=(Up.fX*GetVelX()*fDt);
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

	if(m_pDI->MouseButtonPressed(0) || m_pDI->KeyDown(DIK_SPACE))
	{
		CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
		CMessageSystem::GetInstance()->SndMessage(msg);
	}

	m_pTurret->SetPosX(GetPosX());
	m_pTurret->SetPosY(GetPosY());
	if(GetPosX()-GetHeight()/2<0)
	{
		SetPosX((float)(GetHeight()/2));
	}
	if(GetPosY()-GetHeight()/2<0)
	{
		SetPosY((float)(GetHeight()/2));
	}
	CGame* game=CGame::GetInstance();
	if(GetPosX()+GetHeight()/2>game->GetWidth())
	{
		SetPosX(float(game->GetWidth()-GetHeight()/2));
	}
	if(GetPosY()+GetHeight()/2>game->GetHeight())
	{
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
}
CPlayer::~CPlayer(void)
{
}
