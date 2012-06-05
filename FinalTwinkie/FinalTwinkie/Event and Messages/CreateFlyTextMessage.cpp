#include "CreateFlyTextMessage.h"
#include "../PickUps and Specials/Pickup.h"

CCreateFlyTextMessage::CCreateFlyTextMessage(MessageType msgType, int nType, CPickup* pPickup)
	: CMessage(msgType), m_nType(nType), m_pPickup(pPickup)
{
	if(m_pPickup != nullptr)
	{
		m_pPickup->AddRef();
	}
}


CCreateFlyTextMessage::~CCreateFlyTextMessage(void)
{
	if(m_pPickup != nullptr)
	{
		m_pPickup->Release();
	}
	m_pPickup = nullptr;
}
