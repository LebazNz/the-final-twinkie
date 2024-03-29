#ifndef DESTROYBULLETMESSAGE_H_
#define DESTROYBULLETMESSAGE_H_


#include "message.h" 
class CBullet;

class CDestroyBulletMessage : public CMessage
{
public:
	CDestroyBulletMessage(CBullet* pBullet);
	virtual ~CDestroyBulletMessage(void);

	CBullet* GetBullet(void) {return m_pBullet; }


private:
	CBullet* m_pBullet;
};

#endif DESTROYBULLETMESSAGE_H_