#pragma once
#include "message.h"

class CJet;

class CDestrotJetMessage :
	public CMessage
{
public:
	CDestrotJetMessage(CJet* pJet);
	virtual ~CDestrotJetMessage(void);

	CJet* GetJet(void){return m_pJet;}

private:
	CJet* m_pJet;
};

