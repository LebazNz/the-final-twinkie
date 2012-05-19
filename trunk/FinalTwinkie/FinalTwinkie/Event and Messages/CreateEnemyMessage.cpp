#include "CreateEnemyMessage.h"


CCreateEnemyMessage::CCreateEnemyMessage(MessageType msgType, int nEnemyType)
	: CMessage(msgType),
	m_nEnemyType(nEnemyType)
{
	
}	


CCreateEnemyMessage::~CCreateEnemyMessage(void)
{
}