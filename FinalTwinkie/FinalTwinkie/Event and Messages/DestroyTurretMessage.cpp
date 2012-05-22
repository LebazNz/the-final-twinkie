#include "DestroyTurretMessage.h"

#include "../GameObjects/Turret.h"

CDestroyTurretMessage::CDestroyTurretMessage(CTurret* pTurret)
	: CMessage(MSG_DESTROYTURRET),
	m_pTurret(pTurret)
{
	if(m_pTurret != nullptr)
		m_pTurret->AddRef();
}


CDestroyTurretMessage::~CDestroyTurretMessage(void)
{
	if(m_pTurret != nullptr)
		m_pTurret->Release();
	m_pTurret = nullptr;
}
