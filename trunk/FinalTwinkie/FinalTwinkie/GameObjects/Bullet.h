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

	void SetFlameTimer(float Time){m_fFlameTimer=Time;}
	void SetBulletType(int Type){m_nBulletType=Type;}

	void SetTargetRect(RECT rTarget){m_rTarget = rTarget; }
	RECT GetTargetRect(void) {return m_rTarget;}
	void SetTargetPos(tVector2D vTarget){m_v2TargetPos = vTarget;}
	void SetMissileTimer(float fMissileTimer){m_fMissileTimer = fMissileTimer;}

private:
	// bool for who fired the bullet
	// true		= player fired
	// flase	= enemy fired
	bool m_bWhoFired;
	float m_fRotation;
	float m_fScale;
	float m_fDamage;

	float m_fFlameTimer;
	int m_nBulletType;

	RECT m_rTarget;
	tVector2D m_v2TargetPos;
	float m_fMissileTimer;
};
#endif
