#include "Mine.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "Player.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyMineMessage.h"

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
	if(GetImageID() != -1)
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
				CPlayer* pPlayer = CPlayer::GetInstance();
				pPlayer->TakeDamage(m_nDamage);
				CDestroyMineMessage* pMsg = new CDestroyMineMessage(this);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
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

		default:
			{

			}
			break;
		};
		return true;
	}
	else
		return false;
}
