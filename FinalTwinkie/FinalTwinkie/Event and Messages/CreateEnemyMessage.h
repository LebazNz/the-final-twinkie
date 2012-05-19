#ifndef CREATEENEMYMESSAGE_H_
#define CREATEENEMYMESSAGE_H_


#include "Message.h"

class CCreateEnemyMessage : public CMessage
{
public:
	CCreateEnemyMessage(MessageType msgType, int nEnemyType);
	virtual ~CCreateEnemyMessage(void);

	int GetEnemyType(void) const { return m_nEnemyType; }

private:
	int m_nEnemyType;
};

#endif CREATEENEMYMESSAGE_H_