#include "DestroyFactoryMessage.h"


CDestroyFactoryMessage::CDestroyFactoryMessage(Factory* pFac):CMessage(MSG_DESTROYFACTORY)
{
	m_pFac=pFac;
	if(m_pFac != nullptr)
	{
		m_pFac->AddRef();
	}
}


CDestroyFactoryMessage::~CDestroyFactoryMessage(void)
{
	if(m_pFac != nullptr)
	{
		m_pFac->Release();
	}
	m_pFac = nullptr;
}
