#include "BossFireMessage.h"


CBossFireMessage::CBossFireMessage(MessageType msgType, int nBulletType, CBossTurret* pFiringEntity):CMessage(msgType)
{
	m_nBulType=nBulletType;
	m_pFiringEntity=pFiringEntity;
	if(m_pFiringEntity != nullptr)
	{
		m_pFiringEntity->AddRef();
	}
}


CBossFireMessage::~CBossFireMessage(void)
{
	if(m_pFiringEntity != nullptr)
	{
		m_pFiringEntity->Release();
	}
	m_pFiringEntity = nullptr;
}
