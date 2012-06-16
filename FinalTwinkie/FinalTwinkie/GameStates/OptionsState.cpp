#include "OptionsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
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
	m_pAudio = nullptr;
	
	m_nSelected = 0;
	
	m_nBGImageID = -1;
	m_nPosition = 0;
	m_nPointerID = -1;
	m_nButton = -1;
	m_nClick = -1;
	m_nLang = 0;

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
	m_pAudio = CSGD_XAudio2::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));

	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));


	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();
	LoadText();
}

void COptionsState::Exit(void)
{
	SaveOptions("resource/files/options.txt");

	if(m_nButton != -1)
	{
		if(m_pAudio->SFXIsSoundPlaying(m_nButton))
			m_pAudio->SFXStopSound(m_nButton);

		m_pAudio->SFXUnloadSound(m_nButton);
		m_nButton = -1;
	}

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
	m_pAudio = nullptr;
	
	m_nPosition = 0;
	m_nSelected = 0;
}

bool COptionsState::Input(void)
{
	if(ARCADE == 0)
	{
		// Move the cursor position
		if(m_pDI->KeyPressed(DIK_UP) || m_pDI->JoystickDPadPressed(DIR_UP))
		{
			m_pAudio->SFXPlaySound(m_nButton);

			if(m_nPosition == 0)
			{
				m_nPosition = 4;
			}
			else
			{
				m_nPosition -= 1;
			}
		}
		else if(m_pDI->KeyPressed(DIK_DOWN) || m_pDI->JoystickDPadPressed(DIR_DOWN))
		{
			m_pAudio->SFXPlaySound(m_nButton);

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
		else if(m_pDI->KeyPressed(DIK_LEFTARROW) || m_pDI->JoystickDPadPressed(DIR_LEFT))
		{	
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0)
			{	
				m_fSFXVolume -= 0.05f;
				if(m_fSFXVolume <= 0.0f)
					m_fSFXVolume = 0.0f;
		
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1)
			{
				m_fMusicVolume -= 0.05f;
				if(m_fMusicVolume <= 0.0f)
					m_fMusicVolume = 0.0f;
							
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
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
					m_nLang = 3;
				LoadText();
			}
		}
		else if(m_pDI->KeyPressed(DIK_RIGHTARROW) || m_pDI->JoystickDPadPressed(DIR_RIGHT))
		{	
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0)
			{	
				m_fSFXVolume += 0.05f;
				if(m_fSFXVolume >= 1.0f)
					m_fSFXVolume = 1.0f;
			
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			
			}
			else if(m_nPosition == 1)
			{
				m_fMusicVolume += 0.05f;
				if(m_fMusicVolume >= 1.0f)
					m_fMusicVolume = 1.0f;
			
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
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
				if(m_nLang > 3)
					m_nLang = 0;
				LoadText();
			}
		}
		else if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 245 && m_nMouseY <= 285))
			{	
				m_fSFXVolume -= 0.05f;
				if(m_fSFXVolume <= 0.0f)
					m_fSFXVolume = 0.0f;
						
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 295 && m_nMouseY <= 335))
			{
				m_fMusicVolume -= 0.05f;
				if(m_fMusicVolume <= 0.0f)
					m_fMusicVolume = 0.0f;
							
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
			}
			else if(m_nPosition == 2 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 345 && m_nMouseY <= 385))
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
			else if(m_nPosition == 3 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 395 && m_nMouseY <= 435))
			{
				m_nLang -= 1;
				if(m_nLang < 0)
					m_nLang = 3;
				LoadText();
			}
			else if(m_nPosition == 0 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 245 && m_nMouseY <= 285))
			{	
				m_fSFXVolume += 0.05f;
				if(m_fSFXVolume >= 1.0f)
					m_fSFXVolume = 1.0f;
			
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 295 && m_nMouseY <= 335))
			{
				m_fMusicVolume += 0.05f;
				if(m_fMusicVolume >= 1.0f)
					m_fMusicVolume = 1.0f;
		
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
			}
			else if(m_nPosition == 2 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 345 && m_nMouseY <= 385))
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
			else if(m_nPosition == 3 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 395 && m_nMouseY <= 435))
			{
				m_nLang += 1;
				if(m_nLang > 3)
					m_nLang = 0;
				LoadText();
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
		else if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick);

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
		else if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
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
	else
	{
			// Move the cursor position
		if(m_pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			m_pAudio->SFXPlaySound(m_nButton);

			if(m_nPosition == 0)
			{
				m_nPosition = 4;
			}
			else
			{
				m_nPosition -= 1;
			}
		}
		else if(m_pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			m_pAudio->SFXPlaySound(m_nButton);

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
		else if(m_pDI->JoystickGetLStickDirPressed(DIR_LEFT))
		{	
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0)
			{	
				m_fSFXVolume -= 0.05f;
				if(m_fSFXVolume <= 0.0f)
					m_fSFXVolume = 0.0f;
		
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1)
			{
				m_fMusicVolume -= 0.05f;
				if(m_fMusicVolume <= 0.0f)
					m_fMusicVolume = 0.0f;
							
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
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
					m_nLang = 3;
				LoadText();
			}
		}
		else if(m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT))
		{	
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0)
			{	
				m_fSFXVolume += 0.05f;
				if(m_fSFXVolume >= 1.0f)
					m_fSFXVolume = 1.0f;
			
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			
			}
			else if(m_nPosition == 1)
			{
				m_fMusicVolume += 0.05f;
				if(m_fMusicVolume >= 1.0f)
					m_fMusicVolume = 1.0f;
			
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
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
				if(m_nLang > 3)
					m_nLang = 0;
				LoadText();
			}
		}
		else if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick);

			if(m_nPosition == 0 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 245 && m_nMouseY <= 285))
			{	
				m_fSFXVolume -= 0.05f;
				if(m_fSFXVolume <= 0.0f)
					m_fSFXVolume = 0.0f;
						
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 295 && m_nMouseY <= 335))
			{
				m_fMusicVolume -= 0.05f;
				if(m_fMusicVolume <= 0.0f)
					m_fMusicVolume = 0.0f;
							
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
			}
			else if(m_nPosition == 2 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 345 && m_nMouseY <= 385))
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
			else if(m_nPosition == 3 && (m_nMouseX >= 475 && m_nMouseX <= 585
			&& m_nMouseY >= 395 && m_nMouseY <= 435))
			{
				m_nLang -= 1;
				if(m_nLang < 0)
					m_nLang = 3;
				LoadText();
			}
			else if(m_nPosition == 0 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 245 && m_nMouseY <= 285))
			{	
				m_fSFXVolume += 0.05f;
				if(m_fSFXVolume >= 1.0f)
					m_fSFXVolume = 1.0f;
			
				m_pAudio->SFXSetMasterVolume(m_fSFXVolume);
			}
			else if(m_nPosition == 1 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 295 && m_nMouseY <= 335))
			{
				m_fMusicVolume += 0.05f;
				if(m_fMusicVolume >= 1.0f)
					m_fMusicVolume = 1.0f;
		
				m_pAudio->MusicSetMasterVolume(m_fMusicVolume);
			}
			else if(m_nPosition == 2 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 345 && m_nMouseY <= 385))
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
			else if(m_nPosition == 3 && (m_nMouseX >= 590 && m_nMouseX <= 700
			&& m_nMouseY >= 395 && m_nMouseY <= 435))
			{
				m_nLang += 1;
				if(m_nLang > 3)
					m_nLang = 0;
				LoadText();
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
		else if(m_pDI->JoystickButtonPressed(0) || m_pDI->MouseButtonPressed(0))
		{
			m_pAudio->SFXPlaySound(m_nClick);

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
		else if(m_pDI->JoystickButtonPressed(0))
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

	return true;
}

void COptionsState::Update(float fDt)
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

	if((m_nMouseX >= 475 && m_nMouseX <= 700
		&& m_nMouseY >= 245 && m_nMouseY <= 285)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 240 && m_nMouseY <= 280))
	{
		if(m_nPosition!=0)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 0;
		}
	}
	if((m_nMouseX >= 475 && m_nMouseX <= 700
		&& m_nMouseY >= 295 && m_nMouseY <= 335)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 290 && m_nMouseY <= 330))
	{
		if(m_nPosition!=1)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 1;
		}
	}
	if((m_nMouseX >= 475 && m_nMouseX <= 700
		&& m_nMouseY >= 345 && m_nMouseY <= 385)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 340 && m_nMouseY <= 375))
	{
		if(m_nPosition!=2)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 2;
		}
	}
	if((m_nMouseX >= 475 && m_nMouseX <= 700
		&& m_nMouseY >= 395 && m_nMouseY <= 435)||
		(m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 390 && m_nMouseY <= 425))
	{
		if(m_nPosition!=3)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 3;
		}
	}
	if((m_nMouseX >= 60 && m_nMouseX <= 282
		&& m_nMouseY >= 445 && m_nMouseY <= 480))
	{
		if(m_nPosition!=4)
		{
			m_pAudio->SFXPlaySound(m_nButton);
			m_nPosition = 4;
		}
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
	font->Print(m_sSFX.c_str(),(CGame::GetInstance()->GetWidth()/2)-295,CGame::GetInstance()->GetHeight()/2-50,	1.0f,	D3DCOLOR_XRGB(177,132,0));
	
	font->Print(m_sMusic.c_str(),(CGame::GetInstance()->GetWidth()/2)-300,CGame::GetInstance()->GetHeight()/2,	1.0f,	D3DCOLOR_XRGB(177,132,0));
	
	font->Print(m_sFullScreen.c_str(),(CGame::GetInstance()->GetWidth()/2)-295,CGame::GetInstance()->GetHeight()/2+50,	1.0f,	D3DCOLOR_XRGB(177,132,0));
	if(!m_bWindowed)																													  	
		font->Print(m_sOn.c_str(),(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2+50,		1.0f,	D3DCOLOR_XRGB(177,132,0));
	else																																  	
		font->Print(m_sOff.c_str(),(CGame::GetInstance()->GetWidth()/2)+165,CGame::GetInstance()->GetHeight()/2+50,		1.0f,	D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sLanguage.c_str(),(CGame::GetInstance()->GetWidth()/2)-275,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	D3DCOLOR_XRGB(177,132,0));
	switch(m_nLang)																														  	
	{																																	  	
	case 0:																																  	
		font->Print(m_sSelected.c_str(),(CGame::GetInstance()->GetWidth()/2)+139,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	D3DCOLOR_XRGB(177,132,0));
		break;																															  	
	case 1:																																  	
		font->Print(m_sSelected.c_str(),(CGame::GetInstance()->GetWidth()/2)+158,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	D3DCOLOR_XRGB(177,132,0));
		break;																															  	
	case 2:																																  	
		font->Print(m_sSelected.c_str(),(CGame::GetInstance()->GetWidth()/2)+158,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	D3DCOLOR_XRGB(177,132,0));
		break;	
	case 3:																																  	
		font->Print(m_sSelected.c_str(),(CGame::GetInstance()->GetWidth()/2)+158,CGame::GetInstance()->GetHeight()/2+100,	1.0f,	D3DCOLOR_XRGB(177,132,0));
		break;
	}																																	  	
	font->Print(m_sBack.c_str(),(CGame::GetInstance()->GetWidth()/2)-250,CGame::GetInstance()->GetHeight()/2+150,		1.0f,	D3DCOLOR_XRGB(177,132,0));


	font->Init(1);
	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2-45,			2.0f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("+",655,230,			2.5f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+5,				2.0f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("+",655,280,				2.5f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+55,			2.0f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("+",655,330,			2.5f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("-",(CGame::GetInstance()->GetWidth()/2)+100,CGame::GetInstance()->GetHeight()/2+105,			2.0f,	D3DCOLOR_XRGB(0,0,0));
	font->Print("+",655,380,			2.5f,	D3DCOLOR_XRGB(0,0,0));

	font->Init(0);
	font->Print(nSFXVolume,(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2-50,		1.0f,	D3DCOLOR_XRGB(177,132,0));
	font->Print(nVolume,(CGame::GetInstance()->GetWidth()/2)+175,CGame::GetInstance()->GetHeight()/2,			1.0f,	D3DCOLOR_XRGB(177,132,0));

	char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	/*_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(177,132,0));*/
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	/*_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(177,132,0));*/

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

void COptionsState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("OptionsState");
				TiXmlNode* pButton = pState->FirstChild("Options");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("SFX");
				pText = pButton->FirstChild()->ToText();
				m_sSFX=pText->Value();
				pButton = pState->FirstChild("Music");
				pText = pButton->FirstChild()->ToText();
				m_sMusic=pText->Value();
				pButton=pState->FirstChild("FullScreen");
				pText = pButton->FirstChild()->ToText();
				m_sFullScreen=pText->Value();
				pButton=pState->FirstChild("On");
				pText = pButton->FirstChild()->ToText();
				m_sOn=pText->Value();
				pButton=pState->FirstChild("Off");
				pText = pButton->FirstChild()->ToText();
				m_sOff=pText->Value();
				pButton=pState->FirstChild("Language");
				pText = pButton->FirstChild()->ToText();
				m_sLanguage=pText->Value();
				pButton=pState->FirstChild("Selected");
				pText = pButton->FirstChild()->ToText();
				m_sSelected=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("OptionsState");
				TiXmlNode* pButton = pState->FirstChild("Options");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("SFX");
				pText = pButton->FirstChild()->ToText();
				m_sSFX=pText->Value();
				pButton = pState->FirstChild("Music");
				pText = pButton->FirstChild()->ToText();
				m_sMusic=pText->Value();
				pButton=pState->FirstChild("FullScreen");
				pText = pButton->FirstChild()->ToText();
				m_sFullScreen=pText->Value();
				pButton=pState->FirstChild("On");
				pText = pButton->FirstChild()->ToText();
				m_sOn=pText->Value();
				pButton=pState->FirstChild("Off");
				pText = pButton->FirstChild()->ToText();
				m_sOff=pText->Value();
				pButton=pState->FirstChild("Language");
				pText = pButton->FirstChild()->ToText();
				m_sLanguage=pText->Value();
				pButton=pState->FirstChild("Selected");
				pText = pButton->FirstChild()->ToText();
				m_sSelected=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("OptionsState");
				TiXmlNode* pButton = pState->FirstChild("Options");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("SFX");
				pText = pButton->FirstChild()->ToText();
				m_sSFX=pText->Value();
				pButton = pState->FirstChild("Music");
				pText = pButton->FirstChild()->ToText();
				m_sMusic=pText->Value();
				pButton=pState->FirstChild("FullScreen");
				pText = pButton->FirstChild()->ToText();
				m_sFullScreen=pText->Value();
				pButton=pState->FirstChild("On");
				pText = pButton->FirstChild()->ToText();
				m_sOn=pText->Value();
				pButton=pState->FirstChild("Off");
				pText = pButton->FirstChild()->ToText();
				m_sOff=pText->Value();
				pButton=pState->FirstChild("Language");
				pText = pButton->FirstChild()->ToText();
				m_sLanguage=pText->Value();
				pButton=pState->FirstChild("Selected");
				pText = pButton->FirstChild()->ToText();
				m_sSelected=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("OptionsState");
				TiXmlNode* pButton = pState->FirstChild("Options");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("SFX");
				pText = pButton->FirstChild()->ToText();
				m_sSFX=pText->Value();
				pButton = pState->FirstChild("Music");
				pText = pButton->FirstChild()->ToText();
				m_sMusic=pText->Value();
				pButton=pState->FirstChild("FullScreen");
				pText = pButton->FirstChild()->ToText();
				m_sFullScreen=pText->Value();
				pButton=pState->FirstChild("On");
				pText = pButton->FirstChild()->ToText();
				m_sOn=pText->Value();
				pButton=pState->FirstChild("Off");
				pText = pButton->FirstChild()->ToText();
				m_sOff=pText->Value();
				pButton=pState->FirstChild("Language");
				pText = pButton->FirstChild()->ToText();
				m_sLanguage=pText->Value();
				pButton=pState->FirstChild("Selected");
				pText = pButton->FirstChild()->ToText();
				m_sSelected=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		}
	}
}