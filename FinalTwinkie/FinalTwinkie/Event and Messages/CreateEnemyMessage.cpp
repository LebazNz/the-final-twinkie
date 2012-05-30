#include "CreateEnemyMessage.h"


CCreateEnemyMessage::CCreateEnemyMessage(MessageType msgType, int nEnemyType, float x, float y)
	: CMessage(msgType),
	m_nEnemyType(nEnemyType), m_nPosX(x), m_nPosY(y)
{
	
}	


CCreateEnemyMessage::~CCreateEnemyMessage(void)
{
}