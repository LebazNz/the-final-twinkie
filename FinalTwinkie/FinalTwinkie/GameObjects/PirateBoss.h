#ifndef PIRATEBOSSS_H_
#define PIRATEBOSS_H_
#include "Entity.h"
class CTurret;

class CPirateBoss : public CEntity
{
private:
	int m_nTurretCount;
	int m_nRoundTwo;
	int m_nTurrID;
	int m_nStartX;
	int m_nHealthBar;

	CTurret *tOne;
	CTurret *tTwo;
	CTurret *tThree;

	CTurret *tFour;
	CTurret *tFive;
	CTurret *tSix;

	void Rebound(float time);
	void KillTurrets(void);
	
	bool m_bChanged;
	int m_nMoving;

public:
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	virtual RECT GetRect(void);
	virtual void TakeDamage(int nDamage);

	CPirateBoss(void);
	~CPirateBoss(void);

	void SetOppImage(int n) { m_nRoundTwo = n;}
	void SetTurrID(int t) { m_nTurrID = t;}
	void SetStartX(int x) { m_nStartX = x;}
	void MakeTurrets(void);
};

#endif