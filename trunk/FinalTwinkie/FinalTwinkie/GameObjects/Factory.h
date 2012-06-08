#pragma once
#include "Entity.h"
#include "Turret.h"
class Factory :
	public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	virtual void TakeDamage(int nDamage);
	Factory(void);
	virtual ~Factory(void);

	void SetTurrets(CTurret* T1, CTurret* T2) {TurretOne=T1; TurretTwo=T2;}
	void SetHP(int nHP){m_nHPID=nHP;}

private:
	CTurret* TurretOne;
	CTurret* TurretTwo;
	int m_nImage;

};

