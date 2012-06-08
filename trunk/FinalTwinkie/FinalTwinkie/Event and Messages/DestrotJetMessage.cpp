#include "DestrotJetMessage.h"
#include "../GameObjects/Jet.h"

CDestrotJetMessage::CDestrotJetMessage(CJet* pJet)
	: CMessage(MSG_DESTROYJET), m_pJet(pJet)
{
	if(m_pJet != nullptr)
		m_pJet->AddRef();
}

CDestrotJetMessage::~CDestrotJetMessage(void)
{
	if(m_pJet != nullptr)
		m_pJet->Release();
	m_pJet = nullptr;
}
