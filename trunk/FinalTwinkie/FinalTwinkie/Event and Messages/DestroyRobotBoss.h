#pragma once
#include "message.h"
#include "../GameObjects/RobotBoss.h"
#include "../GameObjects/Turret.h"
class CDestroyRobotBoss :
	public CMessage
{
public:
	CDestroyRobotBoss(RobotBoss* pBoss);
	virtual ~CDestroyRobotBoss(void);
	RobotBoss* GetBoss(void) {return m_pBoss;}
private:
	RobotBoss* m_pBoss;
};

