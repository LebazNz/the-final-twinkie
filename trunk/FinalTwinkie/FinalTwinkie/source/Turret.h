#ifndef TURRET_H
#define TURRET_H
#include "Entity.h"
class CTurret:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	CTurret(void);
	~CTurret(void);

private:
	float m_fRotationRate;
	float m_fFireRate;
	CEntity* m_pOwner;
	int m_nBulletType;
};
#endif