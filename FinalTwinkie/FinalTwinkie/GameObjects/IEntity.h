#ifndef IENTITY_H
#define IENTITY_H

#include <Windows.h>


class IEntity
{
public:
	virtual ~IEntity(void) = 0 {}
	virtual bool CheckCollision(IEntity* pObject) = 0;
	virtual RECT GetRect(void) = 0;
	virtual int GetType(void) const = 0;
	virtual void Update(float fDt) = 0;
	virtual void AddRef(void) = 0;
	virtual void Render(void) = 0;
	virtual void Release(void) = 0;
};
#endif