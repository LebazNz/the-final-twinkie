#include "Building.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
void CBuilding::Update(float)
{
}
void CBuilding::Render(void)
{
	Camera* C=Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (GetPosX()+C->GetPosX())-(GetWidth()/2), (GetPosY()+C->GetPosY())-(GetWidth()/2));
}
RECT CBuilding::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rect;
	rect.top=(GetPosY()+C->GetPosY())-GetHeight()/2;
	rect.bottom=(GetPosY()+C->GetPosY())+GetHeight()/2;
	rect.left=(GetPosX()+C->GetPosX())-GetWidth()/2;
	rect.right=(GetPosX()+C->GetPosX())+GetWidth()/2;
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
}
CBuilding::~CBuilding(void)
{
}