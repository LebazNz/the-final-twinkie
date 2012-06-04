#ifndef CREATETREE_H_
#define CREATETREE_H_

#include "Message.h"

class CCreateTreeMessage : public CMessage
{
public:
	CCreateTreeMessage(MessageType msgType, float x = 0.0f, float y = 0.0f);
	virtual ~CCreateTreeMessage(void);

	float GetPosX(void) const { return m_nPosX;}
	float GetPosY(void) const { return m_nPosY;}

private:
	float m_nPosX;
	float m_nPosY;
};


#endif