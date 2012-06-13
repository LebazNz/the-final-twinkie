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
	bool		GetMoveRight() const { return m_bMoveRight; }
	void		SetMoveRight(bool val) { m_bMoveRight = val; }
	bool		GetMoveLeft() const { return m_bMoveLeft; }
	void		SetMoveLeft(bool val) { m_bMoveLeft = val; }
	bool		GetMoveUp() const { return m_bMoveUp; }
	void		SetMoveUp(bool val) { m_bMoveUp = val; }
	bool		GetMoveDown() const { return m_bMoveDown; }
	void		SetMoveDown(bool val) { m_bMoveDown = val; }
	bool		GetIsMoving() const { return m_bIsMoving; }
	void		SetIsMoving(bool val) { m_bIsMoving = val; }

	void		SetTurret(CTurret* pTurret){m_pTurret=pTurret;}
	void		SetRotation(float fRotate) {m_fRotation=fRotate;}
	float		GetRotation() const { return m_fRotation;}
	CTurret*	GetTurret(){return m_pTurret;}
	float		GetHeat(){return m_fHeat;}

	static CPlayer*		GetInstance(void);
	static void			DeleteInstance(void);

	void SetWeaponAmmo(int nShell, int nArtillery, int nMissile){ m_anWeaponAmmo[0] = nShell; m_anWeaponAmmo[1] = nArtillery; m_anWeaponAmmo[2] = nMissile; }
	void SetMaxWeaponAmmo(int nShell, int nArtillery, int nMissile){ m_anMaxWeaponAmmo[0] = nShell; m_anMaxWeaponAmmo[1] = nArtillery; m_anMaxWeaponAmmo[2] = nMissile; }
	void SetSpecialAmmo(int nAmmoOne, int nAmmoTwo) { m_anSpecialammo[0] = nAmmoOne; m_anSpecialammo[1] = nAmmoTwo; }
	void SetMoney(int nMoney) { m_nMoney = nMoney; }
	void SetName(char* szName) { m_szName = szName; }
	std::string GetUserName(void){return m_szName;}
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
	float GetDoubleDamageTimer(void){return m_fDamageTime;}
	bool GetInfAmmo(void) {return m_bInfAmmo; }
	void SetInfAmmo(bool bAmmo) {m_bInfAmmo = bAmmo;}
	void SetInfoAmmoTimer(float fTimer){m_fInfAmmoTimer = fTimer; }
	float GetInfAmmoTimer(void){return m_fInfAmmoTimer;}
	float GetNoReload(){return m_fNoReloadTimer;}
	void SetSpecial1(CSpecial* pSpecial){ m_pSpec1 = pSpecial; m_pSelectedSpec=m_pSpec1; m_pSelectedSpecAmmo=0;}
	void SetSpecial2(CSpecial* pSpecial){ m_pSpec2 = pSpecial; }

	

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

	CSpecial* GetSpecial1(void) {return m_pSpec1;}
	CSpecial* GetSpecial2(void) {return m_pSpec2;}
	CSpecial* GetSelSpec(void)	{return m_pSelectedSpec;}
	int GetSpecial1Ammo(void) {return  m_anSpecialammo[0];}
	int GetSpecial2Ammo(void) {return  m_anSpecialammo[1];}
	void SetSpecial1Ammo(int ammo) {m_anSpecialammo[0]=ammo;}
	void SetSpecial2Ammo(int ammo) {m_anSpecialammo[1]=ammo;}

	int		GetShotsFired() const { return m_nShotsFired; }
	void	SetShotsFired(int val) { m_nShotsFired = val; }
	int		GetDamageTaken() const { return m_nDamageTaken; }
	void	SetDamageTaken(int val) { m_nDamageTaken = val; }
	int		GetTotalMoneyEarned() const { return m_nTotalMoneyEarned; }
	void	SetTotalMoneyEarned(int val) { m_nTotalMoneyEarned = val; }
	int		GetUnitsKilled() const { return m_nUnitsKilled; }
	void	SetUnitsKilled(int val) { m_nUnitsKilled = val; }
	int		GetSappersExploded() const { return m_nSappersExploded; }
	void	SetSappersExploded(int val) { m_nSappersExploded = val; }
	int		GetNukesBlasted() const { return m_nNukesBlasted; }
	void	SetNukesBlasted(int val) { m_nNukesBlasted = val; }
	int		GetScore() const { return m_nScore; }
	void	SetScore(int val) { m_nScore = val; }

	bool	GetNaziBoss() const { return m_bNaziBoss; }
	void	SetNaziBoss(bool val) { m_bNaziBoss = val; }
	bool	GetAlienBoss() const { return m_bAlienBoss; }
	void	SetAlienBoss(bool val) { m_bAlienBoss = val; }
	bool	GetRobotBoss() const { return m_bRobotBoss; }
	void	SetRobotBoss(bool val) { m_bRobotBoss = val; }
	bool	GetSparta() const { return m_bSparta; }
	void	SetSparta(bool val) { m_bSparta = val; }
	bool	GetSapperAbsorb() const { return m_bSapperAbsorb; }
	void	SetSapperAbsorb(bool val) { m_bSapperAbsorb = val; }
	bool	GetNukem() const { return m_bNukem; }
	void	SetNukem(bool val) { m_bNukem = val; }
	bool	GetIamBoss() const { return m_bIamBoss; }
	void	SetIamBoss(bool val) { m_bIamBoss = val; }
	bool	GetAllUpgrades() const { return m_bAllUpgrades; }
	void	SetAllUpgrades(bool val) { m_bAllUpgrades = val; }


	void SetSecondType(int nType){m_nSecondType=nType;}
	bool	GetRobotBossState() const { return m_bRobotBossState; }
	void	SetRobotBossState(bool val) { m_bRobotBossState = val; }
	
	int GetSecondType(void){return m_nSecondType;}
	void SetEmitterRight(CEmitter* EM){m_pTracksRight=EM;}
	void SetEmitterLeft(CEmitter* EM){m_pTracksLeft=EM;}
	void SetGunSel(int Sel) {m_nGunSel=Sel;}

	void SlowVel(float time, float vel);
	void SetFireSound(int s) {m_nFireSound = s;}
	void SetNukeSound(int n) { m_nNukeSound = n;}

	void SetLevel(int nLevel){m_nLevel = nLevel;}
	int GetLevel(void){return m_nLevel;}

private:
	CPlayer(void);
	~CPlayer(void);
	CPlayer& operator=(CPlayer&);
	CPlayer(CPlayer&);
	int m_nMoney;
	std::string m_szName;
	CSpecial* m_pSpec1;
	CSpecial* m_pSpec2;
	CSpecial* m_pSelectedSpec;
	int m_pSelectedSpecAmmo;
	int m_anWeaponAmmo[3];
	int m_anMaxWeaponAmmo[3];
	int m_anSpecialammo[2];
	
	CEmitter* m_pTracksLeft;
	CEmitter* m_pTracksRight;
	CTurret* m_pTurret;
	float m_fRotation;
	float m_fRotationRate;

	float m_fRotationHeight;
	float m_fRotationWidth;

	tVector2D m_v2OldPos;

	// BOOLS FOR THE CAMERA RYAN IS MAKING DO NOT TOUCH OR ELSE 
	// PANCKAES WILL RAIN HELLFIRE AND BUTTER ONTO YOUR CHILDREN
	bool m_bIsMoving;
	bool m_bMoveRight;
	bool m_bMoveLeft;
	bool m_bMoveUp;
	bool m_bMoveDown;
	bool m_bOverheat;
	float m_fOverheatTimer;

	bool m_bSlowDown;
	float m_fSlowTimer;

	float m_fFireRate;

	float m_fHeat;

	bool SlowFlame;

	// STUFF FOR THE SHOP STATE!
	// IF THIS IS CHANGED ORE REMOVED
	// PEOPLE WILL SUFFER
	// PEOPLE WILL CRY
	// BECAUSE KITTENS WILL ATTACK YOU
	// and eat your cookies >.>
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
	int		m_nGunSel;
	bool m_bRobotBossState;
	float m_fPurchaseLevel;

	bool m_bRocketAccess;
	bool m_bLaserAccess;
	bool m_bNukeAccess;
	bool m_bEMPAccess;
	bool m_bArtilleryAccess;
	bool m_bFlamerAccess;
	bool m_bAirStrikeAccess;
	bool m_bSmokeBombAccess;

	int m_nFireSound;
	int m_nNukeSound;
	bool m_bSoundPlaying;

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
	// Player stat tracks

	int m_nNukesBlasted;
	int m_nScore;
	int m_nShotsFired;
	int m_nDamageTaken;
	int m_nTotalMoneyEarned;
	int m_nUnitsKilled;
	int m_nSappersExploded; 
	
	// Achievable
	// Defeat the Nazi Boss
	bool m_bNaziBoss;	//-------// Dat Reich
	// Defeat the Alien Boss
	bool m_bAlienBoss;	//-------// All your base are belong to me
	// Defeat Anthony's mom
	bool m_bRobotBoss;	// Greased
	// Kill 300 enemies;
	bool m_bSparta;	//--------// This is not Sparta!
	// Absorb 50 sappers
	bool m_bSapperAbsorb;	//--------// WTF is damage?
	// Kill 10 enemies with one Nuke
	bool m_bNukem;	// Nuke Dukem;
	// Purchase a level 5 upgrade
	bool m_bIamBoss;	// Max Pain;
	// Purchase all Upgrades
	bool m_bAllUpgrades;	// God mode
	
	int m_nLevel;

};
#endif

