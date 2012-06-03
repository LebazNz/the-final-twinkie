#include "AirStrike.h"


CAirStrike::CAirStrike(void)
{
}


CAirStrike::~CAirStrike(void)
{
}

void CAirStrike::Update(float fDt)
{
}

void CAirStrike::ActivateSpecial(void)
{
	/*if(m_nAmmo != 0)
	{
		Camera* c = Camera::GetInstance();
		m_pEmitter->UpdateEmitterPos(CPlayer::GetInstance()->GetPosX()-c->GetPosX(),CPlayer::GetInstance()->GetPosY()-c->GetPosY());
		m_pEmitter->ActivateEmitter();
		CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,m_nDamage);
		m_nAmmo--;
	}	*/
}
