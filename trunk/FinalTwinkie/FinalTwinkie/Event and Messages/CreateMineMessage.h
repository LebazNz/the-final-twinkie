#ifndef CREATEMINE_H_
#define CREATEMINE_H_

#include "Message.h"

class CCreateMineMessage : public CMessage
{
public:
	CCreateMineMessage(MessageType msgType, int x = 0, int y = 0);
	virtual ~CCreateMineMessage(void);

	int GetPosX(void) const { return m_nPosX; }
	int GetPosY(void) const { return m_nPosY; }

private:
	int m_nPosX;
	int m_nPosY;
};

#endif