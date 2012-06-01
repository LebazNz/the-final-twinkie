#ifndef CNUKE_H_
#define CNUKE_H_

#include "Special.h"
#include "../Particle/Emitter.h"
#include "../Particle/Particle.h"
#include "../Particle/ParticleManager.h"

class CNuke : public CSpecial
{
public:
	CNuke(void);
	~CNuke(void);
	virtual void Update(float fDt);
	virtual void ActivateSpecial(void);

	void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}

private:
	int		m_nDamage;
	int		m_nRadius;
	float	m_fTimer;
	int		m_nFlames;
	CEmitter* m_pEmitter;
	CParticleManager* m_pPM;
};

#endif