#ifndef CNUKE_H_
#define CNUKE_H_

#include "Special.h"
#include "../Particle/Emitter.h"

class CNuke : public CSpecial
{
public:
	CNuke(void);
	~CNuke(void);

	virtual void ActivateSpecial(void);

	virtual void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}
	

private:
	int		m_nDamage;
	int		m_nRadius;
	float	m_fTimer;
	int		m_nFlames;
	//CEmitter* m_pEmitter;
};

#endif