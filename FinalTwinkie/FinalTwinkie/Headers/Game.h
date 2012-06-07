#ifndef CGAME_H_
#define CGAME_H_

#include <Windows.h>

#include <fmod.h>
#include <fmod.hpp>
#pragma comment(lib, "fmodex_vc.lib")

#include "../GameStates/IGameState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"


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

	// self
	static CGame*			 m_pSelf;

public:
	// sound stuff
	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::Sound* sound;
	FMOD::Sound* my_sound;
	FMOD::Sound* Menu_theme;
	FMOD::Sound* Game_theme;
	FMOD::Channel* channel;
	FMOD::Channel* my_channel;
	bool mute, isPlaying,isTutor;

	
};

#endif
