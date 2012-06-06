#ifndef CEMP_H_
#define CEMP_H_

#include "Special.h"
#include "../GameObjects/Entity.h"

class CEMP : public CSpecial, public CEntity
{
public:
	CEMP(void);
	~CEMP(void);
	virtual void Render(void);
	virtual void Update(float fDt);
	virtual void ActivateSpecial(void);

private:
	int m_nRadius;
	float m_fScale;
	int m_nEMPID;
};

#endif
