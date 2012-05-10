#ifndef BUILDING_H
#define BUILDING_H
#include "IEntity.h"
#include "Entity.h"
#include "Enemy.h"
class CBuilding:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual bool CheckCollision(IEntity*);
	CBuilding(void);
	~CBuilding(void);

private:
	CEnemy* n_pSpawn;
	bool m_bCanSpawn;
	float m_fSpawnTime;
};
#endif