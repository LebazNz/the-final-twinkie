#ifndef PICKUP_H
#define PICKUP_H
#include "../GameObjects/Entity.h"
class CPickup:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckColision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	CPickup(void);
	~CPickup(void);

private:
	float m_fAliveTime;
	int m_nType;

	

};
#endif