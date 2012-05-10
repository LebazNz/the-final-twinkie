#ifndef SAPPER_H
#define SAPPER_H
#include "IEntity.h"
#include "Enemy.h"
class CSapper:public CEnemy
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	CSapper(void);
	~CSapper(void);

private:
	float m_fRaduis;
	float m_fDamage;
};
#endif