#include "Emitter.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
void CEmitter::CreateParticle(float fDt=0)
{
	if(m_nNumberParticles<=m_nMaxParticles)
	{
		if(m_bExplosion)
		{
			for(;;)
			{
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(m_fMaxLife,(float)(((rand()%361)/180.0)-1.0)/2,(float)(((rand()%361)/180.0)-1.0)/2,m_fMaxScale,(float)m_nStartPosX,(float) m_nStartPosY, m_dwStartColor);
				m_vParticles.push_back(newPart);
				m_nNumberParticles++;
				if(m_nNumberParticles>=m_nMaxParticles)
				{
					break;
				}
			}
		}
		else
		{
			if(m_fTimer>m_fSpawnTimer)
			{
				CParticle* newPart=new CParticle();
				newPart->CreateParticle(m_fMaxLife,(float)(((rand()%361)/180.0)-1.0)/2,(float)(((rand()%361)/180.0)-1.0)/2,m_fMaxScale,(float)m_nStartPosX, (float)m_nStartPosY, m_dwStartColor);
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
}

void CEmitter::InitEmmitter(string szFile)
{
	m_bLooping=true;
	m_bExplosion=false;
	m_fMaxLife=2.0;
	m_fMaxVelocityX=(float)(rand()%2)-1;
	m_fMaxVelocityY=(float)(rand()%2)-1;
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
	m_fSpawnTimer=.01f;
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
			if(m_bLooping)
				m_nNumberParticles--;
			continue;
		}
		if(m_vParticles[i]->m_fScale>m_fMinScale)
		{
			m_vParticles[i]->m_fScale-=((m_fMaxScale-m_fMinScale)/m_fMaxLife)*fDt;
		}
		if(m_vParticles[i]->m_dwColor>m_dwEndColor)
		{
			int x =(int)((180/m_fMaxLife)*fDt);
			m_vParticles[i]->m_dwColor-=D3DCOLOR_ARGB(x,0,0,0);
		}
		m_vParticles[i]->m_fCurPosX+=m_vParticles[i]->m_fCurVelocityX;
		m_vParticles[i]->m_fCurPosY+=m_vParticles[i]->m_fCurVelocityY;
	}
	CreateParticle(fDt);
}

void CEmitter::RenderParticles(void)
{
	CSGD_TextureManager* Tm= CSGD_TextureManager::GetInstance();
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{	
		
		Tm->Draw(m_nParticleImage, (int)m_vParticles[i]->m_fCurPosX, (int)m_vParticles[i]->m_fCurPosY,
			m_vParticles[i]->m_fScale, m_vParticles[i]->m_fScale, NULL, 16,16,0,m_vParticles[i]->m_dwColor);
	}
}

CEmitter::~CEmitter(void)
{
	for(unsigned int i=0; i<m_vParticles.size(); i++)
	{
		delete m_vParticles[i];
		m_vParticles.erase(m_vParticles.begin()+i);
		i--;
	}
}