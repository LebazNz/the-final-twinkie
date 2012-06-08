#include "DestroyNaziBoss.h"


CDestroyNaziBoss::CDestroyNaziBoss(CNaziBoss* pBoss):CMessage(MSG_DESTROYNAZIBOSS)
{
	m_pBoss=pBoss;
	if(m_pBoss != nullptr)
	{
		m_pBoss->AddRef();
	}
}


CDestroyNaziBoss::~CDestroyNaziBoss(void)
{
	if(m_pBoss != nullptr)
	{
		m_pBoss->Release();
	}
	m_pBoss = nullptr;
}
