#ifndef CNUKE_H_
#define CNUKE_H_

#include "Special.h"
class CNuke :
	public CSpecial
{
public:
	CNuke(void);
	~CNuke(void);

private:
	float m_fDamage;
	int m_nRadius;
};

#endif