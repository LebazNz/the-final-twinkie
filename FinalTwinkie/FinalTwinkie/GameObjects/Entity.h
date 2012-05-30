#ifndef CENTITY_H
#define CENTITY_H

#include "IEntity.h"
#include "../SGD Wrappers/SGD_Math.h"
class CTileManager;

#include <vector>
enum OBJECT_TYPE { OBJ_BASE, OBJ_PLAYER, OBJ_BULLET, OBJ_ENEMY, OBJ_TURRET, OBJ_PICKUP, OBJ_BUILDING };
enum BULLETYPE { BUL_SHELL, BUL_ROCKET, BUL_ARTILLERY, BUL_MACHINEGUN, BUL_LASER };


class CEntity: public IEntity
{
public:
	virtual void Update(float fDt);
	virtual void Render(void);
	virtual bool CheckCollision(IEntity* pObject);
	virtual RECT GetRect(void);
	virtual int GetType(void)const { return m_nType; }
	virtual int GetImageID(void) { return m_nImageID; }

	virtual void SetImageID(int nImageID) { m_nImageID = nImageID; }

	virtual void AddRef(void);
	virtual void Release(void);

	CEntity(void);
	virtual ~CEntity(void);

	void TakeDamage(int nDamage);

	virtual float GetPosX(void) {return m_fPosX; }
	virtual float GetPosY(void) {return m_fPosY; }
	virtual float GetVelX(void) {return m_fVelX; }
	virtual float GetVelY(void) {return m_fVelY; }
	virtual int GetWidth(void) { return m_nWidth; }
	virtual int GetHeight(void) { return m_nHeight; }
	virtual int GetColor(void) { return m_nColor; }
	virtual float GetHealth(void) { return m_fHealth; }

	virtual void SetPosX(float fPosX) {m_fPosX = fPosX; }
	virtual void SetPosY(float fPosY) {m_fPosY = fPosY; }
	virtual void SetVelX(float fVelX) {m_fVelX = fVelX; }
	virtual void SetVelY(float fVelY) {m_fVelY = fVelY; }
	virtual void SetWidth(int nWidth) {m_nWidth = nWidth; }
	virtual void SetHeight(int nHeight) {m_nHeight = nHeight; }
	virtual void SetColor(int nColor) {m_nColor = nColor; }
	virtual void SetHealth(float fHealth) { m_fHealth = fHealth; }

	virtual tVector2D GetOldPos(void) { return m_v2OldPos;}
	virtual void AddEmitter(int nEmitter){ m_vEmitters.push_back(nEmitter);  }

private:
	// Position
	float m_fPosX;
	float m_fPosY;
	// Velocity
	float m_fVelX;
	float m_fVelY;
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

	tVector2D m_v2OldPos;

	// vector of Emmiters
	std::vector<int> m_vEmitters;

	// pointer to tile manager
	CTileManager *m_pTM;

protected:
	// Object Type
	int m_nType;

};
#endif