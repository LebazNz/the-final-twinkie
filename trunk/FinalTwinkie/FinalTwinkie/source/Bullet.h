#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
class CBullet:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	CBullet(void);
	~CBullet(void);
};
#endif
