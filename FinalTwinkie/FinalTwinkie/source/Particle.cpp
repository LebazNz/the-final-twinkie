#include "Particle.h"


void CParticle::Update(float fDt)
{
}

void CParticle::Render(void)
{
}

void CParticle::CreateParticle(float fLife, float fVelocityX, float fVelocityY, float fScale, float nPosX, float nPosY, DWORD dwColor)
{
	m_fCurLife=fLife;
	m_fCurVelocityX=fVelocityX;
	m_fCurVelocityY=fVelocityY;
	m_fScale=fScale;
	m_fCurPosX=nPosX;
	m_fCurPosY=nPosY;
	m_dwColor=dwColor;
}