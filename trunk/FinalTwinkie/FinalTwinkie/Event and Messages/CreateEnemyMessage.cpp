#include "CreateEnemyMessage.h"


CCreateEnemyMessage::CCreateEnemyMessage(MessageType msgType, int nEnemyType, int x, int y)
	: CMessage(msgType),
	m_nEnemyType(nEnemyType), m_nPosX(x), m_nPosY(y)
{
	
}	


CCreateEnemyMessage::~CCreateEnemyMessage(void)
{
}