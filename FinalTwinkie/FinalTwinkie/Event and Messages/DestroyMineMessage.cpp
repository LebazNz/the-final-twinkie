#include "DestroyMineMessage.h"

#include "../GameObjects/Mine.h"

CDestroyMineMessage::CDestroyMineMessage(CMine *pMine) : CMessage(MSG_DESTROYMINE), m_pMine(pMine)
{
	if(m_pMine != nullptr)
	{
		m_pMine->AddRef();
	}
}


CDestroyMineMessage::~CDestroyMineMessage(void)
{

	if(m_pMine != nullptr)
	{
		m_pMine->Release();
	}

	m_pMine = nullptr;
}
