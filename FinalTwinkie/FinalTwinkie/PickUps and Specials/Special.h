#ifndef CSPECIAL_H_
#define CSPECIAL_H_

#include "../Particle/Emitter.h"

enum SpecialType{SPECIAL,SMOKE,EMP,NUKE,REINFORCE,AIRSTRIKE };

class CSpecial
{
public:
	CSpecial(void);
	~CSpecial(void);

	virtual void Update(float fDt);
	virtual void Render(void);
	virtual void ActivateSpecial(void);
	virtual void SetAmmoCount(int nAmmo) {m_nAmmo = nAmmo;}
	virtual int GetAmmoCount(void){return m_nAmmo;}
	virtual void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}

	int GetType(void){return m_nType;}
	void SetType(int Type){m_nType=Type;}

protected:
	int		m_nAmmo;
	float	m_fDuration;
	int		m_nType;
	CEmitter* m_pEmitter;
};


#endif

