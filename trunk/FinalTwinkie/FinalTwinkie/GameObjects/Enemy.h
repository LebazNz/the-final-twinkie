#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "../Event and Messages/IListener.h"
#include "../Particle/Emitter.h"
#include "../GameObjects/Player.h"

enum ENEMYTYPE { SAPPER, TANK, TURRET, RIFLE, ROCKET, HELP };

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

	void SetFire(CEmitter* Fire){m_pOnFire=Fire;}
	CEmitter* GetTail(void){return m_pOnFire;}

	virtual void HandleEvent(CEvent* pEvent);

	void SetPlayer(CPlayer* pPlayer){m_pPlayer=pPlayer;}
	void SetHelpTarget(CEntity* pTarget){m_pTarget=pTarget;}
	CEntity* GetHelpTarget(void){return m_pTarget;}
	void SetEType(ENEMYTYPE eType){m_nEType=eType;}
	int GetEType(void) { return m_nEType;}
	float GetRotation(void){return m_fRotation;}

	void SetShotTimer(float fTimer){m_fShotTimer=fTimer;}
	void SetOnFire();
	virtual void SetStopTimer(float fTimer){m_fStopTimer = fTimer;}
	virtual float GetStopTimer(void){return m_fStopTimer;}
	virtual void SetStop(bool bStop){m_bStop = bStop;}
	virtual bool GetStop(void){return m_bStop;}

	virtual void TakeDamage(int nDamage);
	void SetSoldierSounds(int sounds[]);

protected:
	bool m_bOnFire;
	bool m_bHurt1;
	bool m_bHurt2;
	float m_fFireTimer;
	CEmitter* m_pOnFire;

private:
	float	m_fMaxDist;
	float	m_fMinDist;
	float	m_fFireRate;
	int		m_nMainBulletType;
	int		m_nMachineGunBulletType;
	bool	m_bHasATurret;
	int     m_anHurtSounds[9];
	
	tVector2D m_v2OldPos;

	ENEMYTYPE m_nEType;
	CPlayer* m_pPlayer;
	CEntity* m_pTarget;

	float m_fRotation;
	float m_fTimer;
	float m_fShotTimer;	
};
#endif