#include "CreateBulletMessage.h"


CCreateBulletMessage::CCreateBulletMessage(MessageType msgType, int nBulletType)
	: CMessage(msgType),
	m_nBulletType(nBulletType)
{
	
}	


CCreateBulletMessage::~CCreateBulletMessage(void)
{
}
