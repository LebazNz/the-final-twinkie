#ifndef MINE_H_
#define MINE_H_

#include "Entity.h"

class CMine : public CEntity
{
public:
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	CMine(void);
	~CMine(void);
};

#endif