#ifndef CREATEBUILDING_H_
#define CREATEBUILDING_H_

#include "Message.h"

class CCreateBuildingMessage : public CMessage
{
public:
	CCreateBuildingMessage(MessageType msgType, int nType, int x = 0, int y = 0);
	virtual ~CCreateBuildingMessage(void);

	int GetType(void) const { return m_nType; }
	int GetPosX(void) const { return m_nPosX; }
	int GetPosY(void) const { return m_nPosY; }

private:
	int m_nType;
	int m_nPosX;
	int m_nPosY;
};

#endif