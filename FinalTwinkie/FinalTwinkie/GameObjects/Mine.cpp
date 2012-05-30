#include "Mine.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../source/Camera.h"
#include "Player.h"

CMine::CMine(void)
{
	m_nType = OBJ_MINE;
}


CMine::~CMine(void)
{
}


void CMine::Update(float fDt)
{

}
void CMine::Render(void)
{
	Camera* C = Camera::GetInstance();
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2);
}
bool CMine::CheckCollision(IEntity* pBase)
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
			}
			break;
		};
		return true;
	}
	else
		return false;
}
