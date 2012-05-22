#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <Windows.h>
#include "../SGD Wrappers/CSGD_Direct3D.h"

class CParticle
{
public:
	void Update(float fDt);
	void Render(void);
	void CreateParticle(float fLife, float fVelocityX, float fVelocityY, float fScale, float nPosX, float nPosY, DWORD dwColor, int nImage);

private:
	float m_fCurLife;
	float m_fCurVelocityX;
	float m_fCurVelocityY;
	float m_fScale;
	float m_fCurPosX;
	float m_fCurPosY;
	D3DXCOLOR m_dwColor;
	int m_nParticleID;
	float m_fTotalLife;

public:

	float GetScale(void){return m_fScale;}
	void SetScale(float S){m_fScale=S;}

	float GetVelocityY(void){return m_fCurVelocityY;}
	void SetVelocityY(float VY){m_fCurVelocityY=VY;}

	float GetVelocityX(void){return m_fCurVelocityX;}
	void SetVelocityX(float VX) {m_fCurVelocityX=VX;}

	float GetLife(void){return m_fCurLife;}
	void SetLife(float L){m_fCurLife=L;}

	D3DCOLOR GetColor(void){return m_dwColor;}
	void SetColor(D3DCOLOR C){m_dwColor=C;}

	float GetPosX(void){return m_fCurPosX;}
	void SetPosX(float PX){m_fCurPosX=PX;}

	float GetPosY(void){return m_fCurPosY;}
	void SetPosY(float PY) {m_fCurPosY=PY;}

	float GetTotalLife(void) {return m_fTotalLife;}

};

#endif PARTICLE_H_