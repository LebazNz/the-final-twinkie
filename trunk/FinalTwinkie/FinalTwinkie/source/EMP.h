#ifndef CEMP_H_
#define CEMP_H_

#include "Special.h"
class CEMP : public CSpecial
{
public:
	CEMP(void);
	~CEMP(void);
private:
	int m_nRadius;
};

#endif
