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
