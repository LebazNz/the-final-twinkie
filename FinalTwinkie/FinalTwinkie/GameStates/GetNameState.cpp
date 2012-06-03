#include "GetNameState.h"

#include "../Headers/Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "../GameObjects/Player.h"

CGetNameState* CGetNameState::m_pSelf = nullptr;

CGetNameState* CGetNameState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGetNameState;
	return m_pSelf;
}

void CGetNameState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CGetNameState::CGetNameState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;

	m_nBGImageID = -1;
	m_nButtonImageID = -1;
	
	m_nMouseX = 0;
	m_nMouseY = 0;
	
	m_nCursor = -1;

	m_bLowCase = false;
	m_nCount = 0;
}

CGetNameState::~CGetNameState(void)
{
}

void CGetNameState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));

	m_bLowCase = false;
	m_nCount = 0;
}

void CGetNameState::Exit(void)
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

	m_bLowCase = false;
}

bool CGetNameState::Input(void)
{
	// Exit the game when the user presses esc
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
	{
		szName[m_nCount] = 0;
		CPlayer::GetInstance()->SetName(szName);
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		return true;
	}

	if(m_pDI->KeyPressed(DIK_A))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(65);
		else
			szName[m_nCount] = char(97);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_B))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(66);
		else
			szName[m_nCount] = char(98);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_C))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(67);
		else
			szName[m_nCount] = char(99);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_D))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(68);
		else
			szName[m_nCount] = char(100);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_E))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(69);
		else
			szName[m_nCount] = char(101);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_F))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(70);
		else
			szName[m_nCount] = char(102);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_G))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(71);
		else
			szName[m_nCount] = char(103);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_H))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(72);
		else
			szName[m_nCount] = char(104);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_I))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(73);
		else
			szName[m_nCount] = char(105);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_J))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(74);
		else
			szName[m_nCount] = char(106);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_K))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(75);
		else
			szName[m_nCount] = char(107);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_L))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(76);
		else
			szName[m_nCount] = char(108);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_M))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(77);
		else
			szName[m_nCount] = char(109);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_N))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(78);
		else
			szName[m_nCount] = char(110);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_O))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(79);
		else
			szName[m_nCount] = char(111);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_P))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(80);
		else
			szName[m_nCount] = char(112);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Q))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(81);
		else
			szName[m_nCount] = char(113);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_R))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(82);
		else
			szName[m_nCount] = char(114);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_S))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(83);
		else
			szName[m_nCount] = char(115);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_T))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(84);
		else
			szName[m_nCount] = char(116);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_U))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(85);
		else
			szName[m_nCount] = char(117);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_V))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(86);
		else
			szName[m_nCount] = char(118);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_W))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(87);
		else
			szName[m_nCount] = char(119);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_X))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(88);
		else
			szName[m_nCount] = char(120);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Y))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(89);
		else
			szName[m_nCount] = char(121);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Z))
	{
		if(m_bLowCase == false)
			szName[m_nCount] = char(90);
		else
			szName[m_nCount] = char(122);
		m_nCount++;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_LSHIFT) || m_pDI->KeyPressed(DIK_RSHIFT))
	{
		m_bLowCase = !m_bLowCase;
	}
	if(m_pDI->KeyPressed(DIK_BACK))
	{
		m_nCount--;
		szName[m_nCount] = char(32);
		if(m_nCount == 0)
			m_bLowCase = false;
	}
	if(m_pDI->KeyPressed(DIK_SPACE))
	{
		szName[m_nCount] = char(32);
		m_nCount++;
	}


	return true;
}

void CGetNameState::Update(float fDt)
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
}

void CGetNameState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);
		
	

	m_pTM->Draw(m_nButtonImageID,150,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,200,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,250,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,300,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,350,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,400,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,450,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,500,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,550,375,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,600,375,0.20f,0.75f,nullptr,0,0,0);

	m_pTM->Draw(m_nButtonImageID,175,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,225,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,275,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,325,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,375,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,425,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,475,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,525,425,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,575,425,0.20f,0.75f,nullptr,0,0,0);

	m_pTM->Draw(m_nButtonImageID,200,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,250,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,300,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,350,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,400,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,450,475,0.20f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,500,475,0.20f,0.75f,nullptr,0,0,0);

	m_pTM->Draw(m_nButtonImageID,155,525,0.45f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,260,525,0.45f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,365,525,0.75f,0.75f,nullptr,0,0,0);
	m_pTM->Draw(m_nButtonImageID,538,525,0.45f,0.75f,nullptr,0,0,0);

	m_pD3D->GetSprite()->Flush();
	if(m_bLowCase == false)
	{
		font->Print("Q",165,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("W",207,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("E",262,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("R",312,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("T",362,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("Y",412,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("U",462,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("I",518,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("O",565,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("P",615,380,1.0f,D3DCOLOR_XRGB(255,255,255));

		font->Print("A",190,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("S",240,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("D",290,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("F",340,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("G",390,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("H",437,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("J",490,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("K",537,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("L",590,430,1.0f,D3DCOLOR_XRGB(255,255,255));

		font->Print("Z",215,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("X",262,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("C",313,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("V",362,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("B",412,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("N",462,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("M",512,480,1.0f,D3DCOLOR_XRGB(255,255,255));
	}
	else
	{
		font->Print("q",165,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("w",215,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("e",265,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("r",315,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("t",365,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("y",415,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("u",465,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("i",518,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("o",565,380,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("p",615,380,1.0f,D3DCOLOR_XRGB(255,255,255));

		font->Print("a",190,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("s",240,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("d",290,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("f",340,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("g",390,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("h",440,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("j",490,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("k",540,430,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("l",590,430,1.0f,D3DCOLOR_XRGB(255,255,255));

		font->Print("z",215,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("x",265,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("c",315,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("v",365,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("b",415,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("n",465,480,1.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("m",515,480,1.0f,D3DCOLOR_XRGB(255,255,255));
	}

	font->Print("Shift",168,530,1.0f,D3DCOLOR_XRGB(255,255,255));
	font->Print("Space",272,530,1.0f,D3DCOLOR_XRGB(255,255,255));
	font->Print("Backspace",380,530,1.0f,D3DCOLOR_XRGB(255,255,255));
	font->Print("Enter",548,530,1.0f,D3DCOLOR_XRGB(255,255,255));

	font->Print(szName,200,200,1.0f,D3DCOLOR_XRGB(255,255,255));

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
