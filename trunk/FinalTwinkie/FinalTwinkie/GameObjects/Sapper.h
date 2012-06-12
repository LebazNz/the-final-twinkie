#ifndef SAPPER_H
#define SAPPER_H
#include "IEntity.h"
#include "Enemy.h"
#include "../Particle/Emitter.h"
#include "Player.h"
class CSapper:public CEnemy
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	CSapper(void);
	~CSapper(void);

	void SetSight(float fSight) {m_fSight=fSight;}
	void SetPlayer(CPlayer* pPlayer) {m_pPlayer=pPlayer;}
	void SetHelpTarget(CEntity* pTarget){m_pTarget=pTarget;}
	void SetExplosion(CEmitter* pEmitter) {m_pExplosion=pEmitter;}
	void SetRadius(float fRad){m_fRadius=fRad;}
	void SetDamage(float fDam){m_fDamage=fDam;}
	void SetExplode(int s) { m_nExplode = s;}
	tVector2D GetOldPos(void) { return m_v2OldPos;}

private:
	int m_nExplode;

	float m_fRadius;
	float m_fDamage;

	float m_fSight;

	float m_fRotation;

	CEmitter* m_pExplosion;
	CPlayer* m_pPlayer;
	CEntity* m_pTarget;
	tVector2D m_v2OldPos;
};
#endif