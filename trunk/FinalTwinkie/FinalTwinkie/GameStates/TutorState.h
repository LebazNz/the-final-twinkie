#ifndef CTUTORSTATE_H_
#define CTUTORSTATE_H_

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

class CTutorState :  public IGameState
{
public:

	static CTutorState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);

	bool GetPaused(void)const {return m_bPaused;}

	void SetGameOver(bool g) { m_bGameOver = g;}
	void SetWinner(bool w) { m_bWinner = w;}
	void IncrementBox(void);
	
	static void MessageProc(CMessage* pMsg);

	int m_nEnemyCount;

private:
	CTutorState(void);
	CTutorState(const CTutorState&);
	CTutorState& operator=(const CTutorState&);
	virtual ~CTutorState(void);

	void LoadWords(void);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CObjectManager*			m_pOM;
	CFactory*				m_pOF;
	CParticleManager*		m_PM;
	CMessageSystem*			m_pMS;
	CTileManager*			m_pTile;
	CAnimationManager*		m_AM;
	CEventSystem*			m_pES;
	CGUI*					m_pGUI;
	CSGD_XAudio2*			m_pAudio;
	
	
	static CTutorState*	m_pSelf;

	vector<CEmitter*>		m_pEmitters;
	CEntity*				m_pPlayer;
	CEntity*				m_pEnemy;
	CEntity*				m_pTurret;

	void TurnSoundOff(void);
	bool SoundOff;

	//IMAGE IDS
	int m_anBulletSounds[6];
	int m_anSoldierSounds[9];
	int m_nMineSound;
	int m_nSappSound;
	int m_nGameMusic;
	int m_nNukeSound;
	int m_nDeadBullet;
	int m_anBulletImageIDs[5];
	int m_anEnemyIDs[16];
	int m_anSupportIDs[3];
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
	int	m_nButton;
	int	m_nClick;



	int m_nBox;
	string m_asInfo[12];
	string m_sObj;
	string m_sPaused;
	string m_sResume;
	string m_sOptions;
	string m_sExit;
	int m_nCursor;
	bool m_bActivePad;
	bool m_bWordBox;
	int m_nBoxIndex;
	float m_fWordTimer;

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
};

#endif
