#pragma once
#include "message.h"


class CCreateJetMessage : public CMessage
{
public:
	CCreateJetMessage(MessageType msgType);
	virtual ~CCreateJetMessage(void);
};

