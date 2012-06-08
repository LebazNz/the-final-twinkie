#pragma once
#include "Message.h"
#include "../Boss/NaziBoss.h"
class CDestroyNaziBoss :
	public CMessage
{
public:
	CDestroyNaziBoss(CNaziBoss* pBoss);
	virtual ~CDestroyNaziBoss(void);
	CNaziBoss* GetBoss(void) {return m_pBoss;}

private:
	CNaziBoss* m_pBoss;
};

