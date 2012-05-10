#ifndef IENTITY_H
#define IENTITY_H
#include <Windows.h>
class IEntity
{
	virtual bool CheckCollision(IEntity*)=0;
	virtual RECT GetRect(void)=0;
	virtual void Update(float)=0;
	virtual void AddRef(void)=0;
	virtual void Render(void)=0;
	virtual void Release(void)=0;
};
#endif