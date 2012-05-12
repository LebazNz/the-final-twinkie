#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <Windows.h>

class CParticle
{
public:
	void Update(float fDt);
	void Render(void);
	void CreateParticle(float fLife, float fVelocityX, float fVelocityY, float fScale, int nPosX, int nPosY, DWORD dwColor);

//private:
	float m_fCurLife;
	float m_fCurVelocityX;
	float m_fCurVelocityY;
	float m_fScale;
	float m_nCurPosX;
	float m_nCurPosY;
	DWORD m_dwColor;

};

#endif PARTICLE_H_