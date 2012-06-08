#pragma once
#include "BossTurret.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Player.h"
class CNaziBoss:public CEntity
{
public:
	CNaziBoss(void);
	virtual ~CNaziBoss(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	virtual void TakeDamage(int nDamage);
	void CreateTurrets(void);

	void SetTurrets(CBossTurret* LMG, CBossTurret* RMG, CBossTurret* LRKT, CBossTurret* RRKT, CBossTurret* Cannon);
	void ChangeStates(int state);

	void SetPlayer(CPlayer* pPlayer) {m_pPlayer=pPlayer;}

	float GetState(void){ return m_nCurrentState;}
	void SetCollision(void) {Charging=false; Rotating=true;}
	bool GetCharging(void) {return Charging;}

	int GetBossType(void) {return m_nBossType;}

private:
	CBossTurret* m_pLMG;
	CBossTurret* m_pRMG;
	CBossTurret* m_pLRKT;
	CBossTurret* m_pRRKT;
	CBossTurret* m_pCannon;
	CPlayer* m_pPlayer;

	int m_nCurrentState;
	int m_nBossType;

	float m_fRotation;

	float m_fRotationHeight;
	float m_fRotationWidth;

	bool Charging;
	bool Rotating;
	bool Aquiring;
	bool Waiting;

	float WaitTimer;

	tVector2D PlayerPos;
	RECT StopRect;
	RECT CheckRect;
};

