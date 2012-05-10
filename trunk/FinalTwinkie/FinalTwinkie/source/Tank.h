#ifndef TANK_H
#define TANK_H
#include "Enemy.h"
#include "Turret.h"
class CTank:public CEnemy
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	CTank(void);
	~CTank(void);

private:
	CTurret* m_pTurret;
	float m_fRotationRate;

};
#endif