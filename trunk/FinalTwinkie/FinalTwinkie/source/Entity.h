#ifndef CENTITY_H
#define CENTITY_H

#include "IEntity.h"


enum OBJECT_TYPE { OBJ_BASE, OBJ_PLAYER, OBJ_BULLET, OBJ_ENEMY };

class CEntity: public IEntity
{
public:
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	virtual RECT GetRect(void);
	virtual int GetType(void);	

	virtual void AddRef(void);
	virtual void Release(void);

	CEntity(void);
	virtual ~CEntity(void);

	void TakeDamage(int nDamage);

private:
	// Position
	int m_nPosX;
	int m_nPosY;
	// Velocity
	int m_fVelX;
	int m_fVelY;
	// Size
	int m_nWidth;
	int m_nHeight;
	// Image
	int m_nImageID;
	int m_nColor;
	// Health
	float m_fHealth;
	float m_fMaxHealth;	
	// Reference Counter
	int m_nRefCount;

protected:
	// Object Type
	int m_nType;

};
#endif