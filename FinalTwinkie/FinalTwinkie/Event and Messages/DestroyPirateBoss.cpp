#include "DestroyPirateBoss.h"

#include "../GameObjects/PirateBoss.h"

CDestroyPirateBoss::CDestroyPirateBoss(CPirateBoss *pBoss)
	: CMessage(MSG_DESTROYPIRATEBOSS), m_pBoss(pBoss)
{
	// Add ref to smart pointer
	if(m_pBoss != nullptr)
	{
		m_pBoss->AddRef();
	}
}


CDestroyPirateBoss::~CDestroyPirateBoss(void)
{
	// release ref to smart pointer
	if(m_pBoss != nullptr)
	{
		m_pBoss->Release();
	}
	m_pBoss = nullptr;
}