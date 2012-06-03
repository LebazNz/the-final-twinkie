#include "LoadGameState.h"

#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "OptionsState.h"
#include "ShopState.h"
#include "GetNameState.h"
#include "../GameObjects/Player.h"
#include <iostream>
using namespace std;

#include "../tinyxml/tinyxml.h"

CLoadGameState* CLoadGameState::m_pSelf = nullptr;

CLoadGameState* CLoadGameState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CLoadGameState;
	return m_pSelf;
}

void CLoadGameState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CLoadGameState::CLoadGameState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nBGImageID = -1;
	m_nPosition = 0;
	m_nCount = 0;
	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nCursor = -1;
	m_nButtonImageID =-1;
}

CLoadGameState::~CLoadGameState(void)
{
}

void CLoadGameState::Enter(void)
{
	Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah",0,0,0,0,0,0,0,0,0,0,0,0,0};

	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));


	for(int i = 0; i < 3; ++i)
		vSavedData[i] = data;

	if(LoadSavedGame("savedGame1.xml",0) == true)
		m_nCount++;
	if(LoadSavedGame("savedGame2.xml",1) == true)
		m_nCount++;
	if(LoadSavedGame("savedGame3.xml",2) == true)
		m_nCount++;

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	CGame::GetInstance()->system->playSound(FMOD_CHANNEL_FREE,CGame::GetInstance()->Game_theme,false,&CGame::GetInstance()->my_channel);
	CGame::GetInstance()->my_channel->setVolume(CMainMenuState::GetInstance()->GetMusicVolume()/100.0f);
}

void CLoadGameState::Exit(void)
{
	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	if(m_nButtonImageID != -1)
	{
		m_pTM->UnloadTexture(m_nButtonImageID);
		m_nButtonImageID = -1;
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

	m_nCount = 0;
	m_nPosition = 0;
}

bool CLoadGameState::Input(void)
{
	// Exit the game when the user presses esc
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}

	// Move the cursor position
	if(m_pDI->KeyPressed(DIK_LEFT) || m_pDI->JoystickDPadPressed(DIR_LEFT))
	{
		switch(m_nCount)
		{
		case 0:
			if(m_nPosition == 0)
			{
				m_nPosition = 2;
			}
			else
			{
				m_nPosition -= 1;
			}
			break;
		case 1:
			if(m_nPosition == 0)
			{
				m_nPosition = 3;
			}
			else
			{
				m_nPosition -= 1;
			}
			break;
		case 2:
			if(m_nPosition == 0)
			{
				m_nPosition = 4;
			}
			else
			{
				m_nPosition -= 1;
			}
			break;
		case 3:
			if(m_nPosition == 0)
			{
				m_nPosition = 5;
			}
			else
			{
				m_nPosition -= 1;
			}
			break;
		}
	}
	else if(m_pDI->KeyPressed(DIK_RIGHT) || m_pDI->JoystickDPadPressed(DIR_RIGHT))
	{
		switch(m_nCount)
		{
		case 0:
			if(m_nPosition == 2)
			{
				m_nPosition = 0;
			}
			else
			{
				m_nPosition += 1;
			}
			break;
		case 1:
			if(m_nPosition == 3)
			{
				m_nPosition = 0;
			}
			else
			{
				m_nPosition += 1;
			}
			break;
		case 2:
			if(m_nPosition == 4)
			{
				m_nPosition = 0;
			}
			else
			{
				m_nPosition += 1;
			}
			break;
		case 3:
			if(m_nPosition == 5)
			{
				m_nPosition = 0;
			}
			else
			{
				m_nPosition += 1;
			}
			break;
		}
	}

	if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
	{
		if(m_nPosition == 0)
		{	
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				//Data data = {"Jack",1,40,-1,-1,500,0,0,0,0,1,0,0,0,0,0,1,0,0,1,"savedGame1.xml"};
				//Data data = {"Phillipe",1,40,-1,-1,500,0,0,0,0,0,0,0,0,0,0,1,0,0,1,"savedGame1.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame1.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				CPlayer::GetInstance()->SetName(vSavedData[m_nPosition].szName);
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 1)
		{
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				//Data data = {"Bob",1,40,-1,-1,500,0,0,0,0,1,0,0,0,0,0,1,0,0,1,"savedGame2.xml"};
				//Data data = {"Pablo",1,40,-1,-1,500,0,0,0,0,1,0,0,0,0,0,1,0,0,1,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame2.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				CPlayer::GetInstance()->SetName(vSavedData[m_nPosition].szName);
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 2)
		{		
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				//Data data = {"Fred",1,40,-1,-1,500,0,0,0,0,1,0,0,0,0,0,1,0,0,1,"savedGame3.xml"};
				//Data data = {"Marcos",1,40,-1,-1,500,0,0,0,0,0,0,0,0,0,0,1,0,0,1,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame3.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				CPlayer::GetInstance()->SetName(vSavedData[m_nPosition].szName);
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 3)
		{	
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame1.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame1.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
			else if(vSavedData[m_nPosition-1].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-1] = data;
				m_nCount--;
				m_nPosition-=1;
			}
		}
		else if(m_nPosition == 4)
		{	
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
		}
		else if(m_nPosition == 5)
		{	
			remove("savedGame3.xml");
			Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0};
			vSavedData[m_nPosition-3] = data;
			m_nCount--;
			m_nPosition-=3;			
		}
	}
	return true;
}

void CLoadGameState::Update(float fDt)
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

	if(m_nMouseX >= 45 && m_nMouseX <= 215
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		m_nPosition = 0;
	}
	if(m_nMouseX >= 295 && m_nMouseX <= 465
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		m_nPosition = 1;
	}
	if(m_nMouseX >= 550 && m_nMouseX <= 720
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		m_nPosition = 2;
	}
	if(m_nMouseX >= 45 && m_nMouseX <= 215
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[0].nLevel != 0)
			m_nPosition = 3;
	}
	if(m_nMouseX >= 295 && m_nMouseX <= 465
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[0].nLevel == 0)
			m_nPosition = 3;
		else
			m_nPosition = 4;
	}
	if(m_nMouseX >= 550 && m_nMouseX <= 720
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[0].nLevel == 0 && vSavedData[1].nLevel == 0 )
			m_nPosition = 3;
		else if((vSavedData[0].nLevel == 0 && vSavedData[1].nLevel != 0) || (vSavedData[0].nLevel != 0 && vSavedData[1].nLevel == 0) )
			m_nPosition = 4;
		else
			m_nPosition = 5;
	}
}

void CLoadGameState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);
		
	m_pD3D->GetSprite()->Flush();

	//char pos[10];
	//_itoa_s(m_nPosition,pos,10);

	//font->Print(pos,50,50,0.75f,D3DCOLOR_XRGB(255,0,0));

	DWORD fScale1, fScale2, fScale3, fScale4, fScale5, fScale6;
	switch(m_nPosition)
	{
	case 0:
		fScale1 = D3DCOLOR_XRGB(177,132,0);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		fScale6 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 1:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(177,132,0);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		fScale6 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 2:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(177,132,0);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		fScale6 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 3:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(177,132,0);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		fScale6 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 4:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(177,132,0);
		fScale6 = D3DCOLOR_XRGB(255,255,255);
		break;
	case 5:
		fScale1 = D3DCOLOR_XRGB(255,255,255);
		fScale2 = D3DCOLOR_XRGB(255,255,255);
		fScale3 = D3DCOLOR_XRGB(255,255,255);
		fScale4 = D3DCOLOR_XRGB(255,255,255);
		fScale5 = D3DCOLOR_XRGB(255,255,255);
		fScale6 = D3DCOLOR_XRGB(177,132,0);
		break;
	}

	if(vSavedData[0].nLevel == 0)
	{
		SetRect(&rSelf, 30, 630, 175, 940);
		m_pTM->Draw(m_nBGImageID,75,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,65,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,63,475,0.75f,0.75f,nullptr,0,0,0,fScale1);
		m_pD3D->GetSprite()->Flush();
		font->Print("New Game",80,480,1.0f,fScale1);
	}
	else
	{
		SetRect(&rSelf, 210, 630, 360, 940);
		m_pTM->Draw(m_nBGImageID,75,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,65,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,63,475,0.75f,0.75f,nullptr,0,0,0,fScale1);
		m_pTM->Draw(m_nButtonImageID,63,520,0.75f,0.75f,nullptr,0,0,0,fScale4);
		m_pD3D->GetSprite()->Flush();
		font->Print("Save 1",100,480,1.0f,fScale1);
		font->Print("Delete",100,525,1.0f,fScale4);
		font->Print("Name:",80,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Level:",80,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Money:",80,440,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[0].szName,150,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[0].nLevel,buffer,10);
		font->Print(buffer,150,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[0].nMoney,buffer,10);
		font->Print(buffer,150,440,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	if(vSavedData[1].nLevel == 0)
	{

		SetRect(&rSelf, 30, 630, 175, 940);
		m_pTM->Draw(m_nBGImageID,327,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,317,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,315,475,0.75f,0.75f,nullptr,0,0,0,fScale2);
		m_pD3D->GetSprite()->Flush();
		font->Print("New Game",332,480,1.0f,fScale2);
	}
	else
	{
		SetRect(&rSelf, 210, 630, 360, 940);
		m_pTM->Draw(m_nBGImageID,327,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,317,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,315,475,0.75f,0.75f,nullptr,0,0,0,fScale2);
		m_pTM->Draw(m_nButtonImageID,315,520,0.75f,0.75f,nullptr,0,0,0,fScale5);
		m_pD3D->GetSprite()->Flush();
		font->Print("Save 2",352,480,1.0f,fScale2);
		font->Print("Delete",352,525,1.0f,fScale5);
		font->Print("Name:",332,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Level:",332,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Money:",332,440,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[1].szName,402,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[1].nLevel,buffer,10);
		font->Print(buffer,402,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[1].nMoney,buffer,10);
		font->Print(buffer,402,440,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	if(vSavedData[2].nLevel == 0)
	{
		SetRect(&rSelf, 30, 630, 175, 940);
		m_pTM->Draw(m_nBGImageID,580,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,570,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,568,475,0.75f,0.75f,nullptr,0,0,0,fScale3);
		m_pD3D->GetSprite()->Flush();
		font->Print("New Game",585,480,1.0f,fScale3);
	}
	else
	{
		SetRect(&rSelf, 210, 630, 360, 940);
		m_pTM->Draw(m_nBGImageID,580,53,1.0f,1.0f,&rSelf,0,0,0);
		SetRect(&rSelf, 467, 638, 631, 760);
		m_pTM->Draw(m_nBGImageID,570,350,1.0f,1.0f,&rSelf,0,0,0);
		m_pTM->Draw(m_nButtonImageID,568,475,0.75f,0.75f,nullptr,0,0,0,fScale3);
		m_pTM->Draw(m_nButtonImageID,568,520,0.75f,0.75f,nullptr,0,0,0,fScale6);
		m_pD3D->GetSprite()->Flush();
		font->Print("Save 3",605,480,1.0f,fScale3);
		font->Print("Delete",605,525,1.0f,fScale6);
		font->Print("Name:",585,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Level:",585,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print("Money:",585,440,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[2].szName,655,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[2].nLevel,buffer,10);
		font->Print(buffer,655,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[2].nMoney,buffer,10);
		font->Print(buffer,655,440,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));

	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);


}

bool CLoadGameState::LoadSavedGame(const char* szFileName, int nGameData)
{
	TiXmlDocument doc;

	if(doc.LoadFile(szFileName) == false)
		return false;

	TiXmlElement* pRoot = doc.RootElement();
	if(pRoot == nullptr)
		return false;

	TiXmlElement* gameData = pRoot->FirstChildElement("game_data");

	
		Data info = {};

		const char* pText = gameData->GetText();
		if(pText != nullptr)
			strcpy_s(info.szName,32,pText);

		if(gameData->Attribute("level", &info.nLevel) == nullptr)
			info.nLevel = 0;

		if(gameData->Attribute("money", &info.nMoney) == nullptr)
			info.nMoney = 0;

		if(gameData->Attribute("hp", &info.nHp) == nullptr)
			info.nHp = 0;

		if(gameData->Attribute("armor", &info.nArmor) == nullptr)
			info.nArmor = 0;

		if(gameData->Attribute("ammo", &info.nAmmo) == nullptr)
			info.nAmmo = 0;

		if(gameData->Attribute("speed", &info.nSpeed) == nullptr)
			info.nSpeed = 0;

		if(gameData->Attribute("shellammo", &info.nShellAmmo) == nullptr)
			info.nShellAmmo = 0;

		if(gameData->Attribute("missileammo", &info.nMissileAmmo) == nullptr)
			info.nMissileAmmo = 0;

		if(gameData->Attribute("artilleryammo", &info.nArtilleryAmmo) == nullptr)
			info.nArtilleryAmmo = 0;

		if(gameData->Attribute("shell", &info.bShell) == nullptr)
			info.bShell = 0;

		if(gameData->Attribute("missile", &info.bMissile) == nullptr)
			info.bMissile = 0;

		if(gameData->Attribute("artillery", &info.bArtillery) == nullptr)
			info.bArtillery = 0;

		if(gameData->Attribute("airstrike", &info.bAirStrike) == nullptr)
			info.bAirStrike = 0;

		if(gameData->Attribute("emp", &info.bEMP) == nullptr)
			info.bEMP = 0;

		if(gameData->Attribute("nuke", &info.bNuke) == nullptr)
			info.bNuke = 0;

		if(gameData->Attribute("reinforce", &info.bReinforce) == nullptr)
			info.bReinforce = 0;

		if(gameData->Attribute("smoke", &info.bSmoke) == nullptr)
			info.bSmoke = 0;

		if(gameData->Attribute("laser", &info.nLaser) == nullptr)
			info.nLaser = 0;
		if(gameData->Attribute("machinegun"		, &info.nMachineGun) == nullptr)
			info.nMachineGun = 0;


		if(gameData->Attribute("HeatLevel"		, &info.nHeatLevel)==nullptr)
		{
			info.nHeatLevel = 0;
			info.fHeatModifier = 1;
		}
		else
		{
			info.fHeatModifier = 1 - CShopState::GetInstance()->GetHeatUp()*info.nHeatLevel;
		}
		if(gameData->Attribute("DamageLevel"	, &info.nDamageLevel)==nullptr)
		{
			info.nDamageLevel = 0;
			info.fDamageMod = 1;
		}
		else
		{
			info.fDamageMod = 1 + CShopState::GetInstance()->GetDamUp()*info.nDamageLevel;
		}

		if(gameData->Attribute("AmmoLevel"		, &info.nAmmoLevel)==nullptr)
		{
			info.nAmmoLevel = 0;
			info.fAmmoMod = 1;
		}
		else
		{
			info.fAmmoMod = 1 + CShopState::GetInstance()->GetAmmoUp()*info.nAmmoLevel;
		}
		if(gameData->Attribute("HealthLevel"	, &info.nHealthLevel)==nullptr)
		{
			info.nHealthLevel = 0;
			info.fHealthMod = 1;
		}
		else
		{
			info.fHealthMod = 1 + CShopState::GetInstance()->GetHealthUp()*info.nHealthLevel;
		}
		if(gameData->Attribute("ArmorLevel"		, &info.nArmorLevel)==nullptr)
		{
			info.nArmorLevel = 0;
			info.fArmorMod = 1;
		}
		else
		{
			info.fArmorMod = 1 + CShopState::GetInstance()->GetArmorUp()*info.nArmorLevel;
		}
		if(gameData->Attribute("SpeedLevel"		, &info.nSpeedLevel)==nullptr)
		{
			info.nSpeedLevel = 0;
			info.fSpeedMod = 1;
		}
		else
		{
			info.fSpeedMod = 1 + CShopState::GetInstance()->GetSpeedUp()*info.nSpeedLevel;
		}
		/*if(gameData->Attribute("RocketAccess"	, &info.bRocketAccess)==nullptr)
		info.bRocketAccess = 0;
		if(gameData->Attribute("LaserAccess"	, &info.bLaserAccess)==nullptr)
		info.bLaserAccess = 0;
		if(gameData->Attribute("NukeAccess"		, &info.bNukeAccess)==nullptr)
		info.bNukeAccess = 0;
		if(gameData->Attribute("EMPAccess"		, &info.bEMPAccess)==nullptr)
		info.bEMPAccess = 0;
		if(gameData->Attribute("ArtilleryAccess", &info.bArtilleryAccess)==nullptr)
		info.bArtilleryAccess = 0;
		if(gameData->Attribute("FlamerAccess"	, &info.bFlamerAccess)==nullptr)
		info.bFlamerAccess = 0;
		if(gameData->Attribute("AirStrikeAccess", &info.bAirStrikeAccess)==nullptr)
		info.bAirStrikeAccess = 0;
		if(gameData->Attribute("SmokeBombAccess", &info.bSmokeBombAccess)==nullptr)
		info.bSmokeBombAccess = 0;*/





		strcpy_s(info.szFileName,32,szFileName);

		vSavedData[nGameData] = info;

		

	return true;
}
