#pragma once
#include "message.h"

class CEMPBlast;

class CDestroyEMPMessage : public CMessage
{
public:
	CDestroyEMPMessage(CEMPBlast* pEMP);
	virtual ~CDestroyEMPMessage(void);

	CEMPBlast* GetEMP(void){return m_pEMP;}

private:
	CEMPBlast* m_pEMP;
};

