#ifndef CENTITY_H
#define CENTITY_H
#include "IEntity.h"
class CEntity:public IEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity*);
	virtual RECT GetRect(void);
	void TakeDamage(int);
	void AddRef(void);
	void Release(void);
	CEntity(void);
	virtual ~CEntity(void);

private:
	int m_nPosX;
	int m_nPosY;
	int m_fVelX;
	int m_fVelY;
	int m_nWidth;
	int m_nHeight;
	int nImageID;
	int m_nColor;
	float m_fHealth;
	float m_fMaxHealth;
	int m_nType;
	int m_nRefCount;

};
#endif