#ifndef CREATEENEMYMESSAGE_H_
#define CREATEENEMYMESSAGE_H_


#include "Message.h"

class CCreateEnemyMessage : public CMessage
{
public:
	CCreateEnemyMessage(MessageType msgType, int nEnemyType, int x = 0, int y = 0);
	virtual ~CCreateEnemyMessage(void);

	int GetEnemyType(void) const { return m_nEnemyType; }
	int GetPosX(void) const { return m_nPosX; }
	int GetPosY(void) const { return m_nPosY; }

private:
	int m_nEnemyType;
	int m_nPosX;
	int m_nPosY;
};

#endif CREATEENEMYMESSAGE_H_