#include "../Headers/Game.h"

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

	if(CMainMenuState::GetInstance()->LoadOptions("options.txt"))
		m_bWindowed = CMainMenuState::GetInstance()->GetWindowed();
	else
		m_bWindowed = true;
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
	m_pD3D->InitDirect3D( hWnd, nScreenWidth, nScreenHeight, m_bWindowed, true );
	m_pDI->InitDirectInput( hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS, DI_MOUSE);
	m_pTM->InitTextureManager( m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite() );
	
	// Set screen info
	m_nScreenWidth	= nScreenWidth;
	m_nScreenHeight	= nScreenHeight;
	//m_bWindowed		= bWindowed;

	// Start the game in Main menu
	ChangeState(CStartState::GetInstance());

	// Set game time
	m_dwTime = GetTickCount();

	// Set up sound
	CMainMenuState::GetInstance()->LoadOptions("options.txt");
	mute = isPlaying = FALSE;
	result = FMOD::System_Create(&system);
	system->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
	system->init(2000,FMOD_INIT_NORMAL,NULL);
	result = system->createSound("resource/sound/Exciting Trailer2.wav",FMOD_LOOP_OFF,NULL,&my_sound);
	result = system->createSound("resource/sound/explode.wav",FMOD_LOOP_OFF,NULL,&sound);
	result = system->createSound("resource/sound/Junkyard Tribe.mp3", FMOD_LOOP_NORMAL, NULL, &Menu_theme);
	result = system->createSound("resource/sound/Big Mojo.mp3", FMOD_LOOP_NORMAL, NULL, &Game_theme);
	channel->setVolume(0.0f);
	
	channel = 0;
	my_channel = 0;

	result = system->playSound(FMOD_CHANNEL_FREE,my_sound,false,&my_channel);
	my_channel->setVolume(CMainMenuState::GetInstance()->GetMusicVolume()/100.0f);

	
	
}

void CGame::Shutdown(void)
{
	CGame::GetInstance()->channel->stop();
	CGame::GetInstance()->my_channel->stop();
	CMainMenuState::GetInstance()->DeleteInstance();
	CGamePlayState::GetInstance()->DeleteInstance();
	COptionsState::GetInstance()->DeleteInstance();
	CCreditsState::GetInstance()->DeleteInstance();
	CMessageSystem::GetInstance()->DeleteInstance();
	CEventSystem::GetInstance()->DeleteInstance();
	CBitmapFont::GetInstance()->DeleteInstance();
	CLoadGameState::GetInstance()->DeleteInstance();
	CStartState::GetInstance()->DeleteInstance();
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

	system->update();

	// let current state handle the update
	m_pCurState->Update(fElapsedTime);
}

void CGame::Render(void)
{
	// Clear the background
	m_pD3D->Clear( 255, 255, 255 );

	// Start D3D rendering
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();

	// Let the current state render
	m_pCurState->Render();
	
	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();	

	m_pD3D->Present();
}
