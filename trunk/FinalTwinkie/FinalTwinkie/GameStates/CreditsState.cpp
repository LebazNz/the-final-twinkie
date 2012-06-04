#include "CreditsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"

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
	m_nButtonID = -1;
	m_nMouseX = 0;
	m_nMouseY = 0;
	
	m_nCursor = -1;
	m_dColor = D3DCOLOR_XRGB(255,255,255);
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
	m_nButtonID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"),D3DCOLOR_XRGB(255,255,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	LoadText();
}

void CCreditsState::Exit(void)
{
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

	if(m_nCursor != -1)
	{
		m_pTM->UnloadTexture(m_nCursor);
		m_nCursor = -1;
	}

	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
}

bool CCreditsState::Input(void)
{
	// Exit the game when the user presses esc
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1) || (m_nMouseX >= 25 && m_nMouseX <= 177 && m_nMouseY >= 545 && m_nMouseY <= 585 && m_pDI->KeyPressed(DIK_RETURN) || m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonDown(0)))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	return true;
}

void CCreditsState::Update(float fDt)
{
	if(m_pDI->JoystickGetLStickXAmount() > 0)
		m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()+5);
	if(m_pDI->JoystickGetLStickXAmount() < 0)
		m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()-5);
	if(m_pDI->JoystickGetLStickYAmount() > 0)
		m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()+5);
	if(m_pDI->JoystickGetLStickYAmount() < 0)
		m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()-5);

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	if(m_nMouseX >= 25 && m_nMouseX <= 177 && m_nMouseY >= 545 && m_nMouseY <= 585)
		m_dColor = D3DCOLOR_XRGB(177,132,0);
	else
		m_dColor = D3DCOLOR_XRGB(255,255,255);
}

void CCreditsState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);
	m_pTM->Draw(m_nButtonID,25,545,0.75f,0.75f,nullptr,0,0,0,m_dColor);
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

	font->Print(m_sDAP.c_str(),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)-75,1.0f,	D3DCOLOR_XRGB(255,0,0));
	font->Print("Anthony Cintron",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-45,				1.0f,				D3DCOLOR_XRGB(255,0,0));
	font->Print("Nate Zabel",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)-20,					1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Ryan Hofeling",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+5,				1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Joshua Franey",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+30,				1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print(m_sEP.c_str(),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+75,		1.0f,			D3DCOLOR_XRGB(255,0,0));
	font->Print("John O'Leske",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+105,				1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print(m_sAP.c_str(),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+150,		1.0f,			D3DCOLOR_XRGB(255,0,0));
	font->Print("Shawn Paris",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+180,				1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print(m_sAL.c_str(),(CGame::GetInstance()->GetWidth()/2)-125,(CGame::GetInstance()->GetHeight()/2)+205,					1.0f,					D3DCOLOR_XRGB(255,0,0));
	font->Print("Chris Jahosky",(CGame::GetInstance()->GetWidth()/2)-75,(CGame::GetInstance()->GetHeight()/2)+235,				1.0f,				D3DCOLOR_XRGB(255,0,0));

	font->Print(m_sBack.c_str(),75,550,		1.0f,	D3DCOLOR_XRGB(177,132,0));

	m_pD3D->GetSprite()->Flush();
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
}
void CCreditsState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("CreditsState");
				TiXmlNode* pButton = pState->FirstChild("DAP");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sDAP=pText->Value();
				pButton=pState->FirstChild("EP");
				pText = pButton->FirstChild()->ToText();
				m_sEP=pText->Value();
				pButton = pState->FirstChild("AP");
				pText = pButton->FirstChild()->ToText();
				m_sAP=pText->Value();
				pButton=pState->FirstChild("AL");
				pText = pButton->FirstChild()->ToText();
				m_sAL=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("CreditsState");
				TiXmlNode* pButton = pState->FirstChild("DAP");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sDAP=pText->Value();
				pButton=pState->FirstChild("EP");
				pText = pButton->FirstChild()->ToText();
				m_sEP=pText->Value();
				pButton = pState->FirstChild("AP");
				pText = pButton->FirstChild()->ToText();
				m_sAP=pText->Value();
				pButton=pState->FirstChild("AL");
				pText = pButton->FirstChild()->ToText();
				m_sAL=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
			}
			break;
		case 2:
			{
				/*TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("CreditsState");
				TiXmlNode* pButton = pState->FirstChild("DAP");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sDAP=pText->Value();
				pButton=pState->FirstChild("EP");
				pText = pButton->FirstChild()->ToText();
				m_sEP=pText->Value();
				pButton = pState->FirstChild("AP");
				pText = pButton->FirstChild()->ToText();
				m_sAP=pText->Value();
				pButton=pState->FirstChild("AL");
				pText = pButton->FirstChild()->ToText();
				m_sAL=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();*/
			}
			break;
		case 3:
			{
			}
			break;
		}
	}
}

