#ifndef CSMOKE_H_
#define CSMOKE_H_

#include "Special.h"
#include "../Particle/Emitter.h"

class CSmoke : public CSpecial
{
public:
	CSmoke(void);
	~CSmoke(void);
	virtual void ActivateSpecial(void);

	virtual void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}

private:
	int		m_nDamage;
	int		m_nRadius;
	float	m_fTime;
	//CEmitter* m_pEmitter;
};

#endif