#include "Particle.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"

void CParticle::Update(float fDt)
{
}

void CParticle::Render(void)
{
	CSGD_TextureManager* Tm= CSGD_TextureManager::GetInstance();
	Camera* C=Camera::GetInstance();
	Tm->Draw(m_nParticleID, (int)(m_fCurPosX+C->GetPosX())-16, (int)(m_fCurPosY+C->GetPosY())-16, m_fScale, m_fScale, NULL, 16,16,0, m_dwColor);
}

void CParticle::CreateParticle(float fLife, float fVelocityX, float fVelocityY, float fScale, float nPosX, float nPosY, DWORD dwColor, int nImage)
{
	m_fCurLife=fLife;
	m_fCurVelocityX=fVelocityX;
	m_fCurVelocityY=fVelocityY;
	m_fScale=fScale;
	m_fCurPosX=nPosX;
	m_fCurPosY=nPosY;
	m_dwColor=dwColor;
	m_nParticleID=nImage;
	m_fTotalLife=fLife;
}