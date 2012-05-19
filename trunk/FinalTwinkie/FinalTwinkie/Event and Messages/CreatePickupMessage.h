#ifndef CREATEPICKUPMESSAGE_H_
#define CREATEPICKUPMESSAGE_H_


#include "message.h" 

class CCreatePickupMessage : public CMessage
{
public:
	CCreatePickupMessage(MessageType msgType, int nPickupType);
	virtual ~CCreatePickupMessage(void);


private:
	int m_nPickupType;
};

#endif CREATEPICKUPMESSAGE_H_