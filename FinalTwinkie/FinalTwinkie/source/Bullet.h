#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class CBullet: public CEntity
{
public:
	virtual void Update(float);
	
	virtual bool CheckCollision(IEntity*);
	
	CBullet(void);
	~CBullet(void);

	bool GetWhoFired(void) const { return m_bWhoFired; }
	void SetWhoFired(bool bFired) { m_bWhoFired = bFired; }

private:
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	bool m_bWhoFired;
};
#endif
