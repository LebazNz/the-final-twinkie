#ifndef CGAME_H_
#define CGAME_H_

#include <Windows.h>

#include "../GameStates/IGameState.h"
#include "../GameStates/MainMenuState.h"
#include "../GameStates/GamePlayState.h"
#include "../GameStates/CreditsState.h"
#include "../GameStates/OptionsState.h"
#include "../GameStates/LoadGameState.h"
#include "../ObjectManager and Factory/ObjectFactory.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../Headers/BitmapFont.h"
#include "../GameStates/StartState.h"
#include "../GameStates/GetNameState.h"
#include "../GameStates/LoadOutState.h"
#include "../GameStates/ShopState.h"
#include "../GameStates/StatState.h"
#include "../GameStates/SurvivalHS.h"
#include "../GameStates/SurvivalState.h"
#include "../GameStates/TutorState.h"
#include "../GameObjects/Player.h"
#include <iostream>
using namespace std;

#define ARCADE 0

class CGame
{
public:
	static CGame* GetInstance(void);
	static void DeleteInstance(void);
	void ChangeState(IGameState* pNewState);
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int ScreenHeight, bool bWindowed);
	void Shutdown(void);
	bool Main(void);

	int GetWidth(void) const { return m_nScreenWidth; }
	int GetHeight(void) const { return m_nScreenHeight; }
	bool IsWindowed(void) const { return m_bWindowed; }
	void SetIsWindowded(bool isWindowed) { m_bWindowed = isWindowed; }
	IGameState* GetCurState(void){return m_pCurState;}

	HWND GethWnd() const { return m_hWnd; }
	void SethWnd(HWND val) { m_hWnd = val; }
private:
	CGame(void);
	CGame(const CGame&);
	CGame& operator=(const CGame&);
	~CGame(void);

	bool Input(void);
	void Update(void);
	void Render(void);

	// Screen Info
	int						 m_nScreenWidth;
	int						 m_nScreenHeight;
	bool					 m_bWindowed;

	// Game Time
	DWORD					 m_dwTime;
	
	// GameState
	IGameState*				 m_pCurState;

	// Wrappers
	CSGD_Direct3D*			 m_pD3D;
	CSGD_DirectInput*		 m_pDI;
	CSGD_TextureManager*	 m_pTM;
	CSGD_XAudio2*			 m_pAudio;

	CMainMenuState*		m_pMenu;
	CGamePlayState*		m_pGame;
	CCreditsState*		m_Credit;
	COptionsState*		m_Options;
	CLoadGameState*		m_LoadGame;
	CMessageSystem*		m_Message;
	CEventSystem*		m_Event;
	CBitmapFont*		m_pFont;
	CStartState*		m_pStart;
	CGetNameState*		m_pGetName;
	CLoadOutState*		m_pLoadOut;
	CShopState*			m_pShop;
	StatState*			m_pStat;
	CSurvivalHS*		m_pSurvivalHS;
	CSurvivalState*		m_pSurvival;
	CTutorState*		m_pTutor;
	CPlayer*			m_pPlayer;

	// self
	static CGame*			 m_pSelf;

	// Sound
	
	// Other
	HWND m_hWnd;
	
public:

	bool mute, isPlaying,isTutor;

	
};

#endif
