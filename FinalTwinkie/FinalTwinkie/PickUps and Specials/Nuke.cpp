#include "Nuke.h"
#include "../GameObjects/Player.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"

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
	//m_pPM->RemoveAttachedEmitter(m_pEmmiter);
}

void CNuke::Update(float fDt)
{
}

void CNuke::ActivateSpecial(void)
{
	Camera* c = Camera::GetInstance();
	m_pEmitter->UpdateEmitterPos(CPlayer::GetInstance()->GetPosX()-c->GetPosX(),CPlayer::GetInstance()->GetPosY()-c->GetPosY());
	m_pEmitter->ActivateEmitter();
	CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,m_nDamage);
}
