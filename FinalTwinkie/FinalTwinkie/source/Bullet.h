#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "IListener.h"

class CBullet: public CEntity, public IListener
{
public:
	virtual void Update(float);
	virtual void Render(void);
	
	virtual bool CheckCollision(IEntity*);
	
	CBullet(void);
	~CBullet(void);

	bool GetWhoFired(void) const { return m_bWhoFired; }
	void SetWhoFired(bool bFired) { m_bWhoFired = bFired; }

	float GetRotation(void) const { return m_fRotation; }
	void SetRotation(float fRotation) { m_fRotation = fRotation; }

	virtual void HandleEvent(CEvent* pEvent);

private:
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	bool m_bWhoFired;
	float m_fRotation;
};
#endif
