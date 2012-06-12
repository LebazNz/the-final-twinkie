#include "AirStrike.h"
#include "../Event and Messages/CreateJetMessage.h"
#include "../Event and Messages/MessageSystem.h"

CAirStrike::CAirStrike(void)
{
	m_nAmmo = 2;
	m_nType = AIRSTRIKE;
}


CAirStrike::~CAirStrike(void)
{
}

void CAirStrike::ActivateSpecial(void)
{
	if(m_nAmmo > 0)
	{
		CCreateJetMessage* pMsg = new CCreateJetMessage(MSG_CREATEJET);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}
