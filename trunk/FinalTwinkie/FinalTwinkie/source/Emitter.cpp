#include "Emitter.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
void CEmitter::CreateParticle(float fDt=0)
{
	for(int i=0; i<m_nMaxParticles; i=m_nNumberParticles)
	{
		if(m_fTimer>m_fSpawnTimer)
		{
			CParticle* newPart=new CParticle();
			newPart->CreateParticle(m_fMaxLife,(((rand()%361)/180.0)-1.0)/2,(((rand()%361)/180.0)-1.0)/2,m_fMaxScale,m_nStartPosX, m_nStartPosY, m_dwStartColor);
			m_vParticles.push_back(newPart);
			m_nNumberParticles++;
			m_fTimer=0;
		}
		else
		{
			m_fTimer+=fDt;
		}
	}
}

void CEmitter::InitEmmitter(string szFile)
{
	m_bLooping=true;
	m_fMaxLife=2.0;
	m_fMaxVelocityX=(rand()%2)-1;
	m_fMaxVelocityY=(rand()%2)-1;
	m_fMinVelocityX=1.0;
	m_fMinVelocityY=1.0;
	m_fMaxScale=0.5;
	m_fMinScale=0.0;
	m_nStartPosX=CGame::GetInstance()->GetWidth()/2;
	m_nStartPosY=CGame::GetInstance()->GetHeight()/2;
	m_dwStartColor=D3DCOLOR_ARGB(180,255,141,0);
	m_dwEndColor=D3DCOLOR_ARGB(0,255,140,0);
	m_nMaxParticles=90;
	m_nNumberParticles=0;
	m_nParticleImage=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/Cloud.png"));
	m_fSpawnTimer=.001;
	m_fTimer=0;
}

void CEmitter::UpdateParticles(float fDt)
{
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{
		if(m_vParticles[i]->m_fCurLife>0)
		{
			m_vParticles[i]->m_fCurLife-=fDt;
		}
		else
		{
			delete m_vParticles[i];
			m_vParticles.erase(m_vParticles.begin()+i);
			i--;
			continue;
		}
		if(m_vParticles[i]->m_fScale>m_fMinScale)
		{
			m_vParticles[i]->m_fScale-=((m_fMaxScale-m_fMinScale)/m_fMaxLife)*fDt;
		}
		if(m_vParticles[i]->m_dwColor>m_dwEndColor)
		{
			int x =(180/m_fMaxLife)*fDt;//*fDt;
			m_vParticles[i]->m_dwColor-=D3DCOLOR_ARGB(x,0,0,0);
		}
		m_vParticles[i]->m_nCurPosX+=m_vParticles[i]->m_fCurVelocityX;
		m_vParticles[i]->m_nCurPosY+=m_vParticles[i]->m_fCurVelocityY;
	}
	if(m_bLooping)
	{
		CreateParticle(fDt);
	}
}

void CEmitter::RenderParticles(void)
{
	CSGD_TextureManager* Tm= CSGD_TextureManager::GetInstance();
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{	
		
		Tm->Draw(m_nParticleImage, m_vParticles[i]->m_nCurPosX, m_vParticles[i]->m_nCurPosY,
			m_vParticles[i]->m_fScale, m_vParticles[i]->m_fScale, NULL, 16,16,0,m_vParticles[i]->m_dwColor);
	}
}