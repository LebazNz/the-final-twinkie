#include "CreateBuildingMessage.h"


CCreateBuildingMessage::CCreateBuildingMessage(MessageType msgType, int nType, int x, int y)
	: CMessage(msgType),
	m_nType(nType),  m_nPosX(x), m_nPosY(y) 
{
	
}	

CCreateBuildingMessage::~CCreateBuildingMessage(void)
{
}
