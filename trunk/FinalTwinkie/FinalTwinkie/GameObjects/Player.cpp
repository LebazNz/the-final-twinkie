#include "Player.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "Enemy.h"

CPlayer* CPlayer::m_pInstance=nullptr;
CPlayer* CPlayer::GetInstance(void)
{
	if(m_pInstance==nullptr)
		m_pInstance=new CPlayer();
	return m_pInstance;
}

void CPlayer::DeleteInstance(void)
{
	if(m_pInstance!=nullptr)
		delete m_pInstance;
	m_pInstance=nullptr;
}
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

	if(m_pDI->MouseButtonPressed(0) && m_fFireTimer >= m_fTime)
	{
		if(m_fNoReloadTimer == 0.0f)
		{			
				CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
				CMessageSystem::GetInstance()->SndMessage(msg);
				m_fFireTimer = 0.0f;
				m_fTime = 1.0f;
		}
		else
		{
			CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, m_pTurret->GetBullet(), m_pTurret);
			CMessageSystem::GetInstance()->SndMessage(msg);
			m_fFireTimer = 0.0f;
			m_fTime = 0.25f;
			m_fNoReloadTimer -= fDt;
		}
	}
	else
		m_fFireTimer += fDt;

	if(m_pDI->MouseButtonDown(1))
	{
		if(m_fFireRate >= 0.15f&&m_fHeat<100&&!m_bOverheat)
		{
			m_fFireRate = 0.0f;
			CCreateBulletMessage* msg=new CCreateBulletMessage(MSG_CREATEBULLET, BUL_MACHINEGUN, m_pTurret);
			CMessageSystem::GetInstance()->SndMessage(msg);
			if(m_bInfAmmo == false)
				m_fHeat+=3;
		}
		else
			m_fFireRate += fDt;
		if(m_fHeat>100)
		{
			m_bOverheat=true;
		}
		if(m_bOverheat&&m_fOverheatTimer>=2.0f)
		{
			m_bOverheat=false;
			m_fOverheatTimer=0.0f;
		}
		else if(m_bOverheat&&m_fOverheatTimer<2.0f)
		{
			m_fOverheatTimer+=fDt;
		}
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
	if(m_fHeat>0&&!m_bOverheat)
	{
		m_fHeat-=0.1f;
	}
	else if(m_fHeat>0&&m_bOverheat)
	{
		m_fHeat-=.5;
	}
	if(m_fHeat<0)
		m_fHeat=0;

	if(m_bDoubleDamage == true)
		if(m_fDamageTime > 0.0f)
			m_fDamageTime-=fDt;
		else
			m_bDoubleDamage = false;

	if(m_bInfAmmo == true)
		if(m_fInfAmmoTimer > 0.0f)
			m_fInfAmmoTimer-=fDt;
		else
			m_bInfAmmo = false;
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
			{				
			}
			break;
		case OBJ_ENEMY:
			{
				CEnemy* pEnemy =dynamic_cast<CEnemy*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		case OBJ_PICKUP:
			{
			}
			break;
		case OBJ_BUILDING:
			{
				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		case OBJ_MINE:
			{
			}
			break;
		};
		return true;
	}
	else
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
	m_bOverheat		= false;

	m_fFireRate = 0.0f;
	m_fHeat=0.0f;
	m_fOverheatTimer=0.0f;
	m_fTime=1.0f;
	m_fFireTimer=m_fTime;	
	m_fNoReloadTimer=0.0f;
	m_bDoubleDamage = false;
	m_fDamageTime = 0.0f;
	m_bInfAmmo = false;
	m_fInfAmmoTimer = 0.0f;
}
CPlayer::~CPlayer(void)
{
}
