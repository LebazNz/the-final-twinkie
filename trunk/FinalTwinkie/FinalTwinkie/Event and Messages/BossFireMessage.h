#pragma once
#include "message.h"
#include "../Boss/BossTurret.h"
class CBossFireMessage :
	public CMessage
{
public:
	CBossFireMessage(MessageType msgType, int nBulletType, CBossTurret* pFiringEntity);
	virtual ~CBossFireMessage(void);
	CBossTurret* GetFiringEntity(void) {return m_pFiringEntity;}
	int GetBulletType(void) {return m_nBulType;}

private:
	CBossTurret* m_pFiringEntity;
	int m_nBulType;
};

