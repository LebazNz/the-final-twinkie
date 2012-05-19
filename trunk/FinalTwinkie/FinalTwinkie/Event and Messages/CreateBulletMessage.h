#ifndef CREATEBULLETMESSAGE_H_
#define CREATEBULLETMESSAGE_H_


#include "message.h" 

class CTurret;

class CCreateBulletMessage : public CMessage
{
public:
	CCreateBulletMessage(MessageType msgType, int nBulletType, CTurret* pFiringEntity);
	virtual ~CCreateBulletMessage(void);

	int GetBulletType(void) const {return m_nBulletType; }
	CTurret* GetFiringEntity(void)const {return m_pFiringEntity;}

private:
	int m_nBulletType;
	CTurret* m_pFiringEntity;
};

#endif CREATEBULLETMESSAGE_H_
