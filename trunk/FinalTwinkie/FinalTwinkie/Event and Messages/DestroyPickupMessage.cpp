#include "DestroyPickupMessage.h"

#include "../PickUps and Specials/Pickup.h"


CDestroyPickupMessage::CDestroyPickupMessage(CPickup* pPickup)
	: CMessage(MSG_DESTROYBULLET),
	  m_pPickup(pPickup)
{
	// Add ref to smart pointer
	if(m_pPickup != nullptr)
	{
		m_pPickup->AddRef();
	}
}


CDestroyPickupMessage::~CDestroyPickupMessage(void)
{
	// release ref to smart pointer
	if(m_pPickup != nullptr)
	{
		m_pPickup->Release();
	}
	m_pPickup = nullptr;
}