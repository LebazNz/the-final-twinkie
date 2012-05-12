#include "Game.h"

#include "MainMenuState.h"
#include "GamePlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"

CGame* CGame::m_pSelf = nullptr;

CGame* CGame::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGame;
	return m_pSelf;
}

CGame::CGame(void)
{
	m_nScreenWidth = -1;
	m_nScreenHeight = -1;
	m_bWindowed = true;	
	
	m_dwTime = 0;	
	
	m_pCurState = nullptr;	
	
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
}

CGame::~CGame(void)
{
}

void CGame::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}

}

void CGame::ChangeState(IGameState* pNewState)
{
	// Check old state and exit
	if(m_pCurState != nullptr)
		m_pCurState->Exit();

	m_pCurState = pNewState;

	// Check new state and enter
	if(m_pCurState != nullptr)
		m_pCurState->Enter();
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bWindowed)
{
	// Gain access to wrapper
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	// Init the wrappers
	m_pD3D->InitDirect3D( hWnd, nScreenWidth, nScreenHeight, bWindowed, true );
	m_pDI->InitDirectInput( hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS);
	m_pTM->InitTextureManager( m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite() );
	
	// Set screen info
	m_nScreenWidth	= nScreenWidth;
	m_nScreenHeight	= nScreenHeight;
	m_bWindowed		= bWindowed;

	// Start the game in Main menu
	ChangeState(CMainMenuState::GetInstance());

	// Set game time
	m_dwTime = GetTickCount();

	// Set up sound
	mute = isPlaying = FALSE;
	result = FMOD::System_Create(&system);
	system->setOutput(FMOD_OUTPUTTYPE_DSOUND);
	system->init(200,FMOD_INIT_NORMAL,0);
	result = system->createSound("Glow.mp3",FMOD_LOOP_NORMAL,NULL,&sound);
	result = system->playSound(FMOD_CHANNEL_FREE,sound,false,&channel);
	
}

void CGame::Shutdown(void)
{
	CMainMenuState::GetInstance()->DeleteInstance();
	CGamePlayState::GetInstance()->DeleteInstance();
	COptionsState::GetInstance()->DeleteInstance();
	CCreditsState::GetInstance()->DeleteInstance();
}

bool CGame::Main(void)
{
	//Check
	if(m_pCurState == nullptr)
		return false;

	if(Input() == false)
		return false;

	Update();
	Render();

	return true;
}

bool CGame::Input(void)
{
	// Refresh input
	m_pDI->ReadDevices();

	if(m_pDI->KeyDown(DIK_LMENU) && m_pDI->KeyPressed(DIK_RETURN) || m_pDI->KeyDown(DIK_RMENU) && m_pDI->KeyPressed(DIK_RETURN))
	{
		m_bWindowed = !m_bWindowed;
		if(!m_bWindowed)
			m_pD3D->ChangeDisplayParam(m_nScreenWidth,m_nScreenHeight,m_bWindowed);
		else
			m_pD3D->ChangeDisplayParam(m_nScreenWidth,m_nScreenHeight,m_bWindowed);
		m_pDI->ReadDevices();
	}

	// return to the current state
	return m_pCurState->Input();
}

void CGame::Update(void)
{
	// Calculate elapsed time
	DWORD newTime = GetTickCount();
	float fElapsedTime = (newTime - m_dwTime)/1000.0f;
	m_dwTime = newTime;

	if(fElapsedTime > 0.125f)
		fElapsedTime = 0.125f;

	// let current state handle the update
	m_pCurState->Update(fElapsedTime);
}

void CGame::Render(void)
{
	// Clear the background
	m_pD3D->Clear( 0, 0, 255 );

	// Start D3D rendering
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();
	
	// Let the current state render
	m_pCurState->Render();
	
	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();

	m_pD3D->Present();
}
