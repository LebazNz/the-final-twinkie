#include "CreateBuildingMessage.h"


CCreateBuildingMessage::CCreateBuildingMessage(MessageType msgType, int nType, float x, float y, bool spawn, float time)
	: CMessage(msgType),
	m_nType(nType),  m_nPosX(x), m_nPosY(y), m_bSpawn(spawn), m_fTime(time)
{
	
}	

CCreateBuildingMessage::~CCreateBuildingMessage(void)
{
}
