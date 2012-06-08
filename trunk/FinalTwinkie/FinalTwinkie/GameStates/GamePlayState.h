#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

#include "IGameState.h"
#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../Event and Messages/Message.h"

#include <string>

class CParticleManager;
class CObjectManager;
//class CObjectFactory;
class CEntity;
class CEmitter;
class CTileManager;
class CAnimationManager;
class CMessageSystem;
class CEventSystem;
class CGUI;


typedef CObjectFactory< std::string , CEntity> CFactory;

class CGamePlayState : public IGameState
{
public:
	static CGamePlayState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	void LoadText(void);

	bool GetPaused(void)const {return m_bPaused;}

	void SetGameOver(bool g) { m_bGameOver = g;}
	void SetWinner(bool w) { m_bWinner = w;}
	
	static void MessageProc(CMessage* pMsg);

	void SetSavedGame(Data gameData);
	int m_nEnemyCount;

private:
	CGamePlayState(void);
	CGamePlayState(const CGamePlayState&);
	CGamePlayState& operator=(const CGamePlayState&);
	virtual ~CGamePlayState(void);

	void SaveGame(const char* szFileName);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CObjectManager*			m_pOM;
public:
	CFactory*				m_pOF;
private:
	CParticleManager*		m_PM;
	CMessageSystem*			m_pMS;
	CTileManager*			m_pTile;
	CAnimationManager*		m_AM;
	CEventSystem*			m_pES;
	CGUI*					m_pGUI;
	
	
	static CGamePlayState*	m_pSelf;

	vector<CEmitter*>		m_pEmitters;
	CEntity*				m_pPlayer;
	CEntity*				m_pEnemy;
	CEntity*				m_pTurret;


	//IMAGE IDS
	int m_anBulletImageIDs[5];
	int m_anEnemyIDs[16];
	int m_nPlayerID;
	int m_nPlayerTurretID;
	int m_nBackGround;
	int m_nPosition;
	bool m_bPaused;
	bool m_bGameOver;
	bool m_bWinner;
	float gameEndTimer;
	int WinnerID;
	int GameOverID;
	int FXEnemy_Tails;
	int FXSapper_Explosion;
	int FXFlame;
	int FXBuildingFlame;
	int FXNuke;
	int FXTreads;
	int m_nMine;
	int FXSmoke;
	int m_nTree;
	int m_nDeadTree;
	int m_nBarricade;
	int m_nDeadBarr;
	int FXEnemyOnFire;
	int FXAirStrike;

	int m_nCursor;

	Data m_dGameData;

	int m_nMouseX;
	int m_nMouseY;
	int	m_nButtonImageID;

	int m_nPickupHealthID;
	int m_nPickupAmmoID;
	int m_nPickupArmorID;
	int m_nPickupDoubleDID;
	int m_nPickupNoReloadID;
	int m_nPickupInvuID;
	int m_nPickupInfAmmoID;
	int m_nPickupMoneyID;

	IDirect3DTexture9* MiniMap;

	int m_nLevel;

	string m_sPaused;
	string m_sResume;
	string m_sOptions;
	string m_sExit;
};

#endif
