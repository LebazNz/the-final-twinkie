#include "Reinforcements.h"
#include "../GameStates/GamePlayState.h"
#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Sapper.h"

typedef CObjectFactory< std::string , CEntity> CFactory;

CReinforcements::CReinforcements(void)
{
	CSapper* pSapper = (CSapper*)CFactory::GetInstance()->CreateObject("CSapper");
}

CReinforcements::~CReinforcements(void)
{
}

CEntity* CReinforcements::GetTarget(void)
{
	CSapper* blah;
	return blah;
}

void CReinforcements::Update(float fDt)
{
}

void CReinforcements::ActivateSpecial(void)
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
