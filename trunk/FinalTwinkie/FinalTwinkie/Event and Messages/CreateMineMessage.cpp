#include "CreateMineMessage.h"

CCreateMineMessage::CCreateMineMessage(MessageType msgType, int x, int y)
	: CMessage(msgType), m_nPosX(x), m_nPosY(y)
{
	
}	


CCreateMineMessage::~CCreateMineMessage(void)
{
}
