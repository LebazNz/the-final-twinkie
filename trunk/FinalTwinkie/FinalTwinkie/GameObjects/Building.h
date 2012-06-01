#ifndef BUILDING_H
#define BUILDING_H
#include "IEntity.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "../Particle/Emitter.h"
class CBuilding:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	virtual void TakeDamage(int nDamage);
	CBuilding(void);
	~CBuilding(void);

	void SetSpawn(int nType) {m_nSpawnType=nType;}
	void SetCanSpawn(bool bSpawn) {m_bCanSpawn=bSpawn;}
	void SetSpawnTime(float fTime) {m_fSpawnTime=fTime;}
	void SetPlayer(CPlayer* pPlayer) {m_pPlayer=pPlayer;}
	void SetFlames(CEmitter* pFlames) {m_pFlames=pFlames;}
	void SetRange(int fRange) {m_fRange=fRange;}

	CEmitter* GetFlames(void) {return m_pFlames;}

	void SetDead(bool dead){m_bDead=dead;}
	void SetDeathImage(int img){m_nDeathImage=img;}
private:
	int m_nSpawnType;
	bool m_bCanSpawn;
	float m_fSpawnTime;
	float m_fTimer;
	CPlayer* m_pPlayer;
	CEmitter* m_pFlames;
	int m_fRange;
	int m_nDeathImage;
	bool m_bDead;
};
#endif