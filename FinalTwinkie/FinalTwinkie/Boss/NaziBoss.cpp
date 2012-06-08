#include "NaziBoss.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

CNaziBoss::CNaziBoss(void)
{
	m_nType=OBJ_NAZIBOSS;
	m_nBossType=NAZI;
	m_fRotation=0;	
	m_nCurrentState=0;
	Rotating=true;
	Aquiring=false;
	Waiting=false;
	Charging=false;
	
	WaitTimer=0;	
}

CNaziBoss::~CNaziBoss(void)
{
	delete m_pLMG;
	delete m_pRMG;
	delete m_pCannon;
}

void CNaziBoss::Update(float fDt)
{
	Camera* C=Camera::GetInstance();
	tVector2D OldPos={GetPosX(), GetPosY()};
	SetOldPos(OldPos);
	tVector2D Look={0,-1};
	//Cannon-Straight On
	if(m_nCurrentState==0)
	{
		tVector2D Up={0,-1};
		tVector2D toTarget;
		Look=Vector2DRotate(Up,m_fRotation);
		toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
		toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
		float Steer=Steering(toTarget, Look);
		if(abs(Steer)>1.0&&abs(m_pCannon->GetRotation())>=.5)
		{
			if(Steer>0)
			{
				m_fRotation-=0.3f*fDt;
			}
			else if(Steer<0)
			{
				m_fRotation+=0.3f*fDt;
			}
		}
		if(Vector2DLength(toTarget)>300)
		{
			SetPosX(GetPosX()+(75*Look.fX)*fDt);
			SetPosY(GetPosY()+(75*Look.fY)*fDt);
		}
		Look=Vector2DRotate(Up, m_fRotation);
	}
	//MG's-BroadSide
	else if(m_nCurrentState==1)
	{
		tVector2D Up={0,-1};
		tVector2D toTarget;
		Look=Vector2DRotate(Up,m_fRotation);
		toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
		toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
		toTarget=Vector2DRotate(toTarget, 1.57f);
		float Steer=Steering(toTarget, Look);
		if(abs(Steer)>1.0)
		{
			if(Steer>0)
			{
				m_fRotation-=0.75f*fDt;
			}
			else if(Steer<0)
			{
				m_fRotation+=0.75f*fDt;
			}
		}
		SetPosX(GetPosX()+(150*Look.fX)*fDt);
		SetPosY(GetPosY()+(150*Look.fY)*fDt);
		Look=Vector2DRotate(Up, m_fRotation);
	}
	//Charge
	else if(m_nCurrentState==2)
	{
		if(Rotating)
		{
			tVector2D Up={0,-1};
			tVector2D toTarget;
			Look=Vector2DRotate(Up,m_fRotation);
			toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
			toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
			float Steer=Steering(toTarget, Look);
			if(abs(Steer)>1.0)
			{
				if(Steer>0)
				{
					m_fRotation-=0.5f*fDt;
				}
				else if(Steer<0)
				{
					m_fRotation+=0.5f*fDt;
				}
			}
			else
			{
				Rotating=false;
				Aquiring=true;
			}
			Look=Vector2DRotate(Up, m_fRotation);
		}
		if(Aquiring)
		{
			tVector2D Up={0,-1};
			Look=Vector2DRotate(Up,m_fRotation);
			PlayerPos.fX=m_pPlayer->GetPosX()-C->GetPosX();
			PlayerPos.fY=m_pPlayer->GetPosY()-C->GetPosY();
			Aquiring=false;
			Waiting=true;
		}
		else if(Waiting)
		{
			tVector2D Up={0,-1};
			Look=Vector2DRotate(Up,m_fRotation);
			if(WaitTimer>3.0f)
			{
				Waiting=false;
				Charging=true;
				WaitTimer=0;
			}
			else
			{
				WaitTimer+=fDt;
			}
		}
		else if(Charging)
		{
			StopRect.top=(LONG)((PlayerPos.fY+C->GetPosY())-m_pPlayer->GetWidth()/2);
			StopRect.bottom=(LONG)((PlayerPos.fY+C->GetPosY())+m_pPlayer->GetWidth()/2);
			StopRect.left=(LONG)((PlayerPos.fX+C->GetPosX())-m_pPlayer->GetHeight()/2);
			StopRect.right=(LONG)((PlayerPos.fX+C->GetPosX())+m_pPlayer->GetHeight()/2);
			tVector2D Up={0,-1};
			Look=Vector2DRotate(Up,m_fRotation);
			SetPosX(GetPosX()+(300*Look.fX)*fDt);
			SetPosY(GetPosY()+(300*Look.fY)*fDt);
			this;
			if(GetPosY()+Look.fY*(GetHeight()/3) < StopRect.bottom-C->GetPosY() && GetPosY()+Look.fY*(GetHeight()/3) > StopRect.top-C->GetPosY() 
			&& GetPosX()+Look.fX*(GetHeight()/3) < StopRect.right-C->GetPosX() && GetPosX()+Look.fX*(GetHeight()/3) > StopRect.left-C->GetPosX() )
			{
				Charging=false;
				Rotating=true;
			}
		}
	}
	//Berzerk
	else if(m_nCurrentState==3)
	{
		tVector2D Up={0,-1};
		Look=Vector2DRotate(Up,m_fRotation);
	}
	if(abs(m_fRotation)>=6.28)
		m_fRotation=0;
	if(abs(m_fRotation)>=5.495)
	{
		m_fRotationHeight=(float)GetHeight();
		m_fRotationWidth=(float)GetWidth();
	}
	else if(abs(m_fRotation)>=3.925)
	{
		m_fRotationHeight=(float)GetWidth();
		m_fRotationWidth=(float)GetHeight();
	}
	else if(abs(m_fRotation)>=2.335)
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
	m_pCannon->Update(fDt);
	m_pCannon->UpdatePos(GetPosX()+100*Look.fX,(GetPosY()-32)+105*Look.fY);
	m_pCannon->UpdateCannonRotation(m_fRotation);
	

		m_pLMG->Update(fDt);
		m_pLMG->UpdatePlatePos(GetPosX()+(83*Look.fX)+(47*(Look.fY)), GetPosY()+(83*Look.fY)+(47*(-Look.fX)));
		m_pLMG->UpdatePos(GetPosX()+(85*Look.fX)+(45*(Look.fY)), GetPosY()+(85*Look.fY)+(45*(-Look.fX)));
		m_pLMG->UpdateCannonRotation(m_fRotation);
	
		m_pRMG->Update(fDt);
		m_pRMG->UpdatePlatePos(GetPosX()+(83*Look.fX)+(47*(-Look.fY)), GetPosY()+(83*Look.fY)+(47*(Look.fX)));
		m_pRMG->UpdatePos(GetPosX()+(85*Look.fX)+(50*(-Look.fY)), GetPosY()+(85*Look.fY)+(50*(Look.fX)));
		m_pRMG->UpdateCannonRotation(m_fRotation);

	if(GetHealth()>(GetMaxHealth()-(GetMaxHealth()*.25)))
	{
		ChangeStates(0);
	}
	else if(GetHealth()>(GetMaxHealth()-(GetMaxHealth()*.50)))
	{
		ChangeStates(1);
	}
	else if(GetHealth()>(GetMaxHealth()-(GetMaxHealth()*.90)))
	{
		ChangeStates(2);
	}
	else if(GetHealth()>0)
	{
		ChangeStates(3);
	}
}

void CNaziBoss::Render(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=10; rect.left=10; rect.right=158; rect.bottom=270;
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX()+C->GetPosX())-GetWidth()/2), (int)((GetPosY()+C->GetPosY())-GetHeight()/2), 1.0f,1.0f, &rect,(float)(GetWidth()/2), (float)(GetHeight()/2), m_fRotation);

	m_pCannon->Render();
	m_pLMG->Render();
	m_pRMG->Render();

	rect.top=(LONG)348; rect.left=(LONG)6; rect.right=(LONG)(6+((127-6)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)363;
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), 145, 10, 4.25,2.0, &rect);
}

RECT CNaziBoss::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect={0,0,0,0};
	rect.top=(LONG)((GetPosY()+C->GetPosY())-m_fRotationHeight/2);
	rect.left=(LONG)((GetPosX()+C->GetPosX())-m_fRotationWidth/2);
	rect.right=(LONG)((GetPosX()+C->GetPosX())+m_fRotationWidth/2);
	rect.bottom=(LONG)((GetPosY()+C->GetPosY())+m_fRotationHeight/2);
	return rect;
}

bool CNaziBoss::CheckCollision(IEntity* pBase)
{
	if(CEntity::CheckCollision(pBase) == true)
	{
		switch(pBase->GetType())
		{
			case OBJ_PLAYER:
			{
				Camera *cam = Camera::GetInstance();
				CPlayer* pEnemy =dynamic_cast<CPlayer*>(pBase);

				pEnemy->SetPosX(pEnemy->GetOldPos().fX);
				pEnemy->SetPosY(pEnemy->GetOldPos().fY);
				cam->SetPosX(cam->GetOldPos().fX);
				cam->SetPosY(cam->GetOldPos().fY);

				this->SetPosX(this->GetOldPos().fX);
				this->SetPosY(this->GetOldPos().fY);

			}
			break;
		}
		return true;
	}
	return false;
}

void CNaziBoss::TakeDamage(int nDamage)
{
	SetHealth(GetHealth()-nDamage);
}

void CNaziBoss::SetTurrets(CBossTurret* LMG, CBossTurret* RMG, CBossTurret* LRKT, CBossTurret* RRKT, CBossTurret* Cannon)
{
	m_pLMG=LMG;
	m_pRMG=RMG;
	m_pLRKT=LRKT;
	m_pRRKT=RRKT;
	m_pCannon=Cannon;
}

void CNaziBoss::ChangeStates(int state)
{
	m_nCurrentState=state;
	m_pCannon->SetState(state);
	m_pLMG->SetState(state);
	m_pRMG->SetState(state);
}

void CNaziBoss::CreateTurrets(void)
{
	m_pCannon=new CBossTurret();
	m_pCannon->SetPosX(GetPosX()-72);
	m_pCannon->SetPosY(GetPosY()-234);
	m_pCannon->SetTurretType(CANNON);
	m_pCannon->SetImageID(GetImageID());
	m_pCannon->SetHeight(103);
	m_pCannon->SetWidth(43);
	m_pCannon->SetTarget(m_pPlayer);
	m_pCannon->SetState(m_nCurrentState);

	m_pLMG=new CBossTurret();
	m_pLMG->SetPosX(GetPosX()-47);
	m_pLMG->SetPosY(GetPosY()-83);
	m_pLMG->SetTurretType(MG1);
	m_pLMG->SetImageID(GetImageID());
	m_pLMG->SetHeight(45);
	m_pLMG->SetWidth(45);
	m_pLMG->SetTarget(m_pPlayer);
	m_pLMG->SetState(m_nCurrentState);

	m_pRMG=new CBossTurret();
	m_pRMG->SetPosX(GetPosX()+47);
	m_pRMG->SetPosY(GetPosY()-83);
	m_pRMG->SetTurretType(MG2);
	m_pRMG->SetImageID(GetImageID());
	m_pRMG->SetHeight(45);
	m_pRMG->SetWidth(45);
	m_pRMG->SetTarget(m_pPlayer);
	m_pRMG->SetState(m_nCurrentState);
}