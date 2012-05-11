#include "MainMenuState.h"
#include "GamePlayState.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "Game.h"

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
	int nY = 0;
	switch(m_nPosition)
	{
	case 0:
		nY = CGame::GetInstance()->GetHeight()/2;
		break;
	case 1:
		nY = (CGame::GetInstance()->GetHeight()/2)+20;
		break;
	case 2:
		nY = (CGame::GetInstance()->GetHeight()/2)+40;
		break;
	case 3:
		nY = (CGame::GetInstance()->GetHeight()/2)+60;
		break;
	}

	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nPointerID,(CGame::GetInstance()->GetWidth()/2)-50,nY,1.0f,1.0f,nullptr,0,0,0);
	m_pD3D->GetSprite()->Flush();
	m_pD3D->DrawText(_T("Play"),(CGame::GetInstance()->GetWidth()/2)-35,CGame::GetInstance()->GetHeight()/2,255,255,255);
	m_pD3D->DrawText(_T("Options"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+20,255,255,255);
	m_pD3D->DrawText(_T("Credits"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+40,255,255,255);
	m_pD3D->DrawText(_T("Exit"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+60,255,255,255);
}
