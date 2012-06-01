#include "Building.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Event and Messages/DestroyBuildingMessage.h"

void CBuilding::Update(float fDt)
{
	Camera* C=Camera::GetInstance();
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
void CBuilding::Render(void)
{
	Camera* C=Camera::GetInstance();
	if(!m_bDead)
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)((GetPosX()+C->GetPosX())-(GetWidth()/2)), (int)((GetPosY()+C->GetPosY())-(GetWidth()/2)));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nDeathImage, (int)((GetPosX()+C->GetPosX())-(GetWidth()/2)), (int)((GetPosY()+C->GetPosY())-(GetWidth()/2)));
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
CBuilding::CBuilding(void)
{
	m_nType=OBJ_BUILDING;
	m_fTimer=0.0f;
}
CBuilding::~CBuilding(void)
{
}

void CBuilding::TakeDamage(int nDamage)
{

	int m_fHealth = GetHealth();
	m_fHealth -= nDamage;
	if(m_fHealth<0)
	{
		m_fHealth=0;
		CDestroyBuildingMessage* pMst = new CDestroyBuildingMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMst);
		pMst=nullptr;
	}

}