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
	CBullet(void);
	~CBullet(void);
};
#endif
