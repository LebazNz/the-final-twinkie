#ifndef CREATEPICKUPMESSAGE_H_
#define CREATEPICKUPMESSAGE_H_


#include "message.h" 
#include "../GameObjects/Entity.h"

class CCreatePickupMessage : public CMessage
{
public:
	CCreatePickupMessage(MessageType msgType, CEntity* pEntity, int nPickupType);
	virtual ~CCreatePickupMessage(void);

	CEntity* GetEntity(void) {return m_pEntity;}
	int GetPickUpType(void) { return m_nPickupType; }

private:
	int m_nPickupType;
	CEntity* m_pEntity;
};

#endif CREATEPICKUPMESSAGE_H_