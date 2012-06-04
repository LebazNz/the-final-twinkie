#include "DestroyTreeMessage.h"

#include "../GameObjects/Tree.h"

CDestroyTreeMessage::CDestroyTreeMessage(CTree * pTree) : CMessage(MSG_DESTROYTREE), m_pTree(pTree)
{
	if(m_pTree != nullptr)
	{
		m_pTree->AddRef();
	}
}


CDestroyTreeMessage::~CDestroyTreeMessage(void)
{
	if(m_pTree != nullptr)
	{
		m_pTree->Release();
	}

	m_pTree = nullptr;
}
