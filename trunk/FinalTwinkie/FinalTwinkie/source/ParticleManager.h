#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include "../source/Emitter.h"

#include <vector>
using namespace std;

class CParticleManager
{
public:
	static CParticleManager* GetInstance(void);
	static void DeleteInstance(void);

	void UpdateEverything(float fDt);
	void RenderEverything(void);
	int AddEmitter(string szFile);
	void RemoveEmitter(int EmitterID);

	void RemoveAllEmitters(void);
	

private:
	CParticleManager(void);
	CParticleManager(const CParticleManager&);
	CParticleManager& operator=(const CParticleManager&);
	~CParticleManager(void);

	vector<CEmitter*> m_vEmitters;
	static CParticleManager* m_pInstance;
	int m_nCurrentIDIndex;

};

#endif PARTICLEMANAGER_H_