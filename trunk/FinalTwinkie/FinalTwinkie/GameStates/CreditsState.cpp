#include "CreditsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "OptionsState.h"

CCreditsState* CCreditsState::m_pSelf = nullptr;

CCreditsState* CCreditsState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CCreditsState;
	return m_pSelf;
}

void CCreditsState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CCreditsState::CCreditsState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nBGImageID = -1;
}

CCreditsState::~CCreditsState(void)
{
}

void CCreditsState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
}

void CCreditsState::Exit(void)
{
	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
}

bool CCreditsState::Input(void)
{
	// Exit the game when the user presses esc
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	return true;
}

void CCreditsState::Update(float fDt)
{

}

void CCreditsState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);
	m_pD3D->GetSprite()->Flush();
	/*m_pD3D->DrawText(_T("Designed and Programmed by:"),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)-75,255,255,255);
	m_pD3D->DrawText(_T("Anthony Cintron"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-45,255,255,255);
	m_pD3D->DrawText(_T("Nate Zabel"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-20,255,255,255);
	m_pD3D->DrawText(_T("Ryan Hofeling"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+5,255,255,255);
	m_pD3D->DrawText(_T("Joshua Franey"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+30,255,255,255);
	m_pD3D->DrawText(_T("Executive Producer:"),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+75,255,255,255);
	m_pD3D->DrawText(_T("John O’Leske"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+105,255,255,255);
	m_pD3D->DrawText(_T("Associate Producer:"),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+150,255,255,255);
	m_pD3D->DrawText(_T("Shawn Paris"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+180,255,255,255);
	m_pD3D->DrawText(_T("Art Lead:"),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+205,255,255,255);
	m_pD3D->DrawText(_T("Chris Jahosky"),(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+235,255,255,255);*/

	font->Print("Designed and Programmed by:",(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)-75,0.75f,	D3DCOLOR_XRGB(255,0,0));
	font->Print("Anthony Cintron",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-45,0.75f,				D3DCOLOR_XRGB(255,0,0));
	font->Print("Nate Zabel",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-20,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Ryan Hofeling",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+5,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Joshua Franey",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+30,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Executive Producer:",(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+75,0.75f,			D3DCOLOR_XRGB(255,0,0));
	font->Print("John O'Leske",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+105,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Associate Producer:",(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+150,0.75f,			D3DCOLOR_XRGB(255,0,0));
	font->Print("Shawn Paris",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+180,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Art Lead:",(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+205,0.75f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Chris Jahosky",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+235,0.75f,				D3DCOLOR_XRGB(255,0,0));

}
