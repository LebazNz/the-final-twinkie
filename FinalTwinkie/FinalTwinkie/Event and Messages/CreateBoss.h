#pragma once
#include "message.h"
class CCreateBoss :
	public CMessage
{
public:
	CCreateBoss(int nBossType, float PosX, float PosY);
	~CCreateBoss(void);

	int GetBossType(void) {return m_nBossType;}
	float GetPosX(void) {return m_fPosX;}
	float GetPosY(void) {return m_fPosY;}

private:
	int m_nBossType;
	float m_fPosX;
	float m_fPosY;
};

