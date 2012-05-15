#ifndef TURRET_H
#define TURRET_H
#include "Entity.h"
#include "../SGD Wrappers/SGD_Math.h"


#define SHOTCOOLDOWN 0.25

class CTurret:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);

	// Setters
	void SetBullet(int bullet) { m_nBulletType = bullet;}
	void SetTarget(CEntity* player) { m_pTarget = player;}
	void SetOwner(CEntity* owner) { m_pOwner = owner;}
	void SetRotationRate(float rotate) { m_fRotationRate = rotate;}


	// Getters
	int GetBullet(void) { return m_nBulletType;}
	tVector2D GetLook(void) { return m_vLookVec; }
	CEntity* GetOwner(void) { return m_pOwner;}
	float GetRotationRate(void) { return m_fRotationRate;}
	

	CTurret(void);
	~CTurret(void);

private:
	float m_fRotPosX, m_fRotPosY;
	float m_fMaxDistance;
	float m_fRotation;
	float m_fRotationRate;
	float m_fFireRate;
	CEntity* m_pOwner;
	CEntity* m_pTarget;
	int m_nBulletType;
	tVector2D m_vLookVec;
};
#endif