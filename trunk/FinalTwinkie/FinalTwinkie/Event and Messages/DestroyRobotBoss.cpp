#include "DestroyRobotBoss.h"
#include "../GameObjects/RobotBoss.h"

CDestroyRobotBoss::CDestroyRobotBoss(RobotBoss* pBoss)
	: CMessage(MSG_DESTROYROBOTBOSS)
{

	
	m_pBoss=pBoss;
	if(m_pBoss != nullptr)
	{
		m_pBoss->AddRef();
	}

}


CDestroyRobotBoss::~CDestroyRobotBoss(void)
{
	if(m_pBoss != nullptr)
	{
		m_pBoss->Release();
	}
	m_pBoss = nullptr;
}
