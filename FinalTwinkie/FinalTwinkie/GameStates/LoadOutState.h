#pragma once
#include "igamestate.h"
#include "../GameObjects/Player.h"
#include "../PickUps and Specials/Special.h"
#include "../Particle/ParticleManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

#include <vector>
using std::vector;

class CLoadOutState :
	public IGameState
{
public:
	static CLoadOutState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	void LoadText();
private:
	CLoadOutState(void);
	CLoadOutState(const CLoadOutState&);
	CLoadOutState& operator=(const CLoadOutState&);
	virtual ~CLoadOutState(void);
	
	//Pointers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CPlayer*				m_pPlayer;
	CParticleManager*		m_PM;
	CSGD_XAudio2*			m_pAudio;

	static CLoadOutState*	m_pSelf;

	int m_nButtonImageID;
	int m_nBGID;
	int	m_nPosition;

	int m_nMouseX;
	int m_nMouseY;

	int m_nCursor;

	int m_nShellCount;
	int m_nMissileCount;
	int m_nArtilleryCount;
	int m_nShellMaxCount;
	int m_nMissileMaxCount;
	int m_nArtilleryMaxCount;
	bool m_bMissile;
	bool m_bArtillery;
	bool m_bLaser;
	bool m_bFlame;
	bool m_bNuke;
	bool m_bSmoke;
	bool m_bEMP;
	bool m_bAirStirke;
	bool m_bRF;
	int m_nSecondAmmo;
	int m_nSpecialCount;
	int m_nSpecialPos1;
	int m_nSpecialPos2;
	vector<int> m_vSpCount;
	bool m_bUseMachineGun;
	bool m_bUseLaser;
	bool m_bUseFlame;
	int m_nButton;
	int m_nClick;

	DWORD m_dShellMin;
	DWORD m_dShellMax;
	DWORD m_dRocketMin;
	DWORD m_dRocketMax;
	DWORD m_dArtilleryMin;
	DWORD m_dArtilleryMax;
	DWORD m_dSPOneMin;
	DWORD m_dSPOneMax;
	DWORD m_dSPTwoMin;
	DWORD m_dSPTwoMax;
	DWORD m_dBack;
	DWORD m_dContinue;

	CSpecial* m_pSpecialOne;
	CSpecial* m_pSpecialTwo;

	string m_sLoad;
	string m_sCannon;
	string m_sShell;
	string m_sRocket;
	string m_sArtillery;
	string m_sSecond;
	string m_sMachine;
	string m_sLaser;
	string m_sFlame;
	string m_sSpecOne;
	string m_sSpecTwo;
	string m_sNone;
	string m_sSmoke;
	string m_sEMP;
	string m_sNuke;
	string m_sReinforce;
	string m_sAirStrike;
	string m_sBack;
	string m_sContinue;
};

