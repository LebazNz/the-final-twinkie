#ifndef CREATETREE_H_
#define CREATETREE_H_

#include "Message.h"

class CCreateTreeMessage : public CMessage
{
public:
	CCreateTreeMessage(MessageType msgType, float x = 0.0f, float y = 0.0f, bool b = false);
	virtual ~CCreateTreeMessage(void);

	float GetPosX(void) const { return m_nPosX;}
	float GetPosY(void) const { return m_nPosY;}
	bool GetBarr(void) const { return m_bIsBar;}

private:
	float m_nPosX;
	float m_nPosY;
	bool m_bIsBar;
};


#endif
