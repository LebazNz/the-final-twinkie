#include "SoldierFireMessage.h"


SoldierFireMessage::SoldierFireMessage(MessageType msgType, int nBulletType, CEnemy* pFiringEntity):CMessage(msgType)
{
	BulletType=nBulletType;
	FiringEntity=pFiringEntity;
	if(FiringEntity != nullptr)
	{
		FiringEntity->AddRef();
	}
}


SoldierFireMessage::~SoldierFireMessage(void)
{
	if(FiringEntity != nullptr)
	{
		FiringEntity->Release();
	}
	FiringEntity = nullptr;
}
