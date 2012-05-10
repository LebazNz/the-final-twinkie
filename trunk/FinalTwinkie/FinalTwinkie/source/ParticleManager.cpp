#include "ParticleManager.h"


CParticleManager* CParticleManager::GetInstance(void)
{
	static CParticleManager s_Instance;
	return &s_Instance;
}

CParticleManager::CParticleManager(void)
{
}

CParticleManager::~CParticleManager(void)
{
}

void CParticleManager::UpdateAllParticles(float fDt)
{
}

void CParticleManager::AddParticle(CParticle* pParticle)
{
}

void CParticleManager::DeleteInstance(void)
{
}