#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Turret.h"
#include "../Particle/Emitter.h"
#include <vector>
#include "../SGD Wrappers/CSGD_DirectInput.h"
class CSpecial;

class CPlayer:public CEntity
{
public:
	virtual void Update(float);
	virtual void Render(void);
	virtual RECT GetRect(void);
	virtual int GetType(void) { return m_nType; }
	virtual bool CheckCollision(IEntity*);
	virtual tVector2D GetOldPos(void) { return m_v2OldPos;}
	CPlayer(void);
	~CPlayer(void);


	// BOOLS FOR THE CAMERA RYAN IS MAKING DO NOT TOUCH OR ELSE PANCKAES WILL RAIN HELLFIRE AND BUTTER ONTO YOUR CHILDREN
	bool	GetMoveRight() const { return m_bMoveRight; }
	void	SetMoveRight(bool val) { m_bMoveRight = val; }
	bool	GetMoveLeft() const { return m_bMoveLeft; }
	void	SetMoveLeft(bool val) { m_bMoveLeft = val; }
	bool	GetMoveUp() const { return m_bMoveUp; }
	void	SetMoveUp(bool val) { m_bMoveUp = val; }
	bool	GetMoveDown() const { return m_bMoveDown; }
	void	SetMoveDown(bool val) { m_bMoveDown = val; }
	bool	GetIsMoving() const { return m_bIsMoving; }
	void	SetIsMoving(bool val) { m_bIsMoving = val; }

	void	SetTurret(CTurret* pTurret){m_pTurret=pTurret;}
	void	SetRotation(float fRotate) {m_fRotation=fRotate;}
	float	GetRotation() const { return m_fRotation;}

private:
	int m_nMoney;
	std::string m_szName;
	CSpecial* m_apSpec;
	int m_anWeaponAmmo[3];
	int m_anSpecialammo[2];
	CEmitter* m_pTracks;
	CTurret* m_pTurret;
	float m_fRotation;
	float m_fRotationRate;

	float m_fRotationHeight;
	float m_fRotationWidth;

	tVector2D m_v2OldPos;

	// BOOLS FOR THE CAMERA RYAN IS MAKING DO NOT TOUCH OR ELSE PANCKAES WILL RAIN HELLFIRE AND BUTTER ONTO YOUR CHILDREN
	bool m_bIsMoving;
	bool m_bMoveRight;
	bool m_bMoveLeft;
	bool m_bMoveUp;
	bool m_bMoveDown;

	float m_fFireRate;



	CSGD_DirectInput* m_pDI;
};
#endif

