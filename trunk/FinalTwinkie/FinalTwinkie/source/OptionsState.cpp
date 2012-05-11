#include "OptionsState.h"
#include "Game.h"
#include "MainMenuState.h"

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
}

COptionsState::~COptionsState(void)
{
}

void COptionsState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/options_screen.png"),D3DCOLOR_XRGB(255,0,255));
	m_nPointerID = m_pTM->LoadTexture(_T("resource/graphics/SGD_MenuCursor.png"),D3DCOLOR_XRGB(255,0,255));
}

void COptionsState::Exit(void)
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
	else if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(m_nPosition == 0)
		{
			//CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			//return true;
		}
		else if(m_nPosition == 1)
		{
			//CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
			//return true;
		}
		else if(m_nPosition == 2)
		{
			//CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
			//return true;
		}
		else if(m_nPosition == 3)
		{
			//CGame::GetInstance()->ChangeState(CCreditsState::GetInstance());
			//return true;
		}
		else if(m_nPosition == 4)
		{
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			return true;
		}
	}
	// Exit the game when the user presses esc
	else if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}

	return true;
}

void COptionsState::Update(float fDt)
{
}

void COptionsState::Render(void)
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
	case 4:
		nY = (CGame::GetInstance()->GetHeight()/2)+80;
	}

	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nPointerID,(CGame::GetInstance()->GetWidth()/2)-50,nY,1.0f,1.0f,nullptr,0,0,0);
	m_pD3D->GetSprite()->Flush();
	m_pD3D->DrawText(_T("SFX Volume"),(CGame::GetInstance()->GetWidth()/2)-35,CGame::GetInstance()->GetHeight()/2,255,255,255);
	m_pD3D->DrawText(_T("Music Volume"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+20,255,255,255);
	m_pD3D->DrawText(_T("Full Screen"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+40,255,255,255);
	m_pD3D->DrawText(_T("Language"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+60,255,255,255);
	m_pD3D->DrawText(_T("Back"),(CGame::GetInstance()->GetWidth()/2)-35,(CGame::GetInstance()->GetHeight()/2)+80,255,255,255);

}
