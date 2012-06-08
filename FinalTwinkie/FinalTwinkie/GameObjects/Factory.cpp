#include "Factory.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"

Factory::Factory(void)
{
	TurretOne=nullptr;
	TurretTwo=nullptr;
	m_nType=OBJ_FACTORY;
	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}


Factory::~Factory(void)
{
}

void Factory::Update(float fDt)
{

}

void Factory::Render(void)
{
	Camera* pCam=Camera::GetInstance();

	Camera* C=Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (GetPosX()+pCam->GetPosX())-GetWidth()/2, (GetPosY()+pCam->GetPosY())-GetHeight()/2);

	if(GetHealth() < GetMaxHealth())
	{
		//Health
		RECT rect;
		rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-40)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-40)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-40)+pCam->GetPosY(), 0.5f,0.5f,&rect);
	}
}

RECT Factory::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect={0,0,0,0};
	rect.top=GetPosY()+C->GetPosY()-GetHeight()/2;
	rect.bottom=GetPosY()+C->GetPosY()+GetHeight()/2;
	rect.left=GetPosX()+C->GetPosX()-GetWidth()/2;
	rect.right=GetPosX()+C->GetPosX()+GetWidth()/2;
	return rect;
}

bool Factory::CheckCollision(IEntity* pBase)
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

void Factory::TakeDamage(int nDamage)
{
	SetHealth(GetHealth()-nDamage);
}
