#include "OptionsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include <fstream>
using namespace std;

COptionsState* COptionsState::m_pSelf = nullptr;

COptionsState* COptionsState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new COptionsState;
	return m_pSelf;
}

void COptionsState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

COptionsState::COptionsState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nSelected = 0;
	
	m_nBGImageID = -1;
	m_nPosition = 0;
	m_nPointerID = -1;
	m_nLang = 0;

	CGame::GetInstance()->channel->getVolume(&m_fSFXVolume);
	CGame::GetInstance()->my_channel->getVolume(&m_fMusicVolume);

	m_bWindowed = CGame::GetInstance()->IsWindowed();

	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nCursor = -1;
	m_nButtonID = -1;
}

COptionsState::~COptionsState(void)
{
}

void COptionsState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));


	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();
}

void COptionsState::Exit(void)
{
	SaveOptions("options.txt");

	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	if(m_nButtonID != -1)
	{
		m_pTM->UnloadTexture(m_nButtonID);
		m_nButtonID = -1;
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
	
	m_nPosition = 0;
	m_nSelected = 0;
}

bool COptionsState::Input(void)
{
	// Move the cursor position
	if(m_pDI->KeyPressed(DIK_UP))
	{
		if(m_nPosition == 0)
		{
			m_nPosition = 4;
		}
		else
		{
			m_nPosition -= 1;
		}
	}
	else if(m_pDI->KeyPressed(DIK_DOWN))
	{
		if(m_nPosition == 4)
		{
			m_nPosition = 0;
		}
		else
		{
			m_nPosition += 1;
		}
	}
	// Make selection
	else if(m_pDI->KeyPressed(DIK_LEFTARROW))
	{	
		if(m_nPosition == 0)
		{	
			m_fSFXVolume -= 0.05f;
			if(m_fSFXVolume <= 0.0f)
				m_fSFXVolume = 0.0f;
						
			CGame::GetInstance()->channel->setVolume(m_fSFXVolume);
		}
		else if(m_nPosition == 1)
		{
			m_fMusicVolume -= 0.05f;
			if(m_fMusicVolume <= 0.0f)
				m_fMusicVolume = 0.0f;
							
			CGame::GetInstance()->my_channel->setVolume(m_fMusicVolume);
		}
		else if(m_nPosition == 2)
		{
			m_bWindowed = !m_bWindowed;
			CGame::GetInstance()->SetIsWindowded(m_bWindowed);
			if(m_bWindowed == false)
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
			else
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
		}
		else if(m_nPosition == 3)
		{
			m_nLang -= 1;
			if(m_nLang < 0)
				m_nLang = 2;
		}
	}
	else if(m_pDI->KeyPressed(DIK_RIGHTARROW))
	{	
		if(m_nPosition == 0)
		{	
			m_fSFXVolume += 0.05f;
			if(m_fSFXVolume >= 1.0f)
				m_fSFXVolume = 1.0f;
			
			CGame::GetInstance()->channel->setVolume(m_fSFXVolume);
		}
		else if(m_nPosition == 1)
		{
			m_fMusicVolume += 0.05f;
			if(m_fMusicVolume >= 1.0f)
				m_fMusicVolume = 1.0f;
			
			CGame::GetInstance()->my_channel->setVolume(m_fMusicVolume);
		}
		else if(m_nPosition == 2)
		{
			m_bWindowed = !m_bWindowed;
			CGame::GetInstance()->SetIsWindowded(m_bWindowed);
			if(m_bWindowed == false)
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
			else
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
		}
		else if(m_nPosition == 3)
		{
			m_nLang += 1;
			if(m_nLang > 2)
				m_nLang = 0;		
		}
	}
	else if(m_pDI->MouseButtonPressed(0))
	{
		if(m_nPosition == 0 && (m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 240 && m_nMouseY <= 280))
		{	
			m_fSFXVolume -= 0.05f;
			if(m_fSFXVolume <= 0.0f)
				m_fSFXVolume = 0.0f;
						
			CGame::GetInstance()->channel->setVolume(m_fSFXVolume);
		}
		else if(m_nPosition == 1 && (m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 290 && m_nMouseY <= 330))
		{
			m_fMusicVolume -= 0.05f;
			if(m_fMusicVolume <= 0.0f)
				m_fMusicVolume = 0.0f;
							
			CGame::GetInstance()->my_channel->setVolume(m_fMusicVolume);
		}
		else if(m_nPosition == 2 && (m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 340 && m_nMouseY <= 375))
		{
			m_bWindowed = !m_bWindowed;
			CGame::GetInstance()->SetIsWindowded(m_bWindowed);
			if(m_bWindowed == false)
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
			else
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
		}
		else if(m_nPosition == 3 && (m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 390 && m_nMouseY <= 425))
		{
			m_nLang -= 1;
			if(m_nLang < 0)
				m_nLang = 2;
		}
		else if(m_nPosition == 0 && (m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 240 && m_nMouseY <= 280))
		{	
			m_fSFXVolume += 0.05f;
			if(m_fSFXVolume >= 1.0f)
				m_fSFXVolume = 1.0f;
			
			CGame::GetInstance()->channel->setVolume(m_fSFXVolume);
		}
		else if(m_nPosition == 1 && (m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 290 && m_nMouseY <= 330))
		{
			m_fMusicVolume += 0.05f;
			if(m_fMusicVolume >= 1.0f)
				m_fMusicVolume = 1.0f;
			
			CGame::GetInstance()->my_channel->setVolume(m_fMusicVolume);
		}
		else if(m_nPosition == 2 && (m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 340 && m_nMouseY <= 375))
		{
			m_bWindowed = !m_bWindowed;
			CGame::GetInstance()->SetIsWindowded(m_bWindowed);
			if(m_bWindowed == false)
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
			else
			{
				m_pD3D->ChangeDisplayParam(CGame::GetInstance()->GetWidth(),CGame::GetInstance()->GetHeight(),CGame::GetInstance()->IsWindowed());
			}
		}
		else if(m_nPosition == 3 && (m_nMouseX >= 670 && m_nMouseX <= 700
		&& m_nMouseY >= 390 && m_nMouseY <= 425))
		{
			m_nLang += 1;
			if(m_nLang > 2)
				m_nLang = 0;		
		}
		else if(m_nPosition == 4)
		{
			if(CGamePlayState::GetInstance()->GetPaused() == false)
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				return true;
			}
			else
			{
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
		}
	}
		// Make selection
	else if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(m_nPosition == 4)
		{
			if(CGamePlayState::GetInstance()->GetPaused() == false)
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				return true;
			}
			else
			{
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
		}
	}
	// Exit the game when the user presses esc
	else if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		if(CGamePlayState::GetInstance()->GetPaused() == false)
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				return true;
			}
			else
			{
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
	}

	return true;
}

void COptionsState::Update(float fDt)
{
	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	if((m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 240 && m_nMouseY <= 280)||
		(m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 240 && m_nMouseY <= 280) ||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 240 && m_nMouseY <= 280))
	{
		m_nPosition = 0;
	}
	if((m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 290 && m_nMouseY <= 330)||
		(m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 290 && m_nMouseY <= 330)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 290 && m_nMouseY <= 330))
	{
		m_nPosition = 1;
	}
	if((m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 340 && m_nMouseY <= 375)||
		(m_nMouseX >= 615 && m_nMouseX <= 650
		&& m_nMouseY >= 340 && m_nMouseY <= 375)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 340 && m_nMouseY <= 375))
	{
		m_nPosition = 2;
	}
	if((m_nMouseX >= 490 && m_nMouseX <= 525
		&& m_nMouseY >= 390 && m_nMouseY <= 425)||
		(m_nMouseX >= 670 && m_nMouseX <= 700
		&& m_nMouseY >= 390 && m_nMouseY <= 425)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 390 && m_nMouseY <= 425))
	{
		m_nPosition = 3;
	}
	if((m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 445 && m_nMouseY <= 480))
	{
		m_nPosition = 4;
	}
}

void COptionsState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());


	DWORD fScale1, fScale2, fScale3, fScale4, fScale5;
	switch(m_nPosition)
	{
	case 0:
		fScale1 = D3DCOLOR_XRGB(177,132,0);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 1:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(177,132,0);	 
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 2:
		fScale1 = D3DCOLOR_XRGB(255,255,255); 
		fScale2 = D3DCOLOR_XRGB(255,255,255); 
		fScale3 = D3DCOLOR_XRGB(177,132,0);	  
		fScale4 = D3DCOLOR_XRGB(255,255,255); 
		fScale5 = D3DCOLOR_XRGB(255,255,255); 
		break;
	case 3:
		fScale1 = D3DCOLOR_XRGB(255,255,255); 
		fScale2 = D3DCOLOR_XRGB(255,255,255); 
		fScale3 = D3DCOLOR_XRGB(255,255,255); 
		fScale4 = D3DCOLOR_XRGB(177,132,0);   
		fScale5 = D3DCOLOR_XRGB(255,255,255); 
		break;
	case 4:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(177,132,0);
		break;
	}
	
	char nVolume[100];
	sprintf_s(nVolume,100,"%0.0f",m_fMusicVolume*100);
	char nSFXVolume[100];
	sprintf_s(nSFXVolume,100,"%0.0f",m_fSFXVolume*100);
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);
	m_pTM->Draw(m_nButtonID,75,245,1.0f,0.75f,nullptr,0,0,0,fScale1);
	m_pTM->Draw(m_nButtonID,75,295,1.0f,0.75f,nullptr,0,0,0,fScale2);
	m_pTM->Draw(m_nButtonID,75,CGame::GetInstance()->GetHeight()/2+45,1.0f,0.75f,nullptr,0,0,0,fScale3);
	m_pTM->Draw(m_nButtonID,75,CGame::GetInstance()->GetHeight()/2+95,1.0f,0.75f,nullptr,0,0,0,fScale4);
	m_pTM->Draw(m_nButtonID,75,CGame::GetInstance()->GetHeight()/2+145,1.0f,0.75f,nullptr,0,0,0,fScale5);

	m_pTM->Draw(m_nButtonID,(CGame::GetInstance()->GetWidth()/2)+75,245,1.0f,0.75f,nullptr,0,0,0,fScale1);
	m_pTM->Draw(m_nButtonID,(CGame::GetInstance()->GetWidth()/2)+75,295,1.0f,0.75f,nullptr,0,0,0,fScale2);
	m_pTM->Draw(m_nButtonID,(CGame::GetInstance()->GetWidth()/2)+75,CGame::GetInstance()->GetHeight()/2+45,1.0f,0.75f,nullptr,0,0,0,fScale3);
	m_pTM->Draw(m_nButtonID,(CGame::GetInstance()->GetWidth()/2)+75,CGame::GetInstance()->GetHeight()/2+95,1.0f,0.75f,nullptr,0,0,0,fScale4);
	
	
	m_pD3D->GetSprite()->Flush();
	font->Print("SFX Volume:",(CGame::GetInstance()->GetWidth()/2)-295,CGame::GetInstance()->GetHeight()/2-50,	1.0f,	fScale1);
	
	font->Print("Music Volume:",(CGame::GetInstance()->GetWidth()/2)-300,CGame::GetInstance()->GetHeight()/2,	1.0f,	fScale2);
	
	font->Print("Full Screen:",(CGame::GetInstance()->GetWidth()/2)-295,CGame::GetInstance()->GetHeight()/2+50,	1.0f,	fScale3);
	if(!m_bWindowed)																													  	
		font->Print("On",(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2+50,		1.0f,	fScale3);
	else																																  	
		font->Print("Off",(CGame::GetInstance()->GetWidth()/2)+165,CGame::GetInstance()->GetHeight()/2+50,		1.0f,	fScale3);
	font->Print("Language:",(CGame::GetInstance()->GetWidth()/2)-275,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	fScale4);
	switch(m_nLang)																														  	
	{																																	  	
	case 0:																																  	
		font->Print("English",(CGame::GetInstance()->GetWidth()/2)+139,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	fScale4);
		break;																															  	
	case 1:																																  	
		font->Print("German",(CGame::GetInstance()->GetWidth()/2)+158,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	fScale4);
		break;																															  	
	case 2:																																  	
		font->Print("Pirate",(CGame::GetInstance()->GetWidth()/2)+158,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	fScale4);
		break;																															  	
	}																																	  	
	font->Print("Back",(CGame::GetInstance()->GetWidth()/2)-250,CGame::GetInstance()->GetHeight()/2+150,		1.0f,	fScale5);


	font->Init(1);
	font->Print(nSFXVolume,(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2-45,		1.0f,	fScale1);
	font->Print(nVolume,(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2+5,			1.0f,	fScale2);

	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2-40,			1.0f,	fScale1);
	font->Print("+",(CGame::GetInstance()->GetWidth()/2)+275,CGame::GetInstance()->GetHeight()/2-55,			1.5f,	fScale1);

	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+10,				1.0f,	fScale2);
	font->Print("+",(CGame::GetInstance()->GetWidth()/2)+275,CGame::GetInstance()->GetHeight()/2-5,			1.5f,	fScale2);

	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+60,			1.0f,	fScale3);
	font->Print("+",(CGame::GetInstance()->GetWidth()/2)+275,CGame::GetInstance()->GetHeight()/2+45,			1.5f,	fScale3);

	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+110,			1.0f,	fScale4);
	font->Print("+",(CGame::GetInstance()->GetWidth()/2)+275,CGame::GetInstance()->GetHeight()/2+95,			1.5f,	fScale4);

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

void COptionsState::SaveOptions(const char* szFileName)
{
	ofstream fileOut;
	fileOut.open(szFileName, ios::out | ios::trunc);
	if(fileOut.is_open())
	{
		fileOut << m_fMusicVolume*100.0f << '\n';
		fileOut << m_fSFXVolume*100.0f << '\n';
		fileOut << m_bWindowed << '\n';
		fileOut << m_nLang << '\n';
	}
	fileOut.close();
}
