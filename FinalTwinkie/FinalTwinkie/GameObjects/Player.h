#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Turret.h"
#include "../Particle/Emitter.h"
#include <vector>
#include "../SGD Wrappers/CSGD_DirectInput.h"
class CSpecial;

enum SecondType {MACHINEGUN, LAZER, FLAME};
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
	int GetWeaponAmmoShell(void) const { return m_anWeaponAmmo[0]; }
	int GetWeaponAmmoArtillery(void) const { return m_anWeaponAmmo[1]; }
	int GetWeaponAmmoMissile(void) const { return m_anWeaponAmmo[2]; }
	int GetMaxWeaponAmmoShell(void) const { return m_anMaxWeaponAmmo[0]; }
	int GetMaxWeaponAmmoArtillery(void) const { return m_anMaxWeaponAmmo[1]; }
	int GetMaxWeaponAmmoMissile(void) const { return m_anMaxWeaponAmmo[2]; }
	int GetMoney(void) const {return m_nMoney; }
	void SetNoReloadTimer(float fNoReload) { m_fNoReloadTimer = fNoReload; }
	bool GetDoubleDamage(void) {return m_bDoubleDamage; }
	void SetDoubleDamage(bool bDD) { m_bDoubleDamage = bDD; }
	void SetDamageTimer(float fTimer) { m_fDamageTime = fTimer; }
	bool GetInfAmmo(void) {return m_bInfAmmo; }
	void SetInfAmmo(bool bAmmo) {m_bInfAmmo = bAmmo;}
	void SetInfoAmmoTimer(float fTimer){m_fInfAmmoTimer = fTimer; }
	float GetNoReload(){return m_fNoReloadTimer;}
	void SetSpecial(CSpecial* pSpecial){ m_apSpec = pSpecial; }


	float	GetDamageMod() const { return m_fDamageMod; }
	void	SetDamageMod(float val) { m_fDamageMod = val; }
	float	GetAmmoMod() const { return m_fAmmoMod; }
	void	SetAmmoMod(float val) { m_fAmmoMod = val; }
	float	GetHealthMod() const { return m_fHealthMod; }
	void	SetHealthMod(float val) { m_fHealthMod = val; }
	float	GetArmorMod() const { return m_fArmorMod; }
	void	SetArmorMod(float val) { m_fArmorMod = val; }
	float	GetSpeedMod() const { return m_fSpeedMod; }
	void	SetSpeedMod(float val) { m_fSpeedMod = val; }
	float	GetHeatModifier() const { return m_fHeatModifier; }
	void	SetHeatModifier(float val) { m_fHeatModifier = val; }
	float	GetPurchaseLevel() const { return m_fPurchaseLevel; }
	void	SetPurchaseLevel(float val) { m_fPurchaseLevel = val; }

	int		GetHealthLevel() { return m_nHealthLevel; }
	void	SetHealthLevel(int rhs) { m_nHealthLevel = rhs; }
	int		GetDamageLevel() { return m_nDamageLevel; }
	void	SetDamageLevel(int rhs) { m_nDamageLevel = rhs; } 
	int		GetAmmoLevel() { return m_nAmmoLevel; }
	void	SetAmmoLevel(int rhs) { m_nAmmoLevel = rhs; }
	int		GetHeatLevel() { return m_nHeatLevel; }
	void	SetHeatLevel(int rhs) { m_nHeatLevel = rhs; }
	int		GetArmorLevel() { return m_nArmorLevel; }
	void	SetArmorLevel(int rhs) { m_nArmorLevel = rhs; }
	int		GetSpeedLevel() { return m_nSpeedLevel; }
	void	SetSpeedLevel(int rhs) { m_nSpeedLevel = rhs; }

	bool	GetRocketAccess() { return  m_bRocketAccess; }
	void	SetRocketAccess(bool rhs) { m_bRocketAccess = rhs; } 
	bool	GetLaserAccess() { return  m_bLaserAccess; }
	void	SetLaserAccess(bool rhs) { m_bLaserAccess = rhs; } 
	bool	GetNukeAccess() { return  m_bNukeAccess; }
	void	SetNukeAccess(bool rhs) { m_bNukeAccess = rhs; } 
	bool	GetEMPAccess() { return  m_bEMPAccess; }
	void	SetEMPAccess(bool rhs) { m_bEMPAccess = rhs; } 
	bool	GetArtilleryAccess() { return  m_bArtilleryAccess; }
	void	SetArtilleryAccess(bool rhs) { m_bArtilleryAccess = rhs; } 
	bool	GetFlamerAccess() { return  m_bFlamerAccess; }
	void	SetFlamerAccess(bool rhs) { m_bFlamerAccess = rhs; } 
	bool	GetAirStrikeAccess() { return  m_bAirStrikeAccess; }
	void	SetAirStrikeAccess(bool rhs) { m_bAirStrikeAccess = rhs; } 
	bool	GetSmokeBombAccess() { return  m_bSmokeBombAccess; }
	void	SetSmokeBombAccess(bool rhs) { m_bSmokeBombAccess = rhs; } 

	CSpecial* GetSpecial(void) {return m_apSpec;} 
	int GetSpecial1Ammo(void) {return  m_anSpecialammo[0];}
	int GetSpecial2Ammo(void) {return  m_anSpecialammo[1];}
	void SetSpecial1Ammo(int ammo) {m_anSpecialammo[0]=ammo;}
	void SetSpecial2Ammo(int ammo) {m_anSpecialammo[1]=ammo;}

	void SetSecondType(int nType){m_nSecondType=nType;}
	int GetSecondType(void){return m_nSecondType;}

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
	bool m_bOverheat;
	float m_fOverheatTimer;

	float m_fFireRate;

	float m_fHeat;

	bool SlowFlame;

	// STUFF FOR THE SHOP STATE!
	// IF THIS IS CHANGED ORE REMOVED
	// PEOPLE WILL SUFFER
	// PEOPLE WILL CRY
	// BECAUSE KITTENS WILL ATTACK YOU
	float	m_fHeatModifier;
	int		m_nHeatLevel;
	float	m_fDamageMod;
	int		m_nDamageLevel;
	float	m_fAmmoMod;
	int		m_nAmmoLevel;
	float	m_fHealthMod;
	int		m_nHealthLevel;
	float	m_fArmorMod;
	int		m_nArmorLevel;
	float	m_fSpeedMod;
	int		m_nSpeedLevel;
	
	float m_fPurchaseLevel;

	bool m_bRocketAccess;
	bool m_bLaserAccess;
	bool m_bNukeAccess;
	bool m_bEMPAccess;
	bool m_bArtilleryAccess;
	bool m_bFlamerAccess;
	bool m_bAirStrikeAccess;
	bool m_bSmokeBombAccess;


	static CPlayer* m_pInstance;
	CSGD_DirectInput* m_pDI;

	float m_fFireTimer;
	float m_fTime;
	float m_fNoReloadTimer;
	bool m_bDoubleDamage;
	float m_fDamageTime;
	bool  m_bInfAmmo;
	float m_fInfAmmoTimer;

	int m_nSecondType;

};
#endif

