#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "../Event and Messages/IListener.h"
#include "../Particle/Emitter.h"
#include "../GameObjects/Player.h"

enum ENEMYTYPE { SAPPER, TANK, TURRET, RIFLE, ROCKET };

class CEnemy:public CEntity, public IListener
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual int GetType(void)const { return m_nType; }
	
	CEnemy(void);
	virtual ~CEnemy(void);

	virtual float GetMaxDistance(void) { return m_fMaxDist; }
	virtual float GetMinDistance(void) { return m_fMinDist; }
	virtual float GetFireRate(void) { return m_fFireRate; }
	virtual int GetMainBulletType(void) { return m_nMainBulletType; }
	virtual int GetMachineGunBulletType(void) { return m_nMachineGunBulletType; }
	virtual RECT GetRect(void);
	
	virtual void SetMaxDistance(float fMaxDist) { m_fMaxDist = fMaxDist; }
	virtual void SetMinDistance(float fMinDist) { m_fMinDist = fMinDist; }
	virtual void SetFireRate(float fFireRate) { m_fFireRate = fFireRate; }
	virtual void SetMainBulletType(int fMainBulletType) { m_nMainBulletType = fMainBulletType; }
	virtual void SetMachineGunBulletType(int nMachineGunBulletType) { m_nMachineGunBulletType = nMachineGunBulletType; }
	virtual tVector2D GetOldPos(void) { return m_v2OldPos;}
	bool GetHasATuert(void)const{return m_bHasATurret;}
	void SetHasATurret(bool bTurret){m_bHasATurret = bTurret;}

	void SetTail(CEmitter* Tail){m_pTail=Tail;}
	CEmitter* GetTail(void){return m_pTail;}

	virtual void HandleEvent(CEvent* pEvent);

	void SetPlayer(CPlayer* pPlayer){m_pPlayer=pPlayer;}
	void SetEType(ENEMYTYPE eType){m_nEType=eType;}
	float GetRotation(void){return m_fRotation;}

	void SetShotTimer(float fTimer){m_fShotTimer=fTimer;}
	void SetOnFire();
	virtual void SetStopTimer(float fTimer){m_fStopTimer = fTimer;}
	virtual float GetStopTimer(void){return m_fStopTimer;}
	virtual void SetStop(bool bStop){m_bStop = bStop;}
	virtual bool GetStop(void){return m_bStop;}

private:
	float	m_fMaxDist;
	float	m_fMinDist;
	float	m_fFireRate;
	int		m_nMainBulletType;
	int		m_nMachineGunBulletType;
	bool	m_bHasATurret;
	
	tVector2D m_v2OldPos;

	CEmitter* m_pTail;

	ENEMYTYPE m_nEType;
	CPlayer* m_pPlayer;

	float m_fRotation;
	float m_fTimer;
	float m_fShotTimer;

	bool m_bOnFire;
	bool m_bHurt1;
	bool m_bHurt2;
	float m_fFireTimer;
};
#endif