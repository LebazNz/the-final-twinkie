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
	CTurret* GetTurret(){return m_pTurret;}
	float	GetHeat(){return m_fHeat;}

	static CPlayer* GetInstance(void);
	static void DeleteInstance(void);

	void SetWeaponAmmo(int nShell, int nArtillery, int nMissile){ m_anWeaponAmmo[0] = nShell; m_anWeaponAmmo[1] = nArtillery; m_anWeaponAmmo[2] = nMissile; }
	void SetMaxWeaponAmmo(int nShell, int nArtillery, int nMissile){ m_anMaxWeaponAmmo[0] = nShell; m_anMaxWeaponAmmo[1] = nArtillery; m_anMaxWeaponAmmo[2] = nMissile; }
	void SetSpecialAmmo(int nAmmoOne, int nAmmoTwo) { m_anSpecialammo[0] = nAmmoOne; m_anSpecialammo[1] = nAmmoTwo; }
	void SetMoney(int nMoney) { m_nMoney = nMoney; }
	void SetName(std::string szName) { m_szName = szName; }
	int GetWeaponAmmoOne(void) const { return m_anWeaponAmmo[0]; }
	int GetWeaponAmmoTwo(void) const { return m_anWeaponAmmo[1]; }
	int GetWeaponAmmoThree(void) const { return m_anWeaponAmmo[2]; }
	int GetMaxWeaponAmmoOne(void) const { return m_anMaxWeaponAmmo[0]; }
	int GetMaxWeaponAmmoTwo(void) const { return m_anMaxWeaponAmmo[1]; }
	int GetMaxWeaponAmmoThree(void) const { return m_anMaxWeaponAmmo[2]; }
	int GetMoney(void) const {return m_nMoney; }

private:

	CPlayer(void);
	~CPlayer(void);
	CPlayer& operator=(CPlayer&);
	CPlayer(CPlayer&);
	int m_nMoney;
	std::string m_szName;
	CSpecial* m_apSpec;
	int m_anWeaponAmmo[3];
	int m_anMaxWeaponAmmo[3];
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

	float m_fHeat;


	static CPlayer* m_pInstance;
	CSGD_DirectInput* m_pDI;
};
#endif

