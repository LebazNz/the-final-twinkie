#ifndef CSMOKE_H_
#define CSMOKE_H_

#include "Special.h"
class CSmoke : public CSpecial
{
public:
	CSmoke(void);
	~CSmoke(void);

private:
	int m_nRadius;
	float m_fTime;
};

#endif