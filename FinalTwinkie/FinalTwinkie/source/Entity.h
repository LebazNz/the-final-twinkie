#ifndef CENTITY_H
#define CENTITY_H

#include "IEntity.h"

enum OBJECT_TYPE { OBJ_BASE, OBJ_PLAYER, OBJ_BULLET, OBJ_ENEMY };
enum BULLETYPE { BUL_SHELL, BUL_ROCKET, BUL_ARTILLERY, BUL_MACHINEGUN, BUL_LASER };


class CEntity: public IEntity
{
public:
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	virtual RECT GetRect(void)const;
	virtual int GetType(void)const { return m_nType; }
	virtual int GetImageID(void) { return m_nImageID; }

	virtual void SetImageID(int nImageID) { m_nImageID = nImageID; }

	virtual void AddRef(void);
	virtual void Release(void);

	CEntity(void);
	virtual ~CEntity(void);

	void TakeDamage(int nDamage);

	virtual int GetPosX(void) {return m_nPosX; }
	virtual int GetPosY(void) {return m_nPosY; }
	virtual int GetWidth(void) { return m_nWidth; }
	virtual int GetHeight(void) { return m_nHeight; }
	virtual int GetColor(void) { return m_nColor; }

	virtual void SetPosX(int nPosX) {m_nPosX = nPosX; }
	virtual void SetPosY(int nPosY) {m_nPosY = nPosY; }
	virtual void SetWidth(int nWidth) {m_nWidth = nWidth; }
	virtual void SetHeight(int nHeight) {m_nHeight = nHeight; }
	virtual void SetColor(int nColor) {m_nColor = nColor; }


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