#include "CreatePickupMessage.h"


CCreatePickupMessage::CCreatePickupMessage(MessageType msgType, int nPickupType)
	: CMessage(msgType),
	m_nPickupType(nPickupType)
{
	
}	


CCreatePickupMessage::~CCreatePickupMessage(void)
{
}