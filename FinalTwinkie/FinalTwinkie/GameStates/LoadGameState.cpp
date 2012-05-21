#include "LoadGameState.h"

#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"

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
}

CLoadGameState::~CLoadGameState(void)
{
}

void CLoadGameState::Enter(void)
{
	Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};

	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/load_screen.png"),D3DCOLOR_XRGB(255,0,255));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	
	for(int i = 0; i < 3; ++i)
		vSavedData[i] = data;

	if(LoadSavedGame("savedGame1.xml",0) == true)
		m_nCount++;
	if(LoadSavedGame("savedGame2.xml",1) == true)
		m_nCount++;
	if(LoadSavedGame("savedGame3.xml",2) == true)
		m_nCount++;

	m_nMouseX = m_pDI->MouseGetPosX()-16;
	m_nMouseY = m_pDI->MouseGetPosY()-16;
}

void CLoadGameState::Exit(void)
{
	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
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
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}

	// Move the cursor position
	if(m_pDI->KeyPressed(DIK_LEFT))
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
	else if(m_pDI->KeyPressed(DIK_RIGHT))
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

	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(m_nPosition == 0)
		{	
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Jack",1,40,0,0,4500,0,0,0,1,0,0,1,0,0,0,1,0,0,1,"savedGame1.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 1)
		{
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Bob",1,40,0,0,500,0,0,1,0,0,0,1,0,0,0,1,0,0,1,"savedGame2.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 2)
		{		
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Fred",1,40,0,0,1500,0,0,0,0,0,1,0,0,0,0,1,0,0,1,"savedGame3.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 3)
		{	
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame1.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
			else if(vSavedData[m_nPosition-1].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
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
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
		}
		else if(m_nPosition == 5)
		{	
			remove("savedGame3.xml");
			Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
			vSavedData[m_nPosition-3] = data;
			m_nCount--;
			m_nPosition-=3;			
		}
	}
	else if(m_pDI->MouseButtonPressed(0))
	{
		if(m_nPosition == 0)
		{	
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Jack",1,40,0,0,4500,0,0,0,1,0,0,1,0,0,0,1,0,0,1,"savedGame1.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			m_pDI->ReadDevices();
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 1)
		{
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Bob",1,40,0,0,500,0,0,1,0,0,0,1,0,0,0,1,0,0,1,"savedGame2.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			m_pDI->ReadDevices();
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 2)
		{		
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				Data data = {"Fred",1,40,0,0,1500,0,0,0,0,0,1,0,0,0,0,1,0,0,1,"savedGame3.xml"};
				vSavedData[m_nPosition] = data;
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			m_pDI->ReadDevices();
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
			return true;
		}
		else if(m_nPosition == 3)
		{	
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame1.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
			else if(vSavedData[m_nPosition-1].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
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
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
		}
		else if(m_nPosition == 5)
		{	
			remove("savedGame3.xml");
			Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah"};
			vSavedData[m_nPosition-3] = data;
			m_nCount--;
			m_nPosition-=3;			
		}
	}



	return true;
}

void CLoadGameState::Update(float fDt)
{
	m_nMouseX = m_pDI->MouseGetPosX()-16;
	m_nMouseY = m_pDI->MouseGetPosY()-16;

	if(m_nMouseX >= 25 && m_nMouseX <= 225
		&& m_nMouseY >= 475 && m_nMouseY <= 520)
	{
		m_nPosition = 0;
	}
	if(m_nMouseX >= 290 && m_nMouseX <= 490
		&& m_nMouseY >= 475 && m_nMouseY <= 520)
	{
		m_nPosition = 1;
	}
	if(m_nMouseX >= 540 && m_nMouseX <= 740
		&& m_nMouseY >= 475 && m_nMouseY <= 520)
	{
		m_nPosition = 2;
	}
	if(m_nMouseX >= 25 && m_nMouseX <= 225
		&& m_nMouseY >= 540 && m_nMouseY <= 560)
	{
		if(vSavedData[0].nLevel != 0)
			m_nPosition = 3;
	}
	if(m_nMouseX >= 290 && m_nMouseX <= 490
		&& m_nMouseY >= 540 && m_nMouseY <= 560)
	{
		if(vSavedData[0].nLevel == 0)
			m_nPosition = 3;
		else
			m_nPosition = 4;
	}
	if(m_nMouseX >= 540 && m_nMouseX <= 740
		&& m_nMouseY >= 540 && m_nMouseY <= 560)
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
	font->Init("resource/graphics/Font.png",43,32,9,11,20,' ');

	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
	
	m_pD3D->GetSprite()->Flush();

	char pos[10];
	_itoa_s(m_nPosition,pos,10);

	font->Print(pos,50,50,0.75f,D3DCOLOR_XRGB(255,0,0));

	float fScale1, fScale2, fScale3, fScale4, fScale5, fScale6;
	switch(m_nPosition)
	{
	case 0:
		fScale1 = 1.0f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		fScale5 = 0.75f;
		fScale6 = 0.75f;
		break;
	case 1:
		fScale1 = 0.75f;
		fScale2 = 1.0f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		fScale5 = 0.75f;
		fScale6 = 0.75f;
		break;
	case 2:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 1.0f;
		fScale4 = 0.75f;
		fScale5 = 0.75f;
		fScale6 = 0.75f;
		break;
	case 3:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 1.0f;
		fScale5 = 0.75f;
		fScale6 = 0.75f;
		break;
	case 4:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		fScale5 = 1.0f;
		fScale6 = 0.75f;
		break;
	case 5:
		fScale1 = 0.75f;
		fScale2 = 0.75f;
		fScale3 = 0.75f;
		fScale4 = 0.75f;
		fScale5 = 0.75f;
		fScale6 = 1.0f;
		break;
	}

	if(vSavedData[0].nLevel == 0)
		font->Print("New Game",50,500,fScale1,D3DCOLOR_XRGB(255,0,0));
	else
	{
		font->Print("Save 1",50,500,fScale1,D3DCOLOR_XRGB(255,0,0));
		font->Print("Delete",50,550,fScale4,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[0].szName,50,250,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[0].nLevel,buffer,10);
		font->Print(buffer,50,275,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[0].nMoney,buffer,10);
		font->Print(buffer,50,300,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	if(vSavedData[1].nLevel == 0)
		font->Print("New Game",300,500,fScale2,D3DCOLOR_XRGB(255,0,0));
	else
	{
		float fScale;
		if(vSavedData[0].nLevel == 0)
			fScale = fScale4;
		else
			fScale = fScale5;
		font->Print("Save 2",300,500,fScale2,D3DCOLOR_XRGB(255,0,0));
		font->Print("Delete",300,550,fScale,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[1].szName,300,250,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[1].nLevel,buffer,10);
		font->Print(buffer,300,275,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[1].nMoney,buffer,10);
		font->Print(buffer,300,300,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	if(vSavedData[2].nLevel == 0)
		font->Print("New Game",600,500,fScale3,D3DCOLOR_XRGB(255,0,0));
	else
	{
		float fScale;
		if(vSavedData[0].nLevel == 0 && vSavedData[1].nLevel == 0)
			fScale = fScale4;
		else if(vSavedData[1].nLevel == 0)
			fScale = fScale5;
		else
			fScale = fScale6;
		font->Print("Save 3",600,500,fScale3,D3DCOLOR_XRGB(255,0,0));
		font->Print("Delete",600,550,fScale,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[2].szName,600,250,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[2].nLevel,buffer,10);
		font->Print(buffer,600,275,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[2].nMoney,buffer,10);
		font->Print(buffer,600,300,0.75f,D3DCOLOR_XRGB(255,0,0));
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

		if(gameData->Attribute("machinegun", &info.nMachineGun) == nullptr)
			info.nMachineGun = 0;

		strcpy_s(info.szFileName,32,szFileName);

		vSavedData[nGameData] = info;

		

	return true;
}

