#ifndef SOLDIERFIREMESSAGE_H
#define SOLDIERFIREMESSAGE_H
#include "Message.h"
#include "../GameObjects/Enemy.h"
class SoldierFireMessage: public CMessage
{
public:
	SoldierFireMessage(MessageType msgType, int nBulletType, CEnemy* pFiringEntity);
	virtual ~SoldierFireMessage(void);

	int GetBulletType(void){return BulletType;}
	CEnemy* GetFiringEntity(void) {return FiringEntity;}

private:
	int BulletType;
	CEnemy* FiringEntity;
};
#endif SOLDIERFIREMESSAGE_H