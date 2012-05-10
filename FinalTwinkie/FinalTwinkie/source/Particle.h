#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <Windows.h>

class CParticle
{
public:
	void Update(float fDt);
	void Render(void);
private:
	float m_fCurLife;
	float m_fCurVelocityX;
	float m_fCurVelocityY;
	float m_fScale;
	int m_nCurPosX;
	int m_nCurPosY;
	DWORD m_dwColor;

};

#endif PARTICLE_H_