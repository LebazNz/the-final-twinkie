#include "LoadOutState.h"
#include "OptionsState.h"
#include "GamePlayState.h"
#include "ShopState.h"
#include "../Headers/Game.h"

CLoadOutState* CLoadOutState::m_pSelf = nullptr;

CLoadOutState::CLoadOutState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_pPlayer = nullptr;

	m_nBGID = -1;
	m_nButtonImageID = -1;
	m_nPosition = 0;
	m_nMouseX = 0;
	m_nMouseY = 0;	
	m_nCursor = -1;
	m_nShellCount = 0;
	m_nMissileCount = 0;
	m_nArtilleryCount = 0;
	m_nShellMaxCount = 0;
	m_nMissileMaxCount = 0;
	m_nArtilleryMaxCount = 0;
	m_nSecondAmmo = -1;

	m_bMissile = false;
	m_bArtillery = false;
	m_bLaser = false;
	m_bFlame = false;
	m_bNuke = false;
	m_bSmoke = false;
	m_bEMP = false;
	m_bAirStirke = false;
}

CLoadOutState::~CLoadOutState(void)
{
}

CLoadOutState* CLoadOutState::GetInstance( void )
{
	if(m_pSelf == nullptr)
		m_pSelf = new CLoadOutState;
	return m_pSelf;
}

void CLoadOutState::DeleteInstance( void )
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CLoadOutState::Enter( void )
{
	m_pD3D	= CSGD_Direct3D::GetInstance();
	m_pDI	= CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFont = CBitmapFont::GetInstance();;
	m_pPlayer = CPlayer::GetInstance();

	m_nBGID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	m_nShellCount = m_pPlayer->GetMaxWeaponAmmoShell();
	m_nMissileCount = m_pPlayer->GetMaxWeaponAmmoMissile();
	m_nArtilleryCount = m_pPlayer->GetMaxWeaponAmmoArtillery();
	m_bMissile = m_pPlayer->GetRocketAccess();;
	m_bArtillery = m_pPlayer->GetArtilleryAccess();;
	m_bLaser = m_pPlayer->GetLaserAccess();
	m_bFlame = m_pPlayer->GetFlamerAccess();
	m_bNuke = m_pPlayer->GetNukeAccess();
	m_bSmoke = m_pPlayer->GetSmokeBombAccess();
	m_bEMP = m_pPlayer->GetEMPAccess();
	m_bAirStirke = m_pPlayer->GetAirStrikeAccess();
	m_nSecondAmmo = m_pPlayer->GetSecondType();

	m_nShellMaxCount		= m_nShellCount;
	m_nMissileMaxCount		= m_nMissileCount;
	m_nArtilleryMaxCount	= m_nArtilleryCount;

	m_dShellMin = D3DCOLOR_XRGB(255,255,255);
	m_dShellMax = D3DCOLOR_XRGB(255,255,255);
	m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
	m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
	m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
	m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
	m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
	m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
	m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
	m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
	m_dBack = D3DCOLOR_XRGB(255,255,255);
	m_dContinue = D3DCOLOR_XRGB(255,255,255);
}

void CLoadOutState::Exit( void )
{
	m_pPlayer->SetWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);
	m_pPlayer->SetMaxWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);

	if(m_nBGID != -1)
	{
		m_pTM->UnloadTexture(m_nBGID);
		m_nBGID = -1;
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

	m_nPosition = 0;
}

bool CLoadOutState::Input( void )
{
	/*if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		return true;
	}*/

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 25 && m_nMouseX <= 180
		&& m_nMouseY >= 550 && m_nMouseY <= 575))
	{
		CGame::GetInstance()->ChangeState(CShopState::GetInstance());
		return true;
	}
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 600 && m_nMouseX <= 755
		&& m_nMouseY >= 550 && m_nMouseY <= 575))
	{
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		m_pPlayer->SetWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);
		m_pPlayer->SetMaxWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);
		return true;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 88 && m_nMouseX <= 105
		&& m_nMouseY >= 226 && m_nMouseY <= 245))
	{
		if(m_nShellCount > 0)
			m_nShellCount--;
		else
			m_nShellCount = 0;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 195 && m_nMouseX <= 235
		&& m_nMouseY >= 226 && m_nMouseY <= 245))
	{
		if(m_nShellCount < m_nShellMaxCount)
			m_nShellCount++;
		else
			m_nShellCount = m_nShellMaxCount;
	}


	return true;
}

void CLoadOutState::Update( float fDt )
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

	if(m_nMouseX >= 25 && m_nMouseX <= 180
		&& m_nMouseY >= 550 && m_nMouseY <= 575)
	{		
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(177,132,0);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);
	}
	else if(m_nMouseX >= 600 && m_nMouseX <= 755
		&& m_nMouseY >= 550 && m_nMouseY <= 575)
	{
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(177,132,0);
	}
	else if(m_nMouseX >= 88 && m_nMouseX <= 105
		&& m_nMouseY >= 226 && m_nMouseY <= 245)
	{
		m_dShellMin =		D3DCOLOR_XRGB(177,132,0);
		m_dShellMax =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax =	D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(255,255,255);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);
	}
	else if(m_nMouseX >= 195 && m_nMouseX <= 235
		&& m_nMouseY >= 226 && m_nMouseY <= 245)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
		m_dShellMax =		D3DCOLOR_XRGB(177,132,0);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax =	D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(255,255,255);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);
	}
	else
	{
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);
	}
	
}

void CLoadOutState::Render( void )
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGID,0,0,1.0f,1.0f,&rSelf,0,0,0);

	DWORD dColor1, dColor2, dColor3;
	switch(m_nSecondAmmo)
	{
	case 0:
		{
			dColor1 = D3DCOLOR_XRGB(177,132,0);
			dColor2 = D3DCOLOR_XRGB(255,255,255);
			dColor3 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 1:
		{
			dColor1 = D3DCOLOR_XRGB(255,255,255);
			dColor2 = D3DCOLOR_XRGB(177,132,0);
			dColor3 = D3DCOLOR_XRGB(255,255,255);
		}
		break;
	case 2:
		{
			dColor1 = D3DCOLOR_XRGB(255,255,255);
			dColor2 = D3DCOLOR_XRGB(255,255,255);
			dColor3 = D3DCOLOR_XRGB(177,132,0);
		}
		break;
	}
	m_pTM->Draw(m_nButtonImageID,142,350,0.5f,0.5f,nullptr,0,0,0,dColor1);
	if(m_bLaser)
		m_pTM->Draw(m_nButtonImageID,303,350,0.5f,0.5f,nullptr,0,0,0,dColor2);
	if(m_bFlame)
		m_pTM->Draw(m_nButtonImageID,480,350,0.5f,0.5f,nullptr,0,0,0,dColor3);

	SetRect(&rSelf, 467, 638, 631, 760);
	// shell
	m_pTM->Draw(m_nBGID,125,225,0.4f,0.25f,&rSelf,0,0,0);
	// missile
	m_pTM->Draw(m_nBGID,305,225,0.4f,0.25f,&rSelf,0,0,0);
	// artillery
	m_pTM->Draw(m_nBGID,470,225,0.4f,0.25f,&rSelf,0,0,0);

	m_pTM->Draw(m_nBGID,125,440,0.75f,0.35f,&rSelf,0,0,0);
	m_pTM->Draw(m_nBGID,425,440,0.75f,0.35f,&rSelf,0,0,0);

	// shell
	m_pTM->Draw(m_nButtonImageID,88,226,0.15f,0.5f,nullptr,0,0,0,m_dShellMin);
	m_pTM->Draw(m_nButtonImageID,195,226,0.15f,0.5f,nullptr,0,0,0,m_dShellMax);
	// Missile
	if(m_bMissile)
	{
		m_pTM->Draw(m_nButtonImageID,268,226,0.15f,0.5f,nullptr,0,0,0,m_dRocketMin);
		m_pTM->Draw(m_nButtonImageID,375,226,0.15f,0.5f,nullptr,0,0,0,m_dRocketMax);
	}
	// Artillery
	if(m_bArtillery)
	{
		m_pTM->Draw(m_nButtonImageID,433,226,0.15f,0.5f,nullptr,0,0,0,m_dArtilleryMin);
		m_pTM->Draw(m_nButtonImageID,538,226,0.15f,0.5f,nullptr,0,0,0, m_dArtilleryMax);
	}
	// SP One
	m_pTM->Draw(m_nButtonImageID,85,447,0.15f,0.5f,nullptr,0,0,0,m_dSPOneMin);
	m_pTM->Draw(m_nButtonImageID,253,447,0.15f,0.5f,nullptr,0,0,0,m_dSPOneMax);
	// SP Two
	m_pTM->Draw(m_nButtonImageID,385,447,0.15f,0.5f,nullptr,0,0,0,m_dSPTwoMin);
	m_pTM->Draw(m_nButtonImageID,553,447,0.15f,0.5f,nullptr,0,0,0,m_dSPTwoMax);
	// Back/Continue
	m_pTM->Draw(m_nButtonImageID,25,550,0.75f,0.75f,nullptr,0,0,0,m_dBack);
	m_pTM->Draw(m_nButtonImageID,600,550,0.75f,0.75f,nullptr,0,0,0,m_dContinue);


	m_pD3D->GetSprite()->Flush();

	char buffer[10];

	font->Print("LoadOut",250,50,2.5f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Main Cannon Ammo",50,150,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Shell",125,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_nShellCount,buffer,10);
	font->Print(buffer,140,230,0.75f,D3DCOLOR_XRGB(255,255,255));

	font->Print("Rocket",300,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	if(m_bMissile)
	{
		_itoa_s(m_nMissileCount,buffer,10);
		font->Print(buffer,320,230,0.75f,D3DCOLOR_XRGB(255,255,255));
	}
	font->Print("Artillery",450,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	if(m_bArtillery)
	{
		_itoa_s(m_nArtilleryCount,buffer,10);
		font->Print(buffer,485,230,0.75f,D3DCOLOR_XRGB(255,255,255));
	}

	font->Print("Secondary Weapon Type",50,275,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Machine Gun",125,315,0.9f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Laser Gun",300,315,0.9f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Flamethrower",450,315,0.9f,D3DCOLOR_XRGB(177,132,0));

	font->Print("Special Weapon One",50,400,1.0f,D3DCOLOR_XRGB(177,132,0));

	font->Print("Special Weapon Two",350,400,1.0f,D3DCOLOR_XRGB(177,132,0));

	font->Print("Back",75,555,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print("Continue",625,555,1.0f,D3DCOLOR_XRGB(177,132,0));
	

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
