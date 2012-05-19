#include "../Headers/Camera.h"
#include "../GameObjects/Player.h"
#include "../Headers/Game.h"
#include "../SGD Wrappers/SGD_Math.h"
Camera::Camera(void)
{
	m_fPosX = 0;
	m_fPosY = 0;
}

Camera::~Camera(void)
{

}

void Camera::Update( CPlayer* pPlayer, int nWorldWidth, int nWorldHeight,float fDt )
{
	/*if(pPlayer->GetPosX() < 10 && pPlayer->GetIsMoving())
	{
		m_fPosX+= pPlayer->GetVelX()*fDt;
		m_bPlayerCannotMove = true;
	}
	else if(pPlayer->GetPosX() > CGame::GetInstance()->GetWidth() - 10 && pPlayer->GetIsMoving())
	{
		m_fPosX-= pPlayer->GetVelX()*fDt;
		m_bPlayerCannotMove = true;
	}
	else m_bPlayerCannotMove = false;*/

	tVector2D Up={0,-1};

	if(pPlayer->GetMoveDown())
	{
		Up=Vector2DRotate(Up, pPlayer->GetRotation());
		float DX=(Up.fX*pPlayer->GetVelX()*fDt);
		SetPosX(GetPosX()+DX);
		SetPosY(GetPosY()+(Up.fY*pPlayer->GetVelY()*fDt));
		m_bPlayerCannotMove = true;
	}
	else if(pPlayer->GetMoveUp())
	{
		Up=Vector2DRotate(Up, pPlayer->GetRotation());
		float DX=(Up.fX*pPlayer->GetVelX()*fDt);
		SetPosX(GetPosX()-DX);
		SetPosY(GetPosY()-(Up.fY*pPlayer->GetVelY()*fDt));
		m_bPlayerCannotMove = true;
	}
	else m_bPlayerCannotMove = false;

}

Camera* Camera::GetInstance()
{
	static Camera sInstance;
	return &sInstance;
}
