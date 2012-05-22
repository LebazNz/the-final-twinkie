#pragma once
#include "Message.h"
class CTurret;

class CDestroyTurretMessage : public CMessage
{
public:
	CDestroyTurretMessage(CTurret* pTurret);
	virtual ~CDestroyTurretMessage(void);

	CTurret* GetTurret(void) {return m_pTurret;}

private:
	CTurret* m_pTurret;
};

