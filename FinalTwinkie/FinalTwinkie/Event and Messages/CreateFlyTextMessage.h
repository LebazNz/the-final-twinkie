#pragma once
#include "message.h"

class CPickup;

class CCreateFlyTextMessage : public CMessage
{
public:
	CCreateFlyTextMessage(MessageType msgType, int nType, CPickup* pPickup);
	virtual ~CCreateFlyTextMessage(void);

	CPickup* GetPickUp(void) {return m_pPickup;}

private:
	int m_nType;
	CPickup* m_pPickup;
};

