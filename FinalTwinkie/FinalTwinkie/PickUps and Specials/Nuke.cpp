#include "Nuke.h"
#include "../GameObjects/Player.h"
#include "../ObjectManager and Factory/ObjectManager.h"

CNuke::CNuke(void)
{
	m_nType = NUKE;
	m_nDamage = 900;
	m_nRadius = 400;
	m_nAmmo = 1;
	m_fDuration = 2.0f;
}

CNuke::~CNuke(void)
{
}

void CNuke::Update(float fDt)
{
}

void CNuke::ActivateSpecial(void)
{
	CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,m_nDamage);
}
