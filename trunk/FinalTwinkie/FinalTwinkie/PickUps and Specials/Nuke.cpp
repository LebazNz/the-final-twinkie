#include "Nuke.h"
#include "../GameObjects/Player.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../GameStates/GamePlayState.h"
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

void CNuke::ActivateSpecial(void)
{
	if(m_nAmmo != 0)
	{
		m_pEmitter->ResetEmitter();
		Camera* c = Camera::GetInstance();
		m_pEmitter->UpdateEmitterPos((CPlayer::GetInstance()->GetPosX()-CPlayer::GetInstance()->GetWidth()/2-25)-c->GetPosX(),(CPlayer::GetInstance()->GetPosY()-CPlayer::GetInstance()->GetHeight()/2-25)-c->GetPosY());
		m_pEmitter->ActivateEmitter();
		CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,m_nDamage);
		m_nAmmo--;
		if(CGame::GetInstance()->GetCurState()==CGamePlayState::GetInstance())
		{
			CPlayer::GetInstance()->SetNukesBlasted(CPlayer::GetInstance()->GetNukesBlasted()+1);
			if(CPlayer::GetInstance()->GetNukesBlasted()>5)
			{
				CPlayer::GetInstance()->SetNukem(true);
			}
		}
	}	
}
