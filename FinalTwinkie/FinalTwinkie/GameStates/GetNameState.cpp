#include "GetNameState.h"
#include "SurvivalState.h"
#include "../Headers/Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "../GameObjects/Player.h"
#include "../GameStates/SurvivalState.h"
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
	m_bSurvival = false;
	m_nCount = 0;
	m_nPos = 0;
}

CGetNameState::~CGetNameState(void)
{
}

void CGetNameState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pAudio=CSGD_XAudio2::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));

	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));

	m_bLowCase = false;
	m_nCount = 0;
	for(int i = 0; i < 32; ++i)
		szName[i] = 0;

	m_nPos = 0;
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

	for(int i = 0; i < 32; ++i)
		szName[i] = 0;

	m_nPos = 0;
}

bool CGetNameState::Input(void)
{
	// Exit the game when the user presses esc
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(0) || (m_nMouseX >= 538 && m_nMouseX <= 622 && m_nMouseY >= 525 && m_nMouseY <= 565 && m_pDI->MouseButtonPressed(0)))
	{
		szName[m_nCount] = 0;
		if(m_nCount == 0)
			strcpy_s(szName,32,"Player\0");		
		CPlayer::GetInstance()->SetName(szName);		
		if(!m_bSurvival)
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		else
			CGame::GetInstance()->ChangeState(CSurvivalState::GetInstance());
		return true;
	}

	if(m_pDI->KeyPressed(DIK_A) || (m_nMouseX >= 175 && m_nMouseX <= 215 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(65);
		else
			szName[m_nCount] = char(97);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_B) || (m_nMouseX >= 400 && m_nMouseX <= 440 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(66);
		else
			szName[m_nCount] = char(98);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_C) || (m_nMouseX >= 300 && m_nMouseX <= 340 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(67);
		else
			szName[m_nCount] = char(99);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_D) || (m_nMouseX >= 275 && m_nMouseX <= 315 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(68);
		else
			szName[m_nCount] = char(100);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_E) || (m_nMouseX >= 250 && m_nMouseX <= 290 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(69);
		else
			szName[m_nCount] = char(101);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_F) || (m_nMouseX >= 325 && m_nMouseX <= 365 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(70);
		else
			szName[m_nCount] = char(102);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_G) || (m_nMouseX >= 375 && m_nMouseX <= 415 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(71);
		else
			szName[m_nCount] = char(103);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_H) || (m_nMouseX >= 425 && m_nMouseX <= 465 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(72);
		else
			szName[m_nCount] = char(104);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_I) || (m_nMouseX >= 500 && m_nMouseX <= 540 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(73);
		else
			szName[m_nCount] = char(105);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_J) || (m_nMouseX >= 475 && m_nMouseX <= 515 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(74);
		else
			szName[m_nCount] = char(106);
		m_nCount++;
		if(m_nCount >= 10)
		m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_K) || (m_nMouseX >= 525 && m_nMouseX <= 565 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(75);
		else
			szName[m_nCount] = char(107);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_L) || (m_nMouseX >= 575 && m_nMouseX <= 615 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(76);
		else
			szName[m_nCount] = char(108);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_M) || (m_nMouseX >= 500 && m_nMouseX <= 540 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(77);
		else
			szName[m_nCount] = char(109);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_N)  || (m_nMouseX >= 450 && m_nMouseX <= 490 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(78);
		else
			szName[m_nCount] = char(110);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_O) || (m_nMouseX >= 550 && m_nMouseX <= 590 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(79);
		else
			szName[m_nCount] = char(111);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_P) || (m_nMouseX >= 600 && m_nMouseX <= 640 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(80);
		else
			szName[m_nCount] = char(112);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Q) || (m_nMouseX >= 150 && m_nMouseX <= 190 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(81);
		else
			szName[m_nCount] = char(113);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_R) || (m_nMouseX >= 300 && m_nMouseX <= 340 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(82);
		else
			szName[m_nCount] = char(114);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_S) || (m_nMouseX >= 225 && m_nMouseX <= 265 && m_nMouseY >= 425 && m_nMouseY <= 465 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(83);
		else
			szName[m_nCount] = char(115);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_T) || (m_nMouseX >= 350 && m_nMouseX <= 390 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(84);
		else
			szName[m_nCount] = char(116);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_U) || (m_nMouseX >= 450 && m_nMouseX <= 490 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(85);
		else
			szName[m_nCount] = char(117);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_V) || (m_nMouseX >= 350 && m_nMouseX <= 390 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(86);
		else
			szName[m_nCount] = char(118);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_W) || (m_nMouseX >= 200 && m_nMouseX <= 240 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(87);
		else
			szName[m_nCount] = char(119);
		m_nCount++;
		if(m_nCount >= 10)
		m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_X) || (m_nMouseX >= 250 && m_nMouseX <= 290 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(88);
		else
			szName[m_nCount] = char(120);
		m_nCount++;
		if(m_nCount >= 10)
		m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Y) || (m_nMouseX >= 400 && m_nMouseX <= 440 && m_nMouseY >= 375 && m_nMouseY <= 415 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(89);
		else
			szName[m_nCount] = char(121);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_Z) || (m_nMouseX >= 200 && m_nMouseX <= 240 && m_nMouseY >= 475 && m_nMouseY <= 515 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		if(m_bLowCase == false)
			szName[m_nCount] = char(90);
		else
			szName[m_nCount] = char(122);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
		m_bLowCase = true; 
	}
	if(m_pDI->KeyPressed(DIK_LSHIFT) || m_pDI->KeyPressed(DIK_RSHIFT) || (m_nMouseX >= 155 && m_nMouseX <= 250 && m_nMouseY >= 525 && m_nMouseY <= 565 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		m_bLowCase = !m_bLowCase;
	}
	if(m_pDI->KeyReleased(DIK_LSHIFT) || m_pDI->KeyReleased(DIK_RSHIFT))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		m_bLowCase = !m_bLowCase;
	}
	if(m_pDI->KeyPressed(DIK_BACK) || (m_nMouseX >= 365 && m_nMouseX <= 528 && m_nMouseY >= 525 && m_nMouseY <= 565 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		szName[m_nCount] = char(32);
		if(m_nCount == 0)
			m_bLowCase = false;
		m_nCount--;
		if(m_nCount <= 0)
			m_nCount = 0;
	}
	if(m_pDI->KeyPressed(DIK_SPACE) || (m_nMouseX >= 260 && m_nMouseX <= 355 && m_nMouseY >= 525 && m_nMouseY <= 565 && m_pDI->MouseButtonPressed(0)))
	{
		m_pAudio->SFXPlaySound(m_nClick);
		szName[m_nCount] = char(32);
		m_nCount++;
		if(m_nCount >= 10)
			m_nCount = 10;
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

	if(m_nMouseX >= 538 && m_nMouseX <= 622 && m_nMouseY >= 525 && m_nMouseY <= 565)
	{
		if(m_nPos!=30)
			m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 30; // enter
	}
	else if(m_nMouseX >= 175 && m_nMouseX <= 215 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=11)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 11;
	}
	else if(m_nMouseX >= 400 && m_nMouseX <= 440 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=24)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 24;
	}
	else if(m_nMouseX >= 300 && m_nMouseX <= 340 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=22)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 22;
	}
	else if(m_nMouseX >= 275 && m_nMouseX <= 315 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=13)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=13;
	}
	else if(m_nMouseX >= 250 && m_nMouseX <= 290 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=3)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=3;
	}
	else if(m_nMouseX >= 325 && m_nMouseX <= 365 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=14)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=14;
	}
	else if(m_nMouseX >= 375 && m_nMouseX <= 415 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=15)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=15;
	}
	else if(m_nMouseX >= 425 && m_nMouseX <= 465 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=16)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=16;
	}
	else if(m_nMouseX >= 500 && m_nMouseX <= 540 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=8)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=8;
	}
	else if(m_nMouseX >= 475 && m_nMouseX <= 515 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=17)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos=17;
	}
	else if(m_nMouseX >= 525 && m_nMouseX <= 565 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=18)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 18;
	}
	else if(m_nMouseX >= 575 && m_nMouseX <= 615 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=19)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 19;
	}
	else if(m_nMouseX >= 500 && m_nMouseX <= 540 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=26)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 26;
	}
	else if(m_nMouseX >= 450 && m_nMouseX <= 490 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=25)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 25;
	}
	else if(m_nMouseX >= 550 && m_nMouseX <= 590 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=9)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 9;
	}
	else if(m_nMouseX >= 600 && m_nMouseX <= 640 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=10)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 10;
	}
	else if(m_nMouseX >= 150 && m_nMouseX <= 190 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=1)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 1;
	}
	else if(m_nMouseX >= 300 && m_nMouseX <= 340 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=4)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 4;
	}
	else if(m_nMouseX >= 225 && m_nMouseX <= 265 && m_nMouseY >= 425 && m_nMouseY <= 465)
	{
		if(m_nPos!=12)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 12;
	}
	else if(m_nMouseX >= 350 && m_nMouseX <= 390 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=5)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 5;
	}
	else if(m_nMouseX >= 450 && m_nMouseX <= 490 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=7)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 7;
	}
	else if(m_nMouseX >= 350 && m_nMouseX <= 390 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=23)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 23;
	}
	else if(m_nMouseX >= 200 && m_nMouseX <= 240 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=2)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 2;
	}
	else if(m_nMouseX >= 250 && m_nMouseX <= 290 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=21)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 21;
	}
	else if(m_nMouseX >= 400 && m_nMouseX <= 440 && m_nMouseY >= 375 && m_nMouseY <= 415)
	{
		if(m_nPos!=6)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 6;
	}
	else if(m_nMouseX >= 200 && m_nMouseX <= 240 && m_nMouseY >= 475 && m_nMouseY <= 515)
	{
		if(m_nPos!=20)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 20;
	}
	else if(m_nMouseX >= 155 && m_nMouseX <= 250 && m_nMouseY >= 525 && m_nMouseY <= 565)
	{
		if(m_nPos!=27)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 27;
	}
	else if(m_nMouseX >= 365 && m_nMouseX <= 528 && m_nMouseY >= 525 && m_nMouseY <= 565)
	{
		if(m_nPos!=29)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 29;
	}
	else if(m_nMouseX >= 260 && m_nMouseX <= 355 && m_nMouseY >= 525 && m_nMouseY <= 565)
	{
		if(m_nPos!=28)
		m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPos = 28;
	}
	else
		m_nPos = 0;
}

void CGetNameState::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);

	SetRect(&rSelf, 467, 638, 631, 760);
	m_pTM->Draw(m_nBGImageID,238,215,2.0,0.5f,&rSelf,0,0,0);
		

	DWORD dColor0,dColor1,dColor2,dColor3,dColor4,dColor5,dColor6,dColor7,dColor8,dColor9,
		  dColor10,dColor11,dColor12,dColor13,dColor14,dColor15,dColor16,dColor17,dColor18,dColor19,
		  dColor20,dColor21,dColor22,dColor23,dColor24,dColor25,dColor26,dColor27,dColor28,dColor29,
		  dColor30;
	switch(m_nPos)
	{
	case 0:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 1:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(177,132,0);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 2:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(177,132,0);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 3:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(177,132,0);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 4:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(177,132,0);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 5:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(177,132,0);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 6:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(177,132,0);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 7:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(177,132,0);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 8:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(177,132,0);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 9:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(177,132,0);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 10:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(177,132,0);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 11:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(177,132,0);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 12:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(177,132,0);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 13:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(177,132,0);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 14:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(177,132,0);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 15:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(177,132,0);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 16:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(177,132,0);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 17:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(177,132,0);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 18:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(177,132,0);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 19:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(177,132,0);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 20:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(177,132,0);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 21:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(177,132,0);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 22:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(177,132,0);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 23:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(177,132,0);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 24:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(177,132,0);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 25:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(177,132,0);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 26:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(177,132,0);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 27:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(177,132,0);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 28:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(177,132,0);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 29:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(177,132,0);
			dColor30 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 30:
		{
			 dColor0 = D3DCOLOR_XRGB(255,255,255);
			 dColor1 = D3DCOLOR_XRGB(255,255,255);
			 dColor2 = D3DCOLOR_XRGB(255,255,255);
			 dColor3 = D3DCOLOR_XRGB(255,255,255);
			 dColor4 = D3DCOLOR_XRGB(255,255,255);
			 dColor5 = D3DCOLOR_XRGB(255,255,255);
			 dColor6 = D3DCOLOR_XRGB(255,255,255);
			 dColor7 = D3DCOLOR_XRGB(255,255,255);
			 dColor8 = D3DCOLOR_XRGB(255,255,255);
			 dColor9 = D3DCOLOR_XRGB(255,255,255);
			dColor10 = D3DCOLOR_XRGB(255,255,255);
			dColor11 = D3DCOLOR_XRGB(255,255,255);
			dColor12 = D3DCOLOR_XRGB(255,255,255);
			dColor13 = D3DCOLOR_XRGB(255,255,255);
			dColor14 = D3DCOLOR_XRGB(255,255,255);
			dColor15 = D3DCOLOR_XRGB(255,255,255);
			dColor16 = D3DCOLOR_XRGB(255,255,255);
			dColor17 = D3DCOLOR_XRGB(255,255,255);
			dColor18 = D3DCOLOR_XRGB(255,255,255);
			dColor19 = D3DCOLOR_XRGB(255,255,255);
			dColor20 = D3DCOLOR_XRGB(255,255,255);
			dColor21 = D3DCOLOR_XRGB(255,255,255);
			dColor22 = D3DCOLOR_XRGB(255,255,255);
			dColor23 = D3DCOLOR_XRGB(255,255,255);
			dColor24 = D3DCOLOR_XRGB(255,255,255);
			dColor25 = D3DCOLOR_XRGB(255,255,255);
			dColor26 = D3DCOLOR_XRGB(255,255,255);
			dColor27 = D3DCOLOR_XRGB(255,255,255);
			dColor28 = D3DCOLOR_XRGB(255,255,255);
			dColor29 = D3DCOLOR_XRGB(255,255,255);
			dColor30 = D3DCOLOR_XRGB(177,132,0);
		}
		break;
	}
	

	m_pTM->Draw(m_nButtonImageID,150,375,0.20f,0.75f,nullptr,0,0,0, dColor1);
	m_pTM->Draw(m_nButtonImageID,200,375,0.20f,0.75f,nullptr,0,0,0, dColor2);
	m_pTM->Draw(m_nButtonImageID,250,375,0.20f,0.75f,nullptr,0,0,0, dColor3);
	m_pTM->Draw(m_nButtonImageID,300,375,0.20f,0.75f,nullptr,0,0,0, dColor4);
	m_pTM->Draw(m_nButtonImageID,350,375,0.20f,0.75f,nullptr,0,0,0, dColor5);
	m_pTM->Draw(m_nButtonImageID,400,375,0.20f,0.75f,nullptr,0,0,0, dColor6);
	m_pTM->Draw(m_nButtonImageID,450,375,0.20f,0.75f,nullptr,0,0,0, dColor7);
	m_pTM->Draw(m_nButtonImageID,500,375,0.20f,0.75f,nullptr,0,0,0, dColor8);
	m_pTM->Draw(m_nButtonImageID,550,375,0.20f,0.75f,nullptr,0,0,0, dColor9);
	m_pTM->Draw(m_nButtonImageID,600,375,0.20f,0.75f,nullptr,0,0,0,dColor10);
	m_pTM->Draw(m_nButtonImageID,175,425,0.20f,0.75f,nullptr,0,0,0,dColor11);
	m_pTM->Draw(m_nButtonImageID,225,425,0.20f,0.75f,nullptr,0,0,0,dColor12);
	m_pTM->Draw(m_nButtonImageID,275,425,0.20f,0.75f,nullptr,0,0,0,dColor13);
	m_pTM->Draw(m_nButtonImageID,325,425,0.20f,0.75f,nullptr,0,0,0,dColor14);
	m_pTM->Draw(m_nButtonImageID,375,425,0.20f,0.75f,nullptr,0,0,0,dColor15);
	m_pTM->Draw(m_nButtonImageID,425,425,0.20f,0.75f,nullptr,0,0,0,dColor16);
	m_pTM->Draw(m_nButtonImageID,475,425,0.20f,0.75f,nullptr,0,0,0,dColor17);
	m_pTM->Draw(m_nButtonImageID,525,425,0.20f,0.75f,nullptr,0,0,0,dColor18);
	m_pTM->Draw(m_nButtonImageID,575,425,0.20f,0.75f,nullptr,0,0,0,dColor19);
	m_pTM->Draw(m_nButtonImageID,200,475,0.20f,0.75f,nullptr,0,0,0,dColor20);
	m_pTM->Draw(m_nButtonImageID,250,475,0.20f,0.75f,nullptr,0,0,0,dColor21);
	m_pTM->Draw(m_nButtonImageID,300,475,0.20f,0.75f,nullptr,0,0,0,dColor22);
	m_pTM->Draw(m_nButtonImageID,350,475,0.20f,0.75f,nullptr,0,0,0,dColor23);
	m_pTM->Draw(m_nButtonImageID,400,475,0.20f,0.75f,nullptr,0,0,0,dColor24);
	m_pTM->Draw(m_nButtonImageID,450,475,0.20f,0.75f,nullptr,0,0,0,dColor25);
	m_pTM->Draw(m_nButtonImageID,500,475,0.20f,0.75f,nullptr,0,0,0,dColor26);
	m_pTM->Draw(m_nButtonImageID,155,525,0.45f,0.75f,nullptr,0,0,0,dColor27);
	m_pTM->Draw(m_nButtonImageID,260,525,0.45f,0.75f,nullptr,0,0,0,dColor28);
	m_pTM->Draw(m_nButtonImageID,365,525,0.75f,0.75f,nullptr,0,0,0,dColor29);
	m_pTM->Draw(m_nButtonImageID,538,525,0.45f,0.75f,nullptr,0,0,0,dColor30);

	m_pD3D->GetSprite()->Flush();
	if(m_bLowCase == false)
	{
		font->Print("Q",165,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("W",207,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("E",262,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("R",312,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("T",362,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("Y",412,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("U",462,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("I",518,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("O",565,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("P",615,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("A",190,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("S",240,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("D",290,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("F",340,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("G",390,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("H",437,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("J",490,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("K",537,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("L",590,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("Z",215,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("X",262,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("C",313,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("V",362,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("B",412,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("N",462,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("M",512,480,1.0f,D3DCOLOR_XRGB(177,132,0));
	}
	else
	{
		font->Print("q",165,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("w",215,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("e",265,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("r",315,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("t",365,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("y",415,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("u",465,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("i",518,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("o",565,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("p",615,380,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("a",190,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("s",240,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("d",290,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("f",340,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("g",390,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("h",440,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("j",490,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("k",540,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("l",590,430,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("z",215,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("x",265,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("c",315,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("v",365,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("b",415,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("n",465,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print("m",515,480,1.0f,D3DCOLOR_XRGB(177,132,0));
	}

	font->Print("Shift",168,530,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Space",272,530,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Backspace",380,530,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Enter",548,530,1.0f,D3DCOLOR_XRGB(177,132,0));

	font->Print("Enter your name: ",145,100,2.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print(szName,263,225,1.25f,D3DCOLOR_XRGB(177,132,0));

	char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(177,132,0));

	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
}
