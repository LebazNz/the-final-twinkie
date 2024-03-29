#include "StartState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

CStartState* CStartState::m_pSelf = nullptr;

CStartState* CStartState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CStartState;
	return m_pSelf;
}

void CStartState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CStartState::CStartState(void)
{
	m_pD3D = nullptr;
	m_pTM = nullptr;
	m_pDI = nullptr;
	m_pAudio = nullptr;

	m_nEndTimer = 0;

	m_nBG1ID = -1;
	m_nBG2ID = -1;
	m_nMusic = -1;

	m_bSwitch = false;
}

CStartState::~CStartState(void)
{
}

void CStartState::Enter(void)
{
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pTM	= CSGD_TextureManager::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pAudio = CSGD_XAudio2::GetInstance();


	m_nMusic = m_pAudio->MusicLoadSong(_T("resource/sound/StartMusic.xwm"));
	m_pAudio->MusicPlaySong(m_nMusic, false);

	m_nBG1ID = m_pTM->LoadTexture(_T("resource/graphics/start_screen.png"));
	m_nBG2ID = m_pTM->LoadTexture(_T("resource/graphics/TFTimage.png"));
	
	m_nEndTimer = 0;

	m_bSwitch = false;
}

void CStartState::Exit(void)
{
	if(m_nMusic != -1)
	{
		if(m_pAudio->MusicIsSongPlaying(m_nMusic))
			m_pAudio->MusicStopSong(m_nMusic);

		m_pAudio->MusicUnloadSong(m_nMusic);
		m_nMusic = -1;
	}

	if(m_nBG1ID != -1)
	{
		m_pTM->UnloadTexture(m_nBG1ID);
		m_nBG1ID = -1;
	}

	if(m_nBG2ID != -1)
	{
		m_pTM->UnloadTexture(m_nBG2ID);
		m_nBG2ID = -1;
	}

	m_pD3D = nullptr;
	m_pTM = nullptr;
	m_pDI = nullptr;

	m_bSwitch = false;
}

bool CStartState::Input(void)
{
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(0) || m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(6))
	{
		if(m_bSwitch==false)
			m_bSwitch=true;
		else
		{
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			
		}
		return true;
	}
	return true;
}

void CStartState::Update(float fDt)
{
	m_nEndTimer += fDt;
	if(m_nEndTimer >= 4 && m_bSwitch == false)
	{
		m_bSwitch = true;
		m_nEndTimer = 0;
	}
	else if(m_nEndTimer >= 8 && m_bSwitch == true)
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
}

void CStartState::Render(void)
{
	m_pD3D->Clear( 0, 255, 255 );
	RECT rSelf;
	SetRect(&rSelf,0,0,800,600);
	if(m_bSwitch == false)
		m_pTM->Draw(m_nBG1ID,0,0,1.0f,1.0f,&rSelf,0,0,0);
	else
		m_pTM->Draw(m_nBG2ID,0,0,1.0f,1.0f,&rSelf,0,0,0);

}
