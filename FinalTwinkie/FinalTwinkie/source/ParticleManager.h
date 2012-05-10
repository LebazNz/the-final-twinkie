#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include "Particle.h"

#include <vector>
using namespace std;

class CParticleManager
{
public:
	static CParticleManager* GetInstance(void);
	void UpdateAllParticles(float fDt);
	void AddParticle(CParticle* pParticle);
	void DeleteInstance(void);

private:
	CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);
	~CParticleManager(void);

	vector<CParticle*> m_vParticles;	

};

#endif PARTICLEMANAGER_H_