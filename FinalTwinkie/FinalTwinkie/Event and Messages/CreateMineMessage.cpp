#include "CreateMineMessage.h"

CCreateMineMessage::CCreateMineMessage(MessageType msgType, float x, float y)
	: CMessage(msgType), m_nPosX(x), m_nPosY(y)
{
	
}	


CCreateMineMessage::~CCreateMineMessage(void)
{
}
