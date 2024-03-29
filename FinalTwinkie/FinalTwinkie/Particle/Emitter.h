#ifndef EMITTER_H_
#define EMITTER_H_

#include "Particle.h"

#include <string>
#include <vector>
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"
using std::string;

enum Type {Point, CIRCLE, SQUARE, ANGLE};
class CEmitter
{
public:
	CEmitter(void) {}
	~CEmitter(void);
	void InitEmmitter(string szFile);
	void UpdateParticles(float fDt);
	void RenderParticles(void);
	void UpdateEmitterPos(float fPosX, float fPosY);
	void UpdateEmitterDirecton(tVector2D vDir);
	void UpdateRotation(float fRot) {m_fRotation=fRot;}

	void ActivateEmitter(void){m_bActive=true;}
	void DeactivateEmitter(void){m_bActive=false;}

	int NumActiveParticles(void){return m_nNumberParticles;}
	void ResetEmitter(void);

	float GetAngle(void){return m_fAngle;}
	tVector2D GetDir(void) {return m_vDirection;}

	void SetRotation(float Rot){m_fRotation=Rot;}

private:

	void CreateParticle(float fDt);

	bool m_bLooping;
	float m_fMaxLife;
	float m_fMinLife;
	float m_fMaxSpeedX;
	float m_fMaxSpeedY;
	float m_fMinSpeedX;
	float m_fMinSpeedY;
	float m_fMaxScale;
	float m_fMinScale;
	float m_fStartPosX;
	float m_fStartPosY;
	D3DXCOLOR m_dwStartColor;
	D3DXCOLOR m_dwEndColor;
	int m_nNumberParticles;
	int m_nMaxParticles;
	int m_nParticleImage;
	float m_fSpawnTimer;
	float m_fTimer;
	bool m_bExplosion;
	Type m_nType;
	float m_fRadius;
	float m_fAngle;
	bool m_bActive;

	float m_fRotation;

	tVector2D m_vDirection;
	D3DBLEND m_nSource;
	D3DBLEND m_nDest;

	std::vector<CParticle*> m_vParticles;
};

#endif EMITTER_H_