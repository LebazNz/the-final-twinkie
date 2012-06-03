#ifndef CAIRSTRIKE_H_
#define CAIRSTRIKE_H_

#include "special.h"
class CAirStrike : public CSpecial
{
public:
	CAirStrike(void);
	~CAirStrike(void);
	virtual void Update(float fDt);
	virtual void ActivateSpecial(void);

	virtual void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}

private:
	float m_fDamage;
	int m_nRadius;
	int m_nAmount;
};


#endif