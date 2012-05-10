#ifndef CREATEENEMYMESSAGE_H_
#define CREATEENEMYMESSAGE_H_


#include "Message.h"

class CCreateEnemyMessage : public CMessage
{
public:
	CCreateEnemyMessage(MessageType msgType, int nEnemyType);
	virtual ~CCreateEnemyMessage(void);


private:
	int m_nEnemyType;
};

#endif CREATEENEMYMESSAGE_H_