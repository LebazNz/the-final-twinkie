#include "CreateBulletMessage.h"
#include "Turret.h"

CCreateBulletMessage::CCreateBulletMessage(MessageType msgType, int nBulletType, CTurret* pFiringEntity)
	: CMessage(msgType),
	m_nBulletType(nBulletType), 
	m_pFiringEntity(pFiringEntity)
{
	if(m_pFiringEntity != nullptr)
	{
		m_pFiringEntity->AddRef();
	}
}	

CCreateBulletMessage::~CCreateBulletMessage(void)
{
	if(m_pFiringEntity != nullptr)
	{
		m_pFiringEntity->Release();
	}
	m_pFiringEntity = nullptr;
}
