#include "CreateTreeMessage.h"


CCreateTreeMessage::CCreateTreeMessage(MessageType msgType, float x, float y, bool b)
	: CMessage(msgType), m_nPosX(x), m_nPosY(y), m_bIsBar(b)
{
	
}


CCreateTreeMessage::~CCreateTreeMessage(void)
{
}
