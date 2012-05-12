#include "ParticleManager.h"

CParticleManager* CParticleManager::m_pInstance=nullptr;

CParticleManager* CParticleManager::GetInstance(void)
{
	if(m_pInstance==nullptr)
		m_pInstance=new CParticleManager();
	return m_pInstance;
}

void CParticleManager::DeleteInstance(void)
{
	if(m_pInstance!=nullptr)
	{
		delete m_pInstance;
		m_pInstance=nullptr;
	}
}

CParticleManager::CParticleManager(void)
{
	m_nCurrentIDIndex=0;
}

CParticleManager::~CParticleManager(void)
{
}

void CParticleManager::UpdateEverything(float fDt)
{
	for(unsigned int i=0; i<m_vEmitters.size(); i++)
	{
		m_vEmitters[i]->UpdateParticles(fDt);
	}
}

void CParticleManager::RenderEverything(void)
{
	for(unsigned int i=0; i<m_vEmitters.size(); i++)
	{
		m_vEmitters[i]->RenderParticles();
	}
}

int CParticleManager::AddEmitter(string szFile)
{
	CEmitter* testing=new CEmitter();
	testing->InitEmmitter("");
	m_vEmitters.push_back(testing);
	return m_nCurrentIDIndex++;
}

void CParticleManager::RemoveEmitter(int nEmitterID)
{
	delete(m_vEmitters[nEmitterID]);
	m_vEmitters.erase(m_vEmitters.begin()+nEmitterID);
	m_nCurrentIDIndex--;
}

void CParticleManager::RemoveAllEmitters(void)
{
	for(unsigned int i=0; i<m_vEmitters.size(); i++)
	{
		delete(m_vEmitters[i]);
		m_vEmitters.erase(m_vEmitters.begin()+i);
		i--;
		m_nCurrentIDIndex--;
	}
}