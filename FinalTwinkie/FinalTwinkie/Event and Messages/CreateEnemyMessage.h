#ifndef CREATEENEMYMESSAGE_H_
#define CREATEENEMYMESSAGE_H_


#include "Message.h"

class CCreateEnemyMessage : public CMessage
{
public:
	CCreateEnemyMessage(MessageType msgType, int nEnemyType, float x = 0, float y = 0);
	virtual ~CCreateEnemyMessage(void);

	int GetEnemyType(void) const { return m_nEnemyType; }
	float GetPosX(void) const { return m_nPosX; }
	float GetPosY(void) const { return m_nPosY; }

private:
	int m_nEnemyType;
	float m_nPosX;
	float m_nPosY;
};

#endif CREATEENEMYMESSAGE_H_