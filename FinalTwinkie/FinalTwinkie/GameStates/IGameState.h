#ifndef IGAMESTATE_H_
#define IGAMESTATE_H_

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/BitmapFont.h"

struct Data
{
	char szName[32];
	int nLevel;
	int nShellAmmo;
	int nMissileAmmo;
	int nArtilleryAmmo;
	int nMoney;
	int nHp;
	int nArmor;
	int nAmmo;
	int nSpeed;
	int bShell;
	int bMissile;
	int bArtillery;
	int bAirStrike;
	int bEMP;
	int bNuke;
	int bReinforce;
	int bSmoke;
	int nLaser;
	int nMachineGun;

	char szFileName[32];

	// shop stuff
	float	fHeatModifier;
	int		nHeatLevel;
	float	fDamageMod;
	int		nDamageLevel;
	float	fAmmoMod;
	int		nAmmoLevel;
	float	fHealthMod;
	int		nHealthLevel;
	float	fArmorMod;
	int		nArmorLevel;
	float	fSpeedMod;
	int		nSpeedLevel;

	float	fPurchaseLevel;


	int		nScore;
	//int		bRocketAccess;
	//int		bLaserAccess;
	//int		bNukeAccess;
	//int		bEMPAccess;
	//int		bArtilleryAccess;
	//int		bFlamerAccess;
	//int		bAirStrikeAccess;
	//int		bSmokeBombAccess;


	
};

class IGameState
{
public:
	virtual ~IGameState(void)
	{	/*DO NOTHING*/		}

	virtual void Enter(void) = 0;
	virtual void Exit(void)	= 0;
	virtual bool Input(void) = 0;
	virtual void Update(float fDt) = 0;
	virtual void Render(void) = 0;

};



#endif