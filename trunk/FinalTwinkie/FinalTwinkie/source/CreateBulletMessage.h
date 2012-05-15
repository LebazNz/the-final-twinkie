#ifndef CREATEBULLETMESSAGE_H_
#define CREATEBULLETMESSAGE_H_


#include "message.h" 

class CEntity;

class CCreateBulletMessage : public CMessage
{
public:
	CCreateBulletMessage(MessageType msgType, int nBulletType, CEntity* pFiringEntity);
	virtual ~CCreateBulletMessage(void);

	int GetBulletType(void) const {return m_nBulletType; }
	CEntity* GetFiringEntity(void)const {return m_pFiringEntity;}

private:
	int m_nBulletType;
	CEntity* m_pFiringEntity;
};

#endif CREATEBULLETMESSAGE_H_
