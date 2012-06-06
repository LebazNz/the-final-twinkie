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
}

CReinforcements::~CReinforcements(void)
{
}

void CReinforcements::ActivateSpecial(void)
{
	if(m_nAmmo != 0)
	{
		Camera* c = Camera::GetInstance();
		
		CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,300,650);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,250,650);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,350,650);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,275,675);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
		pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,HELP,325,675);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;

		m_nAmmo--;
	}	
}
