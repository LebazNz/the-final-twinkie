#include "EMP.h"
#include "../Event and Messages/CreateEMPMessage.h"
#include "../Event and Messages/MessageSystem.h"

CEMP::CEMP(void)
{
	m_nType = EMP;
	m_nAmmo = 2;
	SetType(EMP);
}

CEMP::~CEMP(void)
{
}

void CEMP::ActivateSpecial(void)
{
	if(m_nAmmo > 0)
	{
		CCreateEMPMessage* pMsg = new CCreateEMPMessage(MSG_CREATEEMP);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}
