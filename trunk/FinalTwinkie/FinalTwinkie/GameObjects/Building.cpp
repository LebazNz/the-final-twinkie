#include "Building.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../source/Camera.h"
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
bool CBuilding::CheckCollision(IEntity*)
{
	return false;
}
CBuilding::CBuilding(void)
{
	m_nType=OBJ_BUILDING;
}
CBuilding::~CBuilding(void)
{
}