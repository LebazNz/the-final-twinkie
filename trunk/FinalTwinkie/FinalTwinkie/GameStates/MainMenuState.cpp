#include "MainMenuState.h"
#include "GamePlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "LoadGameState.h"
#include "../Headers/Game.h"
#include "../Headers/BitmapFont.h"
#include <fstream>
using namespace std;
bool CMainMenuState::playing=false;
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
	m_nSFXVolume = 50;
	m_nCurVolume = 50;
	m_nLang = 0;
	m_bWindowed = false;

	LoadOptions("options.txt");

	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nCursor = -1;
}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/Menu_Screen.png"));
	m_nNameImageID = m_pTM->LoadTexture(_T("resource/graphics/logo_game.png"));
	m_nPointerID = m_pTM->LoadTexture(_T("resource/graphics/SGD_MenuCursor.png"),D3DCOLOR_XRGB(255,0,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
	
	LoadOptions("options.txt");

	COptionsState::GetInstance()->SetMusicVolume(m_nCurVolume);
	COptionsState::GetInstance()->SetSFXVolume(m_nSFXVolume);
	COptionsState::GetInstance()->SetWindowed(m_bWindowed);
	COptionsState::GetInstance()->SetLang(m_nLang);

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();
	StartPlay=0;
}

void CMainMenuState::Exit(void)
{
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
	
	m_nSelected = 0;
}

bool CMainMenuState::Input(void)
{
	// Move the cursor position
	if(m_pDI->KeyPressed(DIK_UP))
	{
		if(m_nPosition == 0)
		{
			m_nPosition = 3;
		}
		else
		{
			m_nPosition -= 1;
		}
	}
	else if(m_pDI->KeyPressed(DIK_DOWN))
	{
		if(m_nPosition == 3)
		{
			m_nPosition = 0;
		}
		else
		{
			m_nPosition += 1;
		}
	}
	
	// Make selection
	else if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(m_nPosition == 0)
		{
			CGame::GetInstance()->my_channel->stop();
			CGame::GetInstance()->ChangeState(CLoadGameState::GetInstance());
			playing=false;
			return true;
		}
		else if(m_nPosition == 1)
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
	else if(m_pDI->MouseButtonPressed(0))
	{
		if(m_nPosition == 0)
		{
			CGame::GetInstance()->my_channel->stop();
			CGame::GetInstance()->ChangeState(CLoadGameState::GetInstance());
			playing=false;
			return true;
		}
		else if(m_nPosition == 1)
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
	// Exit the game when the user presses esc
	else if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void CMainMenuState::Update(float fDt)
{
	m_nMouseX = m_pDI->MouseGetPosX()-16;
	m_nMouseY = m_pDI->MouseGetPosY()-16;

	if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 295 && m_nMouseY <= 340)
	{
		m_nPosition = 0;
	}
	if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 340 && m_nMouseY <= 390)
	{
		m_nPosition = 1;
	}
	if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 390 && m_nMouseY <= 435)
	{
		m_nPosition = 2;
	}
	if(m_nMouseX >= 75 && m_nMouseX <= 242
		&& m_nMouseY >= 435 && m_nMouseY <= 480)
	{
		m_nPosition = 3;
	}
	if(StartPlay<1)
	{
		StartPlay+=fDt;
	}
	else if(StartPlay>=1&&playing==false)
	{
		CGame::GetInstance()->system->playSound(FMOD_CHANNEL_FREE, CGame::GetInstance()->Menu_theme, false, &CGame::GetInstance()->my_channel);
		CGame::GetInstance()->my_channel->setVolume(GetMusicVolume()/100.0f);
		playing=true;
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

	font->Print("Play",125,CGame::GetInstance()->GetHeight()/2,1.0f,		D3DCOLOR_XRGB(255,255,255));
	font->Print("Options",110,CGame::GetInstance()->GetHeight()/2+50,1.0f,	D3DCOLOR_XRGB(255,255,255));
	font->Print("Credits",110,CGame::GetInstance()->GetHeight()/2+100,1.0f,	D3DCOLOR_XRGB(255,255,255));
	font->Print("Exit",125,CGame::GetInstance()->GetHeight()/2+150,1.0f,	D3DCOLOR_XRGB(255,255,255));

	char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));

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
		m_nLang = nLang;
		m_bWindowed = bWindowed;
		return true;
	}
	else
		return false;	
}
