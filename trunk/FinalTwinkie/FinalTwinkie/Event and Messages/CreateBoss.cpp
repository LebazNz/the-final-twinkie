#include "CreateBoss.h"


CCreateBoss::CCreateBoss(int nBossType, float PosX, float PosY):CMessage(MSG_CREATEBOSS)
{
	m_nBossType=nBossType;
	m_fPosX=PosX;
	m_fPosY=PosY;
}


CCreateBoss::~CCreateBoss(void)
{
}
