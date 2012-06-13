#pragma once
#include "igamestate.h"
#include "../GameObjects/Player.h"
class StatState :
	public IGameState
{

public:
	static StatState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	void Highlight( DWORD* dwIndex );
	void SelectButtons();
	void Clicked();
	void RenderStats();
	void RenderAchievements();
	void LoadText(void);
private:
	StatState(void);
	StatState(const StatState&);
	StatState& operator=(const StatState&);
	virtual ~StatState(void);


	//Pointers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CPlayer*				m_pPlayer;

	DWORD					m_dwBack;
	DWORD					m_dwNext;

	static StatState*		m_pSelf;

	// IDs
	int m_nBGImageID;
	int m_nButtonImageID;
	int m_nCursor;

	bool m_bStats;

	int m_nClick;
	int m_nButton;
	int m_nPos;

	DWORD m_dwNaziBoss;	
	DWORD m_dwAlienBoss;	
	DWORD m_dwRobotBoss;	
	DWORD m_dwSparta;	
	DWORD m_dwSapperAbsorb;
	DWORD m_dwNukem;	
	DWORD m_dwIamBoss;	
	DWORD m_dwAllUpgrades;

	string m_sStat;
	string m_sScore;
	string m_sShots;
	string m_sNukes; 
	string m_sDamage;
	string m_sMonies;
	string m_sEnemies;
	string m_sSappers;
	string m_sAchieve;
	string m_sNazi;
	string m_sAlien;
	string m_sRobot;
	string m_sSparta;
	string m_sWTF;
	string m_sNukem;
	string m_sPain;
	string m_sOwnAll;
};