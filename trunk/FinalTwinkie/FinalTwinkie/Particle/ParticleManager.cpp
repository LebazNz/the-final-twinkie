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
	for(unsigned int i=0; i<m_vAttachedEmitters.size(); i++)
	{
		m_vAttachedEmitters[i]->UpdateParticles(fDt);
	}
	for(unsigned int i=0; i<m_vForDestroy.size(); i++)
	{
		m_vForDestroy[i]->UpdateParticles(fDt);
		if(m_vForDestroy[i]->NumActiveParticles()==0)
		{
			delete(m_vForDestroy[i]);
			m_vForDestroy.erase(m_vForDestroy.begin()+i);
			i--;
		}
	}
}

void CParticleManager::RenderEverything(void)
{
	for(unsigned int i=0; i<m_vAttachedEmitters.size(); i++)
	{
		m_vAttachedEmitters[i]->RenderParticles();
	}
	for(unsigned int i=0; i<m_vForDestroy.size(); i++)
	{
		m_vForDestroy[i]->RenderParticles();
	}
}

int CParticleManager::AddEmitter(string szFile)
{
	CEmitter* testing=new CEmitter();
	testing->InitEmmitter(szFile);
	m_vBaseEmitters.push_back(testing);
	return m_nCurrentIDIndex++;
}

void CParticleManager::RemoveBaseEmitter(int nEmitterID)
{
	delete(m_vBaseEmitters[nEmitterID]);
	m_vBaseEmitters.erase(m_vBaseEmitters.begin()+nEmitterID);
	m_nCurrentIDIndex--;
}

void CParticleManager::RemoveAllBaseEmitters(void)
{
	for(unsigned int i=0; i<m_vBaseEmitters.size(); i++)
	{
		delete(m_vBaseEmitters[i]);
		m_vBaseEmitters.erase(m_vBaseEmitters.begin()+i);
		i--;
		m_nCurrentIDIndex--;
	}

	for(unsigned int i=0; i<m_vAttachedEmitters.size(); i++)
	{
		delete(m_vAttachedEmitters[i]);
		m_vAttachedEmitters.erase(m_vAttachedEmitters.begin()+i);
		i--;
	}
}

CEmitter* CParticleManager::GetEmitter(int EmitterID)
{
	CEmitter* newEmitter=new CEmitter();
	*newEmitter=*m_vBaseEmitters[EmitterID];
	m_vAttachedEmitters.push_back(newEmitter);
	return newEmitter;
}

void CParticleManager::RemoveAttachedEmitter(CEmitter* pEmitter)
{
	for(unsigned int i=0; i<m_vAttachedEmitters.size(); i++)
	{
		if(m_vAttachedEmitters[i]==pEmitter)
		{
			m_vAttachedEmitters[i]->DeactivateEmitter();
			m_vForDestroy.push_back(m_vAttachedEmitters[i]);
			m_vAttachedEmitters.erase(m_vAttachedEmitters.begin()+i);
			break;
		}
	}
}