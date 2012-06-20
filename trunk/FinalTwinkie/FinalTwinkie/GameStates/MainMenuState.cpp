#include "MainMenuState.h"
#include "GamePlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "LoadGameState.h"
#include "TutorState.h"
#include "ShopState.h"
#include "GetNameState.h"
#include "../Headers/Game.h"
#include "../Headers/BitmapFont.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
#include <fstream>
#include "SurvivalState.h"

using namespace std;

CMainMenuState* CMainMenuState::m_pSelf = nullptr;

CMainMenuState* CMainMenuState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CMainMenuState;
	return m_pSelf;
}

void CMainMenuState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CMainMenuState::CMainMenuState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nSelected = 0;
	
	m_nBGImageID = -1;
	m_nNameImageID = -1;
	m_nButtonImageID = -1;
	m_nPosition = 0;
	m_nPointerID = -1;
	m_nMenuMusicID = -1;
	m_nButton = -1;
	m_nClick = -1;
	m_nSFXVolume = 50;
	m_nCurVolume = 50;
	m_nLang = 0;
	m_bWindowed = false;
	m_bPlaySelect = false;
	playing=false;

	LoadOptions("resource/files/options.txt");

	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nCursor = -1;
	m_nPos2=3;
}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pAudio = CSGD_XAudio2::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/Menu_Screen.png"));
	m_nNameImageID = m_pTM->LoadTexture(_T("resource/graphics/logo_game.png"));
	m_nPointerID = m_pTM->LoadTexture(_T("resource/graphics/SGD_MenuCursor.png"),D3DCOLOR_XRGB(255,0,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
	
	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));
	LoadOptions("resource/files/options.txt");

	COptionsState::GetInstance()->SetMusicVolume(m_nCurVolume);
	COptionsState::GetInstance()->SetSFXVolume(m_nSFXVolume);
	COptionsState::GetInstance()->SetWindowed(m_bWindowed);
	COptionsState::GetInstance()->SetLang(m_nLang);

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	LoadText();
	m_bPlaySelect=false;
	m_nPos2=3;
	playTimer=0;

	if(m_nMenuMusicID == -1)
	{
		m_nMenuMusicID = m_pAudio->MusicLoadSong(_T("resource/sound/MenuMusic.xwm"));
	}
	if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
	{
		playing=true;
	}
	else
	{
		playing=false;
	}	
}

void CMainMenuState::Exit(void)
{

	if(m_nButton != -1)
	{
		if(m_pAudio->SFXIsSoundPlaying(m_nButton))
			m_pAudio->SFXStopSound(m_nButton);

		m_pAudio->SFXUnloadSound(m_nButton);
		m_nButton = -1;
	}

	if(m_nClick != -1)
	{
		if(m_pAudio->SFXIsSoundPlaying(m_nClick))
			m_pAudio->SFXStopSound(m_nClick);

		m_pAudio->SFXUnloadSound(m_nClick);
		m_nClick = -1;
	}

	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	if(m_nNameImageID != -1)
	{
		m_pTM->UnloadTexture(m_nNameImageID);
		m_nNameImageID = -1;
	}

	if(m_nButtonImageID != -1)
	{
		m_pTM->UnloadTexture(m_nButtonImageID);
		m_nButtonImageID = -1;
	}

	if(m_nPointerID != -1)
	{
		m_pTM->UnloadTexture(m_nPointerID);
		m_nPointerID = -1;
	}

	if(m_nCursor != -1)
	{
		m_pTM->UnloadTexture(m_nCursor);
		m_nCursor = -1;
	}

	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_pAudio = nullptr;
	
	m_nSelected = 0;
}

bool CMainMenuState::Input(void)
{
	if(ARCADE ==0)
	{
		// Move the cursor position
		if(m_pDI->KeyPressed(DIK_UP) || m_pDI->JoystickDPadPressed(DIR_UP))
		{
			m_pAudio->SFXPlaySound(m_nButton,false);

			if(m_nPosition == 0)
			{
				m_nPosition = 3;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			else 
			{
				m_nPosition -= 1;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			m_nPos2=3;
		}
		else if(m_pDI->KeyPressed(DIK_DOWN) || m_pDI->JoystickDPadPressed(DIR_DOWN))
		{
			m_pAudio->SFXPlaySound(m_nButton,false);

			if(m_nPosition == 3)
			{
				m_nPosition = 0;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			else
			{
				m_nPosition += 1;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			m_nPos2=3;
		}
		if(m_bPlaySelect==true)
		{
			if(m_pDI->KeyPressed(DIK_RIGHT))
			{
				m_nPos2++;
				if(m_nPos2>6)
					m_nPos2=6;
			}
			if(m_pDI->KeyPressed(DIK_LEFT))
			{
				m_nPos2--;
				if(m_nPos2<3)
					m_nPos2=3;
			}
		}
		// Make selection
		if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(0) || m_pDI->MouseButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick, false);

			if(m_nPosition == 0)
			{
				if(m_bPlaySelect=true)
				{
					if(m_nPos2 == 4)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGame::GetInstance()->ChangeState(CLoadGameState::GetInstance());
						//playing=false;
						return true;
					}
					else if (m_nPos2 == 5)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGetNameState::GetInstance()->SetSurvival(true);
						CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
						//playing = false;
						return true;
					}
					else if(m_nPos2 == 6)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGame::GetInstance()->ChangeState(CTutorState::GetInstance());
						return true;
					}
				}
				else
				{
					m_bPlaySelect=true;
				}
			}
			if(m_nPosition == 1)
			{
				CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
				return true;
			}
			else if(m_nPosition == 2)
			{
				CGame::GetInstance()->ChangeState(CCreditsState::GetInstance());
				return true;
			}
			else if(m_nPosition == 3)
			{
				return false;
			}
	
		}
	}
	else
	{
			// Move the cursor position
		if(m_pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			m_pAudio->SFXPlaySound(m_nButton,false);

			if(m_nPosition == 0)
			{
				m_nPosition = 3;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			else 
			{
				m_nPosition -= 1;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			m_nPos2=3;
		}
		else if(m_pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			m_pAudio->SFXPlaySound(m_nButton,false);

			if(m_nPosition == 3)
			{
				m_nPosition = 0;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			else
			{
				m_nPosition += 1;
				m_bPlaySelect=false;
				m_nPos2=3;
			}
			m_nPos2=3;
		}
		if(m_bPlaySelect==true)
		{
			if(m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT))
			{
				m_nPos2++;
				if(m_nPos2>6)
					m_nPos2=6;
			}
			if(m_pDI->JoystickGetLStickDirPressed(DIR_LEFT))
			{
				m_nPos2--;
				if(m_nPos2<3)
					m_nPos2=3;
			}
		}
		// Make selection
		if(m_pDI->JoystickButtonPressed(0) || m_pDI->MouseButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick, false);

			if(m_nPosition == 0)
			{
				if(m_bPlaySelect=true)
				{
					if(m_nPos2 == 4)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGame::GetInstance()->ChangeState(CLoadGameState::GetInstance());
						//playing=false;
						return true;
					}
					else if (m_nPos2 == 5)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGetNameState::GetInstance()->SetSurvival(true);
						CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
						//playing = false;
						return true;
					}
					else if(m_nPos2 == 6)
					{
						if(m_pAudio->MusicIsSongPlaying(m_nMenuMusicID))
							m_pAudio->MusicStopSong(m_nMenuMusicID);
						CGame::GetInstance()->ChangeState(CTutorState::GetInstance());
						return true;
					}
				}
				else
				{
					m_bPlaySelect=true;
				}
			}
			if(m_nPosition == 1)
			{
				CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
				return true;
			}
			else if(m_nPosition == 2)
			{
				CGame::GetInstance()->ChangeState(CCreditsState::GetInstance());
				return true;
			}
			else if(m_nPosition == 3)
			{
				return false;
			}
	
		}
	}

	return true;
}

void CMainMenuState::Update(float fDt)
{
	if(ARCADE == 0)
	{
		if(m_pDI->JoystickGetLStickXAmount() > 0)
			m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()+5);
		if(m_pDI->JoystickGetLStickXAmount() < 0)
			m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()-5);
		if(m_pDI->JoystickGetLStickYAmount() > 0)
			m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()+5);
		if(m_pDI->JoystickGetLStickYAmount() < 0)
			m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()-5);
	}

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 295 && m_nMouseY <= 340)
	{
		if(m_nPosition != 0)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 0;
		}
	}
	else if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 340 && m_nMouseY <= 390)
	{
		if(m_nPosition != 1)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 1;
		}
		m_bPlaySelect=false;
		m_nPos2=3;
	}
	else if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 390 && m_nMouseY <= 435)
	{
		if(m_nPosition != 2)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 2;
		}
		m_bPlaySelect=false;
		m_nPos2=3;
	}
	else if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 435 && m_nMouseY <= 480)
	{
		if(m_nPosition != 3)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 3;
		}
		m_bPlaySelect=false;
		m_nPos2=3;
	}
	if(playTimer<1.0f)
	{
		playTimer+=fDt;
	}
	else if(playing==false)
	{
		playing=true;
		m_pAudio->MusicPlaySong(m_nMenuMusicID, true);
	}
}

void CMainMenuState::Render(void)
{
	m_pD3D->Clear( 69, 69, 69 );

	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());


	DWORD fScale1, fScale2, fScale3, fScale4;
	switch(m_nPosition)
	{
	case 0:
		fScale1 = D3DCOLOR_XRGB(177,132,0);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 1:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(177,132,0);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 2:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(177,132,0);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 3:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(177,132,0);
		break;
	default:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		break;
	}

	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nNameImageID,-50,50,0.85f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,75,295,0.75f,0.75f,nullptr,0,0,0,fScale1);
	m_pTM->Draw(m_nButtonImageID,75,CGame::GetInstance()->GetHeight()/2+45,0.75f,0.75f,nullptr,0,0,0,fScale2);
	m_pTM->Draw(m_nButtonImageID,75,CGame::GetInstance()->GetHeight()/2+95,0.75f,0.75f,nullptr,0,0,0,fScale3);
	m_pTM->Draw(m_nButtonImageID,75,CGame::GetInstance()->GetHeight()/2+145,0.75f,0.75f,nullptr,0,0,0,fScale4);
	
	
	m_pD3D->GetSprite()->Flush();
	
	if(COptionsState::GetInstance()->GetLang() == 1 || COptionsState::GetInstance()->GetLang() == 0)
	{
		font->Print(m_sPlay.c_str(),125,CGame::GetInstance()->GetHeight()/2,1.0f,		D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sOptions.c_str(),110,CGame::GetInstance()->GetHeight()/2+50,1.0f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sCredits.c_str(),110,CGame::GetInstance()->GetHeight()/2+100,1.0f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sExit.c_str(),125,CGame::GetInstance()->GetHeight()/2+150,1.0f,	D3DCOLOR_XRGB(177,132,0));
	}
	else if(COptionsState::GetInstance()->GetLang() == 3)
	{
		font->Print(m_sPlay.c_str(),125,CGame::GetInstance()->GetHeight()/2,1.0f,		D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sOptions.c_str(),110,CGame::GetInstance()->GetHeight()/2+50,1.0f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sCredits.c_str(),85,CGame::GetInstance()->GetHeight()/2+100,1.0f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sExit.c_str(),110,CGame::GetInstance()->GetHeight()/2+150,1.0f,	D3DCOLOR_XRGB(177,132,0));
	}
	else
	{
		font->Print(m_sPlay.c_str(),90,CGame::GetInstance()->GetHeight()/2,0.75,		D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sOptions.c_str(),85,CGame::GetInstance()->GetHeight()/2+50,0.75f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sCredits.c_str(),85,CGame::GetInstance()->GetHeight()/2+100,0.75f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sExit.c_str(),90,CGame::GetInstance()->GetHeight()/2+150,0.75f,	D3DCOLOR_XRGB(177,132,0));
	}

	/*char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));*/
	PlayHighlight(fScale1);
	m_pD3D->GetSprite()->Flush();
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);

	


}

bool CMainMenuState::LoadOptions(const char* szFileName)
{
	int nMVolume, nSFXVolume, nLang;
	bool bWindowed;
	ifstream fileIn;
	fileIn.open(szFileName,ios::in);
	if(fileIn.is_open())
	{
		fileIn >> nMVolume;
		fileIn.ignore(INT_MAX, '\n');
		fileIn >> nSFXVolume;
		fileIn.ignore(INT_MAX, '\n');
		fileIn >> bWindowed;
		fileIn.ignore(INT_MAX, '\n');
		fileIn >> nLang;
		fileIn.close();	

		m_nSFXVolume = nSFXVolume;
		m_nCurVolume = nMVolume;

		if(m_nSFXVolume > 100)
			m_nSFXVolume = 100;
		else if(m_nSFXVolume < 0)
			m_nSFXVolume = 0;

		if(m_nCurVolume > 100)
			m_nCurVolume = 100;
		else if(m_nCurVolume < 0)
			m_nCurVolume = 0;

		m_nLang = nLang;
		m_bWindowed = bWindowed;
		return true;
	}
	else
		return false;	
}

void CMainMenuState::PlayHighlight( DWORD dwPlayColor )
{
	if(m_bPlaySelect==true)
	{
		if(m_nMouseX >= 250 && m_nMouseX <= 417
			&& m_nMouseY >= 295 && m_nMouseY <= 335)
		{
			if(m_nPos2 != 4)
			{
				m_pAudio->SFXPlaySound(m_nButton);
				m_nPos2 = 4;
			}
		}
		else if(m_nMouseX >= 425 && m_nMouseX <= 597
			&& m_nMouseY >= 295 && m_nMouseY <= 335)
		{
			if(m_nPos2 != 5)
			{
				m_pAudio->SFXPlaySound(m_nButton);
				m_nPos2 = 5;
			}
		}
		else if(m_nMouseX >= 600 && m_nMouseX <= 772 && m_nMouseY >= 295 && m_nMouseY <= 335)
		{
			if(m_nPos2 != 6)
			{
				m_pAudio->SFXPlaySound(m_nButton);
				m_nPos2 = 6;
			}
		}
		else
		{
			//m_nPos2 = 0;
		}

		DWORD fScale1, fScale2,fScale3;
		switch(m_nPos2)
		{
		case 4:
			fScale1 = D3DCOLOR_XRGB(177,132,0);
			fScale2 = D3DCOLOR_XRGB(255,255,255);
			fScale3 = D3DCOLOR_XRGB(255,255,255);
			break;
		case 5:
			fScale1 = D3DCOLOR_XRGB(255,255,255);
			fScale2 = D3DCOLOR_XRGB(177,132,0);
			fScale3 = D3DCOLOR_XRGB(255,255,255);
			break;
		case 6:
			fScale1 = D3DCOLOR_XRGB(255,255,255);
			fScale2 = D3DCOLOR_XRGB(255,255,255);
			fScale3 = D3DCOLOR_XRGB(177,132,0);
			break;
		default:
			fScale1 = D3DCOLOR_XRGB(255,255,255);
			fScale2 = D3DCOLOR_XRGB(255,255,255);
			fScale3 = D3DCOLOR_XRGB(255,255,255);
		}

		if(COptionsState::GetInstance()->GetLang() == 1 || COptionsState::GetInstance()->GetLang() == 0)
		{
			m_pTM->Draw(m_nButtonImageID,250,295,0.75f,0.75f,nullptr,0,0,0,fScale1);
			CBitmapFont::GetInstance()->Print(m_sCampaign.c_str(),265,300,1.0f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,425,295,0.75f,0.75f,nullptr,0,0,0,fScale2);
			CBitmapFont::GetInstance()->Print(m_sSurvival.c_str(),440,300,1.0f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,600,295,0.75f,0.75f,nullptr,0,0,0,fScale3);
			CBitmapFont::GetInstance()->Print(m_sTutor.c_str(),615,300,1.0f,		D3DCOLOR_XRGB(177,132,0));
		}
		else if(COptionsState::GetInstance()->GetLang() == 2)
		{
			m_pTM->Draw(m_nButtonImageID,250,295,0.75f,0.75f,nullptr,0,0,0,fScale1);
			CBitmapFont::GetInstance()->Print(m_sCampaign.c_str(),265,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,425,295,0.75f,0.75f,nullptr,0,0,0,fScale2);
			CBitmapFont::GetInstance()->Print(m_sSurvival.c_str(),440,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,600,295,0.75f,0.75f,nullptr,0,0,0,fScale3);
			CBitmapFont::GetInstance()->Print(m_sTutor.c_str(),615,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
		}
		else
		{
			m_pTM->Draw(m_nButtonImageID,250,295,0.75f,0.75f,nullptr,0,0,0,fScale1);
			CBitmapFont::GetInstance()->Print(m_sCampaign.c_str(),265,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,425,295,0.75f,0.75f,nullptr,0,0,0,fScale2);
			CBitmapFont::GetInstance()->Print(m_sSurvival.c_str(),440,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
			m_pTM->Draw(m_nButtonImageID,600,295,0.75f,0.75f,nullptr,0,0,0,fScale3);
			CBitmapFont::GetInstance()->Print(m_sTutor.c_str(),615,300,0.85f,		D3DCOLOR_XRGB(177,132,0));
		}
		
	}
}

void CMainMenuState::LoadText(void)
{
	TiXmlDocument doc("resource/files/Text.xml");
	int LangSel=COptionsState::GetInstance()->GetLang();
	if(doc.LoadFile())
	{
		TiXmlNode* pParent = doc.RootElement();
		switch(LangSel)
		{
		case 0:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("MenuState");
				TiXmlNode* pButton = pState->FirstChild("Play");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sPlay=pText->Value();
				pButton=pState->FirstChild("Campaign");
				pText = pButton->FirstChild()->ToText();
				m_sCampaign=pText->Value();
				pButton=pState->FirstChild("Survival");
				pText = pButton->FirstChild()->ToText();
				m_sSurvival=pText->Value();
				pButton=pState->FirstChild("Tutorial");
				pText = pButton->FirstChild()->ToText();
				m_sTutor = pText->Value();
				pButton=pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton = pState->FirstChild("Credits");
				pText = pButton->FirstChild()->ToText();
				m_sCredits=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("MenuState");
				TiXmlNode* pButton = pState->FirstChild("Play");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sPlay=pText->Value();
				pButton=pState->FirstChild("Campaign");
				pText = pButton->FirstChild()->ToText();
				m_sCampaign=pText->Value();
				pButton=pState->FirstChild("Survival");
				pText = pButton->FirstChild()->ToText();
				m_sSurvival=pText->Value();
				pButton=pState->FirstChild("Tutorial");
				pText = pButton->FirstChild()->ToText();
				m_sTutor = pText->Value();
				pButton=pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton = pState->FirstChild("Credits");
				pText = pButton->FirstChild()->ToText();
				m_sCredits=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("MenuState");
				TiXmlNode* pButton = pState->FirstChild("Play");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sPlay=pText->Value();
				pButton=pState->FirstChild("Campaign");
				pText = pButton->FirstChild()->ToText();
				m_sCampaign=pText->Value();
				pButton=pState->FirstChild("Survival");
				pText = pButton->FirstChild()->ToText();
				m_sSurvival=pText->Value();
				pButton=pState->FirstChild("Tutorial");
				pText = pButton->FirstChild()->ToText();
				m_sTutor = pText->Value();
				pButton=pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton = pState->FirstChild("Credits");
				pText = pButton->FirstChild()->ToText();
				m_sCredits=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("MenuState");
				TiXmlNode* pButton = pState->FirstChild("Play");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sPlay=pText->Value();
				pButton=pState->FirstChild("Campaign");
				pText = pButton->FirstChild()->ToText();
				m_sCampaign=pText->Value();
				pButton=pState->FirstChild("Survival");
				pText = pButton->FirstChild()->ToText();
				m_sSurvival=pText->Value();
				pButton=pState->FirstChild("Tutorial");
				pText = pButton->FirstChild()->ToText();
				m_sTutor = pText->Value();
				pButton=pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton = pState->FirstChild("Credits");
				pText = pButton->FirstChild()->ToText();
				m_sCredits=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		}
	}
}
