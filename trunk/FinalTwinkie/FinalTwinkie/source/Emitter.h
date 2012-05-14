#ifndef EMITTER_H_
#define EMITTER_H_

#include "Particle.h"

#include <string>
#include <vector>
using std::string;

class CEmitter
{
public:
	CEmitter(void) {}
	~CEmitter(void);
	void InitEmmitter(string szFile);
	void UpdateParticles(float fDt);
	void RenderParticles(void);

private:

	void CreateParticle(float fDt);

	bool m_bLooping;
	float m_fMaxLife;
	float m_fMaxVelocityX;
	float m_fMaxVelocityY;
	float m_fMinVelocityX;
	float m_fMinVelocityY;
	float m_fMaxScale;
	float m_fMinScale;
	int m_nStartPosX;
	int m_nStartPosY;
	DWORD m_dwStartColor;
	DWORD m_dwEndColor;
	int m_nNumberParticles;
	int m_nMaxParticles;
	int m_nParticleImage;
	float m_fSpawnTimer;
	float m_fTimer;
	bool m_bExplosion;

	std::vector<CParticle*> m_vParticles;
};

#endif EMITTER_H_