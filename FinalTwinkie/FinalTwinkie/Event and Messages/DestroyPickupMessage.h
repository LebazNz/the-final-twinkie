#ifndef DESTROYPICKUPMESSAGE_H_
#define DESTROYPICKUPMESSAGE_H_


#include "message.h" 
class CPickup;

class CDestroyPickupMessage : public CMessage
{
public:
	CDestroyPickupMessage(CPickup* pPickup);
	virtual ~CDestroyPickupMessage(void);
	CPickup* GetPickUp(void) {return m_pPickup; }

private:
	CPickup* m_pPickup;
};

#endif DESTROYPICKUPMESSAGE_H_