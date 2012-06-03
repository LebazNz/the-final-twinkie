#include "Tank.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
CTank::CTank(void)
{
	m_nType = OBJ_TANK;
}
CTank::~CTank(void)
{
}
void CTank::Update(float fDt)
{
	if(m_bStop == false)
	{
		Camera* C=Camera::GetInstance();
		tVector2D Up={0,-1};
		tVector2D Look=Vector2DRotate(Up,m_fRotation);
		tVector2D toTarget;
		toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
		toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
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
			m_v2OldPos.fX = GetPosX();
			m_v2OldPos.fY = GetPosY();
			SetPosX(GetPosX()+DX);
			SetPosY(GetPosY()+DY);
		}
		m_pTurret->SetPosX(GetPosX()+16*Look.fX);
		m_pTurret->SetPosY(GetPosY()+16*Look.fY);
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
	else
	{
		if(m_fStopTimer > 0.0f)
		{
			m_fStopTimer -= fDt;
		}
		else
			m_bStop = false;
	}
}
void CTank::Render(void)
{
	Camera* C=Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2, m_fRotation);
	//CSGD_Direct3D::GetInstance()->DrawRect(GetRect(), 0,255,0);
}
bool CTank::CheckCollision(IEntity* pBase)
{
	if(pBase->GetType() == OBJ_TURRET)
		return false;

	if(pBase == this)
		return false;

	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
		case OBJ_BASE:
			break;
		case OBJ_PLAYER:
			{
				Camera *cam = Camera::GetInstance();
				CPlayer* pPlayer = CPlayer::GetInstance();

				pPlayer->SetPosX(pPlayer->GetOldPos().fX);
				pPlayer->SetPosY(pPlayer->GetOldPos().fY);
				cam->SetPosX(cam->GetOldPos().fX);
				cam->SetPosY(cam->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
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
		case OBJ_TANK:
			{
				CTank* pEnemy =dynamic_cast<CTank*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);
			}
			break;
		};
		return true;
	}
	else
		return false;
}
RECT CTank::GetRect(void)
{
	this->GetPosX();
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2);
	rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2);
	rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2);
	rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2);
	return rect;
}
