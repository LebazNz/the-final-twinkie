#ifndef BUILDING_H
#define BUILDING_H
#include "IEntity.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
class CBuilding:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	CBuilding(void);
	~CBuilding(void);

	void SetSpawn(CEnemy* pEnemy) {m_pSpawn=pEnemy;}
	void SetCanSpawn(bool bSpawn) {m_bCanSpawn=bSpawn;}
	void SetSpawnTime(float fTime) {m_fSpawnTime=fTime;}
	void SetPlayer(CPlayer* pPlayer) {m_pPlayer=pPlayer;}

private:
	CEnemy* m_pSpawn;
	bool m_bCanSpawn;
	float m_fSpawnTime;
	CPlayer* m_pPlayer;
};
#endif