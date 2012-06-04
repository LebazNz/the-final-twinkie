#include "CreateTreeMessage.h"


CCreateTreeMessage::CCreateTreeMessage(MessageType msgType, float x, float y)
	: CMessage(msgType), m_nPosX(x), m_nPosY(y)
{
	
}


CCreateTreeMessage::~CCreateTreeMessage(void)
{
}
