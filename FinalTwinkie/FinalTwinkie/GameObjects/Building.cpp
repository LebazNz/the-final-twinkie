#include "Building.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/DestroyBuildingMessage.h"
#include "../Headers/Game.h"

void CBuilding::Update(float fDt)
{
	this;
	Camera* C=Camera::GetInstance();
	Camera* pCam =Camera::GetInstance();
	CGame *pGame = CGame::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	m_pFlames->UpdateEmitterPos(GetPosX(), GetPosY());
	if(!m_bDead)
	{
		tVector2D toTarget;
		toTarget.fX=((m_pPlayer->GetPosX()-C->GetPosX())-(GetPosX()));
		toTarget.fY=((m_pPlayer->GetPosY()-C->GetPosY())-(GetPosY()));
		float length=Vector2DLength(toTarget);
		if(length<=m_fRange)
		{
			if(m_bCanSpawn&&m_fTimer>=m_fSpawnTime)
			{
				CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, m_nSpawnType, GetPosX(), GetPosY()+GetHeight());
				CMessageSystem::GetInstance()->SndMessage(msg);
				m_fTimer=0.0f;
			}
			else 
			{
				m_fTimer+=fDt;
			}
		}
		else
		{
			m_fTimer+=fDt;
		}
	}
	}
}
void CBuilding::Render(void)
{
	Camera* pCam =Camera::GetInstance();
	CGame *pGame = CGame::GetInstance();

	if(GetHealth() < GetMaxHealth() && GetHealth() > 0)
	{
		//Health
		RECT rect;
		rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-80)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)378;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-80)+pCam->GetPosY(), 0.5f,0.5f,&rect);
		rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(GetHealth()/GetMaxHealth()))); rect.bottom=(LONG)403;
		CSGD_TextureManager::GetInstance()->Draw(m_nHPID, (GetPosX()-41)+pCam->GetPosX(), (GetPosY()-80)+pCam->GetPosY(), 0.5f,0.5f,&rect);
	}

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	Camera* C=Camera::GetInstance();
	if(!m_bDead)
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX()+C->GetPosX())-(GetWidth()/2)), (int)((GetPosY()+C->GetPosY())-(GetWidth()/2)));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nDeathImage, (int)((GetPosX()+C->GetPosX())-(GetWidth()/2)), (int)((GetPosY()+C->GetPosY())-(GetWidth()/2)));
	}
}
RECT CBuilding::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=(LONG)((GetPosY()+C->GetPosY())-GetHeight()/2);
	rect.bottom=(LONG)((GetPosY()+C->GetPosY())+GetHeight()/2);
	rect.left=(LONG)((GetPosX()+C->GetPosX())-GetWidth()/2);
	rect.right=(LONG)((GetPosX()+C->GetPosX())+GetWidth()/2);
	return rect;
}
bool CBuilding::CheckCollision(IEntity* pBase)
{
	Camera* pCam =Camera::GetInstance();
	CGame *pGame = CGame::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
	
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
			}
			break;
		case OBJ_PICKUP:
			{
			}
			break;
		case OBJ_BUILDING:
			{
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
	else return false;
}
CBuilding::CBuilding(void)
{
	m_nType=OBJ_BUILDING;
	m_fTimer=0.0f;
	m_nHPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
}
CBuilding::~CBuilding(void)
{
}

void CBuilding::TakeDamage(int nDamage)
{

	int m_fHealth = GetHealth();
	m_fHealth -= nDamage;
	SetHealth(m_fHealth);
	if(m_fHealth<0)
	{
		m_fHealth=0;
		CDestroyBuildingMessage* pMst = new CDestroyBuildingMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMst);
		pMst=nullptr;
	}

}