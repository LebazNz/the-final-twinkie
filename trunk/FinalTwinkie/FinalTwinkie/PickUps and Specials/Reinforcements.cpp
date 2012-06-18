#include "Reinforcements.h"
#include "../GameStates/GamePlayState.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Sapper.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Headers/Camera.h"
#include "../Event and Messages/MessageSystem.h"


CReinforcements::CReinforcements(void)
{
	m_nAmmo = 5;
	m_nType = REINFORCE;
}

CReinforcements::~CReinforcements(void)
{
}

void CReinforcements::ActivateSpecial(void)
{
	if(m_nAmmo != 0)
	{
		Camera* c = Camera::GetInstance();
		CPlayer* pPlayer = CPlayer::GetInstance();
		
		CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,pPlayer->GetPosX()+100-c->GetPosX(),pPlayer->GetPosY()+100-c->GetPosY());
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,pPlayer->GetPosX()-100-c->GetPosX(),pPlayer->GetPosY()+100-c->GetPosY());
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,pPlayer->GetPosX()+50-c->GetPosX(),pPlayer->GetPosY()+100-c->GetPosY());
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,pPlayer->GetPosX()-50-c->GetPosX(),pPlayer->GetPosY()+100-c->GetPosY());
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,pPlayer->GetPosX()-c->GetPosX(),pPlayer->GetPosY()+100-c->GetPosY());
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;

		m_nAmmo--;
	}	
}
