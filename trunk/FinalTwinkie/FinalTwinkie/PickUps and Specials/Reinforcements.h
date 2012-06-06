#ifndef CREINFORCEMENTS_H_
#define CREINFORCEMENTS_H_

#include "Special.h"
#include <vector>
using namespace std;
class CEntity;
class CEnemy;

class CReinforcements :
	public CSpecial
{
public:
	CReinforcements(void);
	~CReinforcements(void);

	virtual void ActivateSpecial(void);	
};

#endif