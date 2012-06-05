#pragma once
#include "message.h"

class CFlyText;

class CDestroyFlyTextMessage : public CMessage
{
public:
	CDestroyFlyTextMessage(CFlyText* pFlyText);
	virtual ~CDestroyFlyTextMessage(void);

	CFlyText* GetPickup(void) {return m_pFlyText;}

private:
	CFlyText* m_pFlyText;
};

