#include "CreateEnemyMessage.h"


CCreateEnemyMessage::CCreateEnemyMessage(MessageType msgType, int nEnemyType, float x, float y, int nKind)
	: CMessage(msgType),
	m_nEnemyType(nEnemyType), m_nPosX(x), m_nPosY(y), m_nKind(nKind)
{

}	


CCreateEnemyMessage::~CCreateEnemyMessage(void)
{
}