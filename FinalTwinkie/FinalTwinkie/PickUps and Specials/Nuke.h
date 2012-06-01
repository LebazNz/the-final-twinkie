#ifndef CNUKE_H_
#define CNUKE_H_

#include "Special.h"

class CNuke : public CSpecial
{
public:
	CNuke(void);
	~CNuke(void);
	virtual void Update(float fDt);
	virtual void ActivateSpecial(void);

private:
	int		m_nDamage;
	int		m_nRadius;
	float	m_fTimer;
};

#endif