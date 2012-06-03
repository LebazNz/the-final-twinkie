#ifndef CEMP_H_
#define CEMP_H_

#include "Special.h"
class CEMP : public CSpecial
{
public:
	CEMP(void);
	~CEMP(void);
	virtual void Update(float fDt);
	virtual void ActivateSpecial(void);

	virtual void SetEmitter(CEmitter* pEmitter){m_pEmitter = pEmitter;}
private:
	int m_nRadius;
};

#endif
