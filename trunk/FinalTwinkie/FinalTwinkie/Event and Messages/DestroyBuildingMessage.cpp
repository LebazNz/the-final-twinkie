#include "DestroyBuildingMessage.h"

#include "../GameObjects/Building.h"


CDestroyBuildingMessage::CDestroyBuildingMessage(CBuilding* pBuilding)
	: CMessage(MSG_DESTROYBUILDING),
	  m_pBuilding(pBuilding)
{
	// Add ref to smart pointer
	if(m_pBuilding != nullptr)
	{
		m_pBuilding->AddRef();
	}
}


CDestroyBuildingMessage::~CDestroyBuildingMessage(void)
{
	// release ref to smart pointer
	if(m_pBuilding != nullptr)
	{
		m_pBuilding->Release();
	}
	m_pBuilding = nullptr;
}