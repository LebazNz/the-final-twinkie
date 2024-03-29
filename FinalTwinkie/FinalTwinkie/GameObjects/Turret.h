#ifndef TURRET_H
#define TURRET_H
#include "Entity.h"
#include "../SGD Wrappers/SGD_Math.h"
#include "../Particle/Emitter.h"

#define SHOT_DELAY 1.0

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
	void SetUpVec(float x, float y);
	void SetRotationPositon(float fRX, float fRY) {m_fRotPosX=fRX; m_fRotPosY=fRY;}
	void SetFireRate(float fFireRate){m_fFireRate = fFireRate;}
	void SetDistance(float fDistance) {m_fMaxDistance=fDistance;}
	void SetFlamer(CEmitter* pEmitter) {m_pFlamer=pEmitter;}
	CEmitter* GetFlamer(void) {return m_pFlamer;}

	virtual void TakeDamage(int nDamage);


	// Getters
	int GetBullet(void) { return m_nBulletType;}
	tVector2D GetLook(void) { return m_vLookVec; }
	CEntity* GetOwner(void) { return m_pOwner;}
	float GetRotationRate(void) { return m_fRotationRate;}
	float GetRotation(void) { return m_fRotation; }
	float GetRotationX(void) { return m_fRotPosX; }
	float GetRotationY(void) { return m_fRotPosY; }

	virtual RECT GetRect(void);
	

	CTurret(void);
	~CTurret(void);

private:
	float m_fRotPosX, m_fRotPosY;
	float m_fMaxDistance;
	float m_fRotation;
	float m_fRotationRate;
	float m_fFireRate;
	float m_fFireTimer;
	CEntity* m_pOwner;
	CEntity* m_pTarget;
	int m_nBulletType;
	tVector2D m_vLookVec;
	tVector2D m_vUpVec;

	float m_fRotationHeight;
	float m_fRotationWidth;
	CEmitter* m_pFlamer;
};
#endif