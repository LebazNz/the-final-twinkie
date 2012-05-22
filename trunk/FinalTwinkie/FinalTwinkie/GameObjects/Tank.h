#ifndef TANK_H
#define TANK_H
#include "Enemy.h"
#include "Turret.h"
#include "Player.h"
class CTank:public CEnemy
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	void SetRotation(float fRot) {m_fRotation=fRot;}
	void SetTurret(CTurret* pTurret) {m_pTurret=pTurret;}
	void SetPlayer(CPlayer* pPlayer) {m_pPlayer=pPlayer;}
	void SetSight(float fSight) {m_fSight=fSight;}
	void SetRotationRate(float fRotRate) {m_fRotationRate=fRotRate;}
	tVector2D GetOldPos(void) { return m_v2OldPos;}
	CTank(void);
	~CTank(void);

	CTurret* GetTurret(void)const{return m_pTurret;}

private:
	CTurret* m_pTurret;
	float m_fRotationRate;
	float m_fRotation;

	float m_fRotationHeight;
	float m_fRotationWidth;

	float m_fSight;
	CPlayer* m_pPlayer;

	tVector2D m_v2OldPos;
};
#endif