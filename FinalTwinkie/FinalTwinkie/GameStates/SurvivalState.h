#pragma once
#include "igamestate.h"

#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../Event and Messages/Message.h"
#include "../source/Wave.h"
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
class CSurvivalState :
	public IGameState
{
public:
	static CSurvivalState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	bool GetPaused(void)const {return m_bPaused;}
	bool LoadWave(const char* szFileName, int nGamedata);
	static void MessageProc(CMessage* pMsg);
	void LoadText(void);

	int		GetNumUnits() { return m_nNumUnits; }
	void	SetNumUnits(int rhs) { m_nNumUnits = rhs; }
	void	GenerateWave();
private:
	CSurvivalState(void);
	virtual ~CSurvivalState(void);
	CSurvivalState& operator=(const CSurvivalState&);
	CSurvivalState(const CSurvivalState&);

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

	static CSurvivalState*	m_pSelf;
	vector<CWave*>			m_vWave;
	vector<CEmitter*>		m_pEmitters;
	CEntity*				m_pPlayer;
	CEntity*				m_pEnemy;
	CEntity*				m_pTurret;

	int m_anBulletImageIDs[4];
	int m_anEnemyIDs[16];
	int m_nPlayerID;
	int m_nPlayerTurretID;
	int m_nBackGround;
	int m_nPosition;
	bool m_bPaused;

	int FXEnemy_Tails;
	int FXSapper_Explosion;
	int FXFlame;
	int FXBuildingFlame;
	int FXNuke;
	int FXTreads;
	int FXSmoke;
	int FXEnemyOnFire;

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
	int	m_nButton;
	int	m_nClick;

	IDirect3DTexture9* MiniMap;

	int m_nNumUnits;
	int m_nWavesRemaining;
	int m_nCurrWave;
	vector<RECT*> m_vRECTS;
	


	string m_sWave;
	string m_sPaused;
	string m_sResume;
	string m_sOptions;
	string m_sExit;
};

