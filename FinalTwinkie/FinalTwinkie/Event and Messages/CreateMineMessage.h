#ifndef CREATEMINE_H_
#define CREATEMINE_H_

#include "Message.h"

class CCreateMineMessage : public CMessage
{
public:
	CCreateMineMessage(MessageType msgType, float x = 0, float y = 0);
	virtual ~CCreateMineMessage(void);

	float GetPosX(void) const { return m_nPosX; }
	float GetPosY(void) const { return m_nPosY; }

private:
	float m_nPosX;
	float m_nPosY;
};

#endif