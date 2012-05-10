#ifndef ENEMY_H
#define ENEMY_H
#include "IEntity.h"
#include "Entity.h"
class CEnemy:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	CEnemy(void);
	~CEnemy(void);

private:
	float m_fMaxDist;
	float m_fMinDist;
	int m_nBulletType;
	float m_fFireRate;

};
#endif