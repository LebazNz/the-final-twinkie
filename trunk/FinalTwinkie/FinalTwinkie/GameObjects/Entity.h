#ifndef CENTITY_H
#define CENTITY_H

#include "IEntity.h"
#include "../SGD Wrappers/SGD_Math.h"
class CTileManager;

#include <vector>
enum OBJECT_TYPE { OBJ_BASE, OBJ_PLAYER, OBJ_BULLET, OBJ_ENEMY, OBJ_TURRET, OBJ_PICKUP, OBJ_BUILDING, OBJ_MINE, OBJ_TANK, OBJ_TREE, OBJ_FLYTEXT, OBJ_HELP };
enum BULLETYPE { BUL_SHELL, BUL_ROCKET, BUL_ARTILLERY, BUL_MACHINEGUN, BUL_LASER, BUL_FLAME };


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

	virtual void SetType(int nType) {m_nType = nType;}

	virtual void AddRef(void);
	virtual void Release(void);

	CEntity(void);
	virtual ~CEntity(void);

	virtual void TakeDamage(int nDamage);

	virtual float GetPosX(void) {return m_fPosX; }
	virtual float GetPosY(void) {return m_fPosY; }
	virtual float GetVelX(void) {return m_fVelX; }
	virtual float GetVelY(void) {return m_fVelY; }
	virtual int GetWidth(void) { return m_nWidth; }
	virtual int GetHeight(void) { return m_nHeight; }
	virtual int GetColor(void) { return m_nColor; }
	virtual float GetHealth(void) { return m_fHealth; }
	virtual float GetArmor(void) {return m_fArmor;}
	virtual float GetMaxHealth(void) {return m_fMaxHealth;}
	virtual float GetMaxArmor(void) {return m_fMaxArmor;}

	virtual void SetPosX(float fPosX) {m_fPosX = fPosX; }
	virtual void SetPosY(float fPosY) {m_fPosY = fPosY; }
	virtual void SetVelX(float fVelX) {m_fVelX = fVelX; }
	virtual void SetVelY(float fVelY) {m_fVelY = fVelY; }
	virtual void SetWidth(int nWidth) {m_nWidth = nWidth; }
	virtual void SetHeight(int nHeight) {m_nHeight = nHeight; }
	virtual void SetColor(int nColor) {m_nColor = nColor; }
	virtual void SetHealth(float fHealth) { m_fHealth = fHealth; }
	virtual void SetArmor(float fArmor) {m_fArmor=fArmor;}
	virtual void SetMaxHealth(float fHealth) {m_fMaxHealth = fHealth;}
	virtual void SetMaxArmor(float fArmor) { m_fMaxArmor = fArmor; }
	virtual void SetOldPos(tVector2D v2OldPos) { m_v2OldPos = v2OldPos; }
	virtual tVector2D GetOldPos(void) { return m_v2OldPos;}
	virtual void AddEmitter(int nEmitter){ m_vEmitters.push_back(nEmitter);  }
	virtual bool GetInvul(void)const{return m_bInvul;}
	virtual void SetInvul(bool bInv){m_bInvul = bInv;}
	virtual void SetInvulTimer(float fTimer){m_fInvulTimer = fTimer;}
	virtual float GetInvulTimer(void)const{return m_fInvulTimer;}

	virtual void SetStopTimer(float fTimer){m_fStopTimer = fTimer;}
	virtual float GetStopTimer(void){return m_fStopTimer;}
	virtual void SetStop(bool bStop){m_bStop = bStop;}
	virtual bool GetStop(void){return m_bStop;}

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
	//Armor
	float m_fArmor;
	float m_fMaxArmor;
	// Reference Counter
	int m_nRefCount;
	// Invul 
	bool  m_bInvul;
	float m_fInvulTimer;

	tVector2D m_v2OldPos;

	// vector of Emmiters
	std::vector<int> m_vEmitters;

	// pointer to tile manager
	CTileManager *m_pTM;

protected:
	// Object Type
	int m_nType;
	// Stop moving
	float m_fStopTimer;
	bool  m_bStop;
	int	  m_nHPID;
};
#endif