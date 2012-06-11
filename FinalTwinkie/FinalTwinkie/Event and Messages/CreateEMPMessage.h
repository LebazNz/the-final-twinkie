#pragma once
#include "message.h"

class CCreateEMPMessage : public CMessage
{
public:
	CCreateEMPMessage(MessageType msgType);
	virtual ~CCreateEMPMessage(void);
};

