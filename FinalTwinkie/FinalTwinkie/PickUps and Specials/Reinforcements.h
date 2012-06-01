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
	CEntity* GetTarget(void);

private:
	int m_nAmmount;
	vector<CEnemy*> m_vUnits;
};

#endif