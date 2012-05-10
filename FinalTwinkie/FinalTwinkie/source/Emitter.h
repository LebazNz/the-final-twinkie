#ifndef EMITTER_H_
#define EMITTER_H_

#include "ParticleManager.h"

#include <string>
using std::string;

class CEmitter
{
public:
	CEmitter(void) {}
	~CEmitter(void) {}
	void CreateParticle(void);
	void InitEmmitter(string szFile);

private:
	bool m_bLooping;
	float m_fMaxLife;
	float m_fMaxVelocityX;
	float m_fMaxVelocityY;
	float m_fMinVelocityX;
	float m_fMinVelocityY;
	float m_fMaxScale;
	float m_fMinSclae;
	int m_nStartPosX;
	int m_nStartPosY;
	DWORD m_dwStartColor;
	DWORD m_dwEndColor;

	CParticleManager* m_pPM;
};

#endif EMITTER_H_