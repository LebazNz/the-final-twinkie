#ifndef CAIRSTRIKE_H_
#define CAIRSTRIKE_H_

#include "special.h"
class CAirStrike : public CSpecial
{
public:
	CAirStrike(void);
	~CAirStrike(void);

private:
	float m_fDamage;
	int m_nRadius;
	int m_nAmount;
};


#endif