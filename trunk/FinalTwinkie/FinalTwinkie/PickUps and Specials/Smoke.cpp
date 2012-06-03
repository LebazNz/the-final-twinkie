#include "Smoke.h"
#include "../GameObjects/Player.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"

CSmoke::CSmoke(void)
{
	m_nAmmo = 5;
	m_nDamage = 0;
	m_fDuration = 2.0f;
	m_nType = SMOKE;
	m_nRadius = 400;
	m_fTime = 0.0f;
}

CSmoke::~CSmoke(void)
{
}

void CSmoke::Update(float fDt)
{
}

void CSmoke::ActivateSpecial(void)
{
	if(m_nAmmo != 0)
	{
		Camera* c = Camera::GetInstance();
		m_pEmitter->UpdateEmitterPos(CPlayer::GetInstance()->GetPosX()-c->GetPosX(),CPlayer::GetInstance()->GetPosY()-c->GetPosY());
		m_pEmitter->ActivateEmitter();
		CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,m_nDamage);
		m_nAmmo--;
	}	
}
