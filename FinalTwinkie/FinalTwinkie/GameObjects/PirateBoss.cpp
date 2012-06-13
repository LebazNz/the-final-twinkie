#include "PirateBoss.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../GameObjects/Player.h"
#include "../Headers/Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../GameStates/MainMenuState.h"
#include "../Event and Messages/DestroyPirateBoss.h"


CPirateBoss::CPirateBoss(void)
{
	m_nType = OBJ_PIRATEBOSS;
	m_nTurretCount = 6;
	m_nTurrID = -1;
	m_nRoundTwo = -1;
	m_nStartX = 0;
	m_bChanged = false;
	m_nMoving = 0;
	m_nHealthBar = -1;

	tOne = nullptr;
	tTwo = nullptr;
	tThree = nullptr;
	
	tFour = nullptr;
	tFive = nullptr;
	tSix = nullptr;

	m_nHealthBar = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/pBossHealth.png"));
	
}


CPirateBoss::~CPirateBoss(void)
{
	if(tOne != nullptr)
	{
		tOne->Release();
		//delete tOne;
		tOne = nullptr;
	}
	if(tTwo != nullptr)
	{
		tTwo->Release();
		//delete tTwo;
		tTwo = nullptr;
	}
	if(tThree != nullptr)
	{
		tThree->Release();
		//delete tThree;
		tThree = nullptr;
	}
	if(tFour != nullptr)
	{
		tFour->Release();
		//delete tFour;
		tFour = nullptr;
	}
	if(tFive != nullptr)
	{
		tFive->Release();
		//delete tFive;
		tFive = nullptr;
	}
	if(tSix != nullptr)
	{
		tSix->Release();
		//delete tSix;
		tSix = nullptr;
	}

	if(m_nHealthBar != -1)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nHealthBar);
		m_nHealthBar = -1;
	}
}


void CPirateBoss::Update(float fDt)
{
	CEntity::Update(fDt);

	if(m_bChanged == false)
	{
		if(GetHealth() <= GetMaxHealth()/2)
		{
			Rebound(fDt);
		}
	}

	if(GetHealth() <= 0)
	{
		CDestroyPirateBoss* pMsg = new CDestroyPirateBoss(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}

	if(tOne != nullptr)
	{
		tOne->SetPosX((GetPosX())+73);
		tOne->SetPosY((GetPosY())+100);
		tOne->Update(fDt);
	}
	if(tTwo != nullptr)
	{
		tTwo->SetPosX((GetPosX())+153);
		tTwo->SetPosY((GetPosY())+108);
		tTwo->Update(fDt);
	}
	if(tThree != nullptr)
	{
		tThree->SetPosX((GetPosX())+252);
		tThree->SetPosY((GetPosY())+108);
		tThree->Update(fDt);
	}
	if(tFour != nullptr)
	{
		if(m_nMoving == 1)
		{
			tFour->SetPosX((GetPosX())+440);
			tFour->SetPosY((GetPosY())+101);
			tFour->Update(fDt);
		}
		else
		{
			tFour->SetPosX((GetPosX())+73);
			tFour->SetPosY((GetPosY())+25);
			tFour->Update(fDt);
		}
	}
	if(tFive != nullptr)
	{
		if(m_nMoving == 1)
		{
			tFive->SetPosX((GetPosX())+259);
			tFive->SetPosY((GetPosY())+108);
			tFive->Update(fDt);
		}
		else
		{
			tFive->SetPosX((GetPosX())+153);
			tFive->SetPosY((GetPosY())+37);
			tFive->Update(fDt);
		}
	}
	if(tSix != nullptr)
	{
		if(m_nMoving == 1)
		{
			tSix->SetPosX((GetPosX())+359);
			tSix->SetPosY((GetPosY())+108);
			tSix->Update(fDt);
		}
		else
		{
			tSix->SetPosX((GetPosX())+252);
			tSix->SetPosY((GetPosY())+37);
			tSix->Update(fDt);
		}
	}

}

void CPirateBoss::Render(void)
{
	CSGD_TextureManager *m_pTM = CSGD_TextureManager::GetInstance();
	Camera* C = Camera::GetInstance();

	if(m_nMoving == 1)
	{
		m_pTM->Draw(m_nRoundTwo, (int)(GetPosX()+C->GetPosX()), (int)(GetPosY()+C->GetPosY()));
	}
	else
		m_pTM->Draw(GetImageID(), (int)(GetPosX()+C->GetPosX()), (int)(GetPosY()+C->GetPosY()));

	if(tOne != nullptr)
		tOne->Render();
	if(tTwo != nullptr)
		tTwo->Render();
	if(tThree != nullptr)
		tThree->Render();
	if(tFour != nullptr)
		tFour->Render();
	if(tFive != nullptr)
		tFive->Render();
	if(tSix != nullptr)
		tSix->Render();
	
	

	if(m_nHealthBar != -1)
	{
		if(GetHealth() < GetMaxHealth())
		{
			RECT rect = {};
			rect.top=(LONG)7; rect.left=(LONG)3; rect.right=(LONG)(3+((122-3)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)22;
			CSGD_TextureManager::GetInstance()->Draw(m_nHealthBar,(int)(GetPosX()+C->GetPosX()), (int)(GetPosY()+C->GetPosY()),2.0f,1.0f,&rect);
		}
	}

}
bool CPirateBoss::CheckCollision(IEntity* pObject)
{

	return true;
}
RECT CPirateBoss::GetRect(void)
{
	Camera* cam = Camera::GetInstance();

	RECT rect = {};
	rect.left = (LONG)(GetPosX() + cam->GetPosX());
	rect.top = (LONG)(GetPosY() + cam->GetPosY());
	rect.right = (LONG)((GetPosX()+cam->GetPosX()) + GetWidth());
	rect.bottom = (LONG)((GetPosY()+cam->GetPosY()) + GetHeight());

	return rect;
}

void CPirateBoss::TakeDamage(int nDamage)
{
	float health = GetHealth();

	 health -= nDamage;
	 SetHealth((float) health );

   if(health < 0)
    health = 0;

}

void CPirateBoss::Rebound(float time)
{

	if(m_bChanged == true)
		return;

	Camera *cam = Camera::GetInstance();
	// Make the ship sail to the left and then change images
	// then sail in from right
	if(m_nMoving == 0)
	{
		SetVelX(200);
	}
	
		
		if((GetPosX()/*+cam->GetPosX()*/) >= 2500 && m_nMoving == 0)
		{
			
			KillTurrets();
			SetVelX(-200);
			m_nMoving = 1;
		}
	
	
		if(GetPosX() < m_nStartX)
		{
			SetVelX(0);
			SetPosX((float)m_nStartX);
			tFour->SetPosX((GetPosX())+440);
			tFour->SetPosY((GetPosY())+101);
			tFour->SetDistance(400);

			tFive->SetPosX((GetPosX())+259);
			tFive->SetPosY((GetPosY())+108);
			tFive->SetDistance(350);

			tSix->SetPosX((GetPosX())+359);
			tSix->SetPosY((GetPosY())+108);
			tSix->SetDistance(400);
			
			m_bChanged = true;

		}
	
}
	

void CPirateBoss::KillTurrets(void)
{
	if(tOne != nullptr)
	{
		tOne->Release();
		//delete tOne;
		tOne = nullptr;
	}
	
	if(tTwo != nullptr)
	{
		tTwo->Release();
		//delete tTwo;
		tTwo = nullptr;
	}

	if(tThree != nullptr)
	{
		tThree->Release();
		//delete tThree;
		tThree = nullptr;
	}
}

void CPirateBoss::MakeTurrets(void)
{
	CObjectManager* m_pOM = CObjectManager::GetInstance();
	Camera *cam = Camera::GetInstance();
	CObjectFactory< std::string , CEntity>* m_pOF = CObjectFactory< std::string , CEntity>::GetInstance();

	{
		tOne = (CTurret*)m_pOF->CreateObject("CTurret");
		tOne->SetImageID(m_nTurrID);
		tOne->SetPosX((GetPosX())+73);
		tOne->SetPosY((GetPosY())+100);
		tOne->SetWidth(64);
		tOne->SetHeight(128);
		tOne->SetInvul(true);
		tOne->SetOwner(nullptr);
		tOne->SetBullet(BUL_SHELL);	
		tOne->SetDamage(20);
		tOne->SetRotationPositon(32,98);
		tOne->SetUpVec(0,-1);
		tOne->SetDistance(400);
		tOne->SetHealth(200);
		tOne->SetMaxHealth(200);
		tOne->SetFireRate(2.0f);
		tOne->SetTarget(CPlayer::GetInstance());
		tOne->SetRotationRate(1.0f);
	}
	{
		tTwo = (CTurret*)m_pOF->CreateObject("CTurret");
		tTwo->SetImageID(m_nTurrID);
		tTwo->SetPosX((GetPosX())+153);
		tTwo->SetPosY((GetPosY())+108);
		tTwo->SetWidth(64);
		tTwo->SetHeight(128);
		tTwo->SetInvul(true);
		tTwo->SetOwner(nullptr);
		tTwo->SetBullet(BUL_SHELL);	
		tTwo->SetDamage(35);
		tTwo->SetRotationPositon(32,98);
		tTwo->SetUpVec(0,-1);
		tTwo->SetDistance(350);
		tTwo->SetHealth(200);
		tTwo->SetMaxHealth(200);
		tTwo->SetFireRate(3.0f);
		tTwo->SetTarget(CPlayer::GetInstance());
		tTwo->SetRotationRate(1.0f);
	}
	{
		tThree = (CTurret*)m_pOF->CreateObject("CTurret");
		tThree->SetImageID(m_nTurrID);
		tThree->SetPosX((GetPosX())+252);
		tThree->SetPosY((GetPosY())+108);
		tThree->SetWidth(64);
		tThree->SetHeight(128);
		tThree->SetInvul(true);
		tThree->SetOwner(nullptr);
		tThree->SetBullet(BUL_SHELL);
		tThree->SetDamage(20);
		tThree->SetRotationPositon(32,98);
		tThree->SetUpVec(0,-1);
		tThree->SetDistance(400);
		tThree->SetHealth(200);
		tThree->SetMaxHealth(200);
		tThree->SetFireRate(1.5f);
		tThree->SetTarget(CPlayer::GetInstance());
		tThree->SetRotationRate(1.0f);
	}
	{
		tFour = (CTurret*)m_pOF->CreateObject("CTurret");
		tFour->SetImageID(m_nTurrID);
		tFour->SetPosX((GetPosX())+73);
		tFour->SetPosY((GetPosY())+25);
		tFour->SetWidth(64);
		tFour->SetHeight(128);
		tFour->SetInvul(true);
		tFour->SetOwner(nullptr);
		tFour->SetBullet(BUL_SHELL);
		tFour->SetDamage(20);
		tFour->SetRotationPositon(32,98);
		tFour->SetUpVec(0,-1);
		tFour->SetDistance(300);
		tFour->SetHealth(200);
		tFour->SetMaxHealth(200);
		tFour->SetFireRate(1.5f);
		tFour->SetTarget(CPlayer::GetInstance());
		tFour->SetRotationRate(1.0f);
	}
	{
		tFive = (CTurret*)m_pOF->CreateObject("CTurret");
		tFive->SetImageID(m_nTurrID);
		tFive->SetPosX((GetPosX())+153);
		tFive->SetPosY((GetPosY())+37);
		tFive->SetWidth(64);
		tFive->SetHeight(128);
		tFive->SetInvul(true);
		tFive->SetOwner(nullptr);
		tFive->SetBullet(BUL_SHELL);	
		tFive->SetDamage(35);
		tFive->SetRotationPositon(32,98);
		tFive->SetUpVec(0,-1);
		tFive->SetDistance(100);
		tFive->SetHealth(200);
		tFive->SetMaxHealth(200);
		tFive->SetFireRate(2.5f);
		tFive->SetTarget(CPlayer::GetInstance());
		tFive->SetRotationRate(1.0f);
	}
	{
		tSix = (CTurret*)m_pOF->CreateObject("CTurret");
		tSix->SetImageID(m_nTurrID);
		tSix->SetPosX((GetPosX())+252);
		tSix->SetPosY((GetPosY())+37);
		tSix->SetWidth(64);
		tSix->SetHeight(128);
		tSix->SetInvul(true);
		tSix->SetOwner(nullptr);
		tSix->SetBullet(BUL_SHELL);	
		tSix->SetDamage(35);
		tSix->SetRotationPositon(32,98);
		tSix->SetUpVec(0,-1);
		tSix->SetDistance(150);
		tSix->SetHealth(200);
		tSix->SetMaxHealth(200);
		tSix->SetFireRate(1.5f);
		tSix->SetTarget(CPlayer::GetInstance());
		tSix->SetRotationRate(1.0f);
	}

}

