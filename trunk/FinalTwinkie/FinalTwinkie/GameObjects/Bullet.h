#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "../Event and Messages/IListener.h"

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
	void SetDamage(float fDamage){m_fDamage = fDamage;}

	void SetScale(float fScale){m_fScale = fScale;}

	virtual void HandleEvent(CEvent* pEvent);

private:
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	bool m_bWhoFired;
	float m_fRotation;
	float m_fScale;
	float m_fDamage;
};
#endif
