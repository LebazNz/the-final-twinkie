#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "../Event and Messages/IListener.h"
#include "../Particle/Emitter.h"

enum ENEMYTYPE { SAPPER, TANK, TURRET };

class CEnemy:public CEntity, public IListener
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	virtual int GetType(void)const { return m_nType; }
	
	CEnemy(void);
	virtual ~CEnemy(void);

	virtual float GetMaxDistance(void) { return m_fMaxDist; }
	virtual float GetMinDistance(void) { return m_fMinDist; }
	virtual float GetFireRate(void) { return m_fFireRate; }
	virtual int GetMainBulletType(void) { return m_nMainBulletType; }
	virtual int GetMachineGunBulletType(void) { return m_nMachineGunBulletType; }
	
	virtual void SetMaxDistance(float fMaxDist) { m_fMaxDist = fMaxDist; }
	virtual void SetMinDistance(float fMinDist) { m_fMinDist = fMinDist; }
	virtual void SetFireRate(float fFireRate) { m_fFireRate = fFireRate; }
	virtual void SetMainBulletType(int fMainBulletType) { m_nMainBulletType = fMainBulletType; }
	virtual void SetMachineGunBulletType(int nMachineGunBulletType) { m_nMachineGunBulletType = nMachineGunBulletType; }

	void SetTail(CEmitter* Tail){m_pTail=Tail;}
	CEmitter* GetTail(void){return m_pTail;}

	virtual void HandleEvent(CEvent* pEvent);

private:
	float	m_fMaxDist;
	float	m_fMinDist;
	float	m_fFireRate;
	int		m_nMainBulletType;
	int		m_nMachineGunBulletType;
	

	CEmitter* m_pTail;
};
#endif