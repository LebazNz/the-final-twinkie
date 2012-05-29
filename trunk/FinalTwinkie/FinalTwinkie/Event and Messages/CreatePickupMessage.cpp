#include "CreatePickupMessage.h"


CCreatePickupMessage::CCreatePickupMessage(MessageType msgType, CEntity* pEntity, int nPickupType)
	: CMessage(msgType), m_pEntity(pEntity),
	m_nPickupType(nPickupType)
{
	if(m_pEntity != nullptr)
	{
		m_pEntity->AddRef();
	}
}	


CCreatePickupMessage::~CCreatePickupMessage(void)
{
	if(m_pEntity != nullptr)
	{
		m_pEntity->Release();
	}
	m_pEntity = nullptr;
}