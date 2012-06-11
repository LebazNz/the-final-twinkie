#include "DestroyEMPMessage.h"
#include "../GameObjects/EMPBlast.h"

CDestroyEMPMessage::CDestroyEMPMessage(CEMPBlast* pEMP)
	: CMessage(MSG_DESTROYEMP), m_pEMP(pEMP)
{
	if(m_pEMP != nullptr)
		m_pEMP->AddRef();
}

CDestroyEMPMessage::~CDestroyEMPMessage(void)
{
	if(m_pEMP != nullptr)
		m_pEMP->Release();
	m_pEMP = nullptr;
}
