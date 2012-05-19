#include "MainMenuState.h"
#include "GamePlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "../Headers/Game.h"
#include "../Headers/BitmapFont.h"
#include <fstream>
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
	m_nPosition = 0;
	m_nPointerID = -1;
	m_nSFXVolume = -1;
	m_nCurVolume = -1;
	m_nLang = -1;
	m_bWindowed = false;

	LoadOptions("options.txt");
}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/Menu_Screen.png"),D3DCOLOR_XRGB(255,0,255));
	m_nPointerID = m_pTM->LoadTexture(_T("resource/graphics/SGD_MenuCursor.png"),D3DCOLOR_XRGB(255,0,255));
	
	LoadOptions("options.txt");

	COptionsState::GetInstance()->SetMusicVolume(m_nCurVolume);
	COptionsState::GetInstance()->SetSFXVolume(m_nSFXVolume);
	COptionsState::GetInstance()->SetWindowed(m_bWindowed);
	COptionsState::GetInstance()->SetLang(m_nLang);
}

void CMainMenuState::Exit(void)
{
	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	if(m_nPointerID != -1)
	{
		m_pTM->UnloadTexture(m_nPointerID);
		m_nPointerID = -1;
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
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
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
}

void CMainMenuState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init("resource/graphics/Font.png",43,32,9,11,20,' ');


	float fScale1, fScale2, fScale3, fScale4;
	switch(m_nPosition)
	{
	case 0:
		fScale1 = 1.0f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		break;
	case 1:
		fScale1 = 0.75f;
		fScale2 = 1.0f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		break;
	case 2:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 1.0f;
		fScale4 = 0.75f;
		break;
	case 3:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 1.0f;
		break;
	}

	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	//m_pTM->Draw(m_nPointerID,(CGame::GetInstance()->GetWidth()/2)-80,nY,1.0f,1.0f,nullptr,0,0,0);
	m_pD3D->GetSprite()->Flush();
	//m_pD3D->DrawText(_T("Play"),(CGame::GetInstance()->GetWidth()/2)-35,CGame::GetInstance()->GetHeight()/2,255,255,255);
	//m_pD3D->DrawText(_T("Options"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+20,255,255,255);
	//m_pD3D->DrawText(_T("Credits"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+40,255,255,255);
	//m_pD3D->DrawText(_T("Exit"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+60,255,255,255);

	font->Print("Play",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2,fScale1,D3DCOLOR_XRGB(0,255,0));
	font->Print("Options",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2+50,fScale2,D3DCOLOR_XRGB(0,255,0));
	font->Print("Credits",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2+100,fScale3,D3DCOLOR_XRGB(0,255,0));
	font->Print("Exit",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2+150,fScale4,D3DCOLOR_XRGB(0,255,0));

	/*font->Print("EFGHIJLKMNOPQRSTUVWXYZa",0,CGame::GetInstance()->GetHeight()/2,1.15f,D3DCOLOR_XRGB(255,255,255));
	font->Print("abcdefghijklmnopqrstuvwxyza",35,CGame::GetInstance()->GetHeight()/2+50,1.25f,D3DCOLOR_XRGB(255,255,255));
	font->Print("a0123456789A",35,CGame::GetInstance()->GetHeight()/2+150,1.25f,D3DCOLOR_XRGB(255,255,255));
	font->Print("a!\"#$%&'()*+,-./:;<=>?@[]^_'{|}!A",35,CGame::GetInstance()->GetHeight()/2+200,1.25f,D3DCOLOR_XRGB(255,255,255));*/

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
