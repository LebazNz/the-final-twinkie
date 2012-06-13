#include "LoadOutState.h"
#include "OptionsState.h"
#include "GamePlayState.h"
#include "ShopState.h"
#include "../Headers/Game.h"
#include "../PickUps and Specials/AirStrike.h"
#include "../PickUps and Specials/EMP.h"
#include "../PickUps and Specials/Nuke.h"
#include "../PickUps and Specials/Reinforcements.h"
#include "../PickUps and Specials/Smoke.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"

CLoadOutState* CLoadOutState::m_pSelf = nullptr;

CLoadOutState::CLoadOutState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_pPlayer = nullptr;
	m_PM = nullptr;

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

	m_bMissile		= false;
	m_bArtillery	= false;
	m_bLaser		= false;
	m_bFlame		= false;
	m_bNuke			= false;
	m_bSmoke		= false;
	m_bEMP			= false;
	m_bAirStirke	= false;
	m_bRF			= false;

	m_bUseMachineGun	= true;
	m_bUseLaser			= false;
	m_bUseFlame			= false;

	m_pSpecialOne = nullptr;
	m_pSpecialTwo = nullptr;

	m_nSpecialCount = 0;
	m_nSpecialPos1 = 0;
	m_nSpecialPos2 = 0;
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
	m_pFont = CBitmapFont::GetInstance();
	m_pPlayer = CPlayer::GetInstance();
	m_PM = CParticleManager::GetInstance();
	m_pAudio=CSGD_XAudio2::GetInstance();

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
	m_bNuke			=	m_pPlayer->GetNukeAccess();
	m_bSmoke		=	m_pPlayer->GetSmokeBombAccess();
	m_bEMP			=	m_pPlayer->GetEMPAccess();
	m_bAirStirke	=	m_pPlayer->GetAirStrikeAccess();
	m_nSecondAmmo = m_pPlayer->GetSecondType();
	m_bRF = true;

	m_nShellMaxCount		= m_nShellCount;
	m_nMissileMaxCount		= m_nMissileCount;
	m_nArtilleryMaxCount	= m_nArtilleryCount;

	m_pSpecialOne = m_pPlayer->GetSpecial1();
	m_pSpecialTwo = m_pPlayer->GetSpecial2();

	if(m_nSecondAmmo == 0)
	{
		m_bUseMachineGun = true;
		m_bUseLaser = false;
		m_bUseFlame = false;
	}
	else if(m_nSecondAmmo == 1)
	{
		m_bUseMachineGun = false;
		m_bUseLaser = true;
		m_bUseFlame = false;
	}
	else if(m_nSecondAmmo == 2)
	{
		m_bUseMachineGun = false;
		m_bUseLaser = false;
		m_bUseFlame = true;
	}

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

	m_nSpecialCount = 0;
	m_nSpecialPos1 = m_pSpecialOne->GetType();
	m_nSpecialPos2 = m_pSpecialTwo->GetType();

	if(m_bNuke)
		m_nSpecialCount += 1;
	if(m_bSmoke)
		m_nSpecialCount += 1;
	if(m_bEMP)
		m_nSpecialCount += 1;
	if(m_bAirStirke)
		m_nSpecialCount += 1;
	if(m_bRF)
		m_nSpecialCount += 1;	

	m_vSpCount.clear();
	m_vSpCount.push_back(SPECIAL);	
	if(m_bSmoke)
		m_vSpCount.push_back(SMOKE);
	else
		m_vSpCount.push_back(-1);
	if(m_bEMP)
		m_vSpCount.push_back(EMP);
	else
		m_vSpCount.push_back(-1);
	if(m_bNuke)
		m_vSpCount.push_back(NUKE);
	else
		m_vSpCount.push_back(-1);
	if(m_bRF)
		m_vSpCount.push_back(REINFORCE);
	if(m_bAirStirke)
		m_vSpCount.push_back(AIRSTRIKE);
	else
		m_vSpCount.push_back(-1);

	LoadText();
	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));
}

void CLoadOutState::Exit( void )
{
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
	m_PM = nullptr;
	
	m_pSpecialOne = nullptr;
	m_pSpecialTwo = nullptr;

	m_nPosition = 0;
}

bool CLoadOutState::Input( void )
{
	/*if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		return true;
	}*/
	// Back/Continue
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 25 && m_nMouseX <= 193
		&& m_nMouseY >= 550 && m_nMouseY <= 575))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		CGame::GetInstance()->ChangeState(CShopState::GetInstance());
		return true;
	}
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 600 && m_nMouseX <= 768
		&& m_nMouseY >= 550 && m_nMouseY <= 575))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		m_pPlayer->SetWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);
		m_pPlayer->SetMaxWeaponAmmo(m_nShellCount,m_nArtilleryCount,m_nMissileCount);
		m_pPlayer->SetSecondType(m_nSecondAmmo);
		switch(m_vSpCount[m_nSpecialPos1])
		{
		case 0:
			{
				CSpecial* pSpecial = new CSpecial;
				m_pPlayer->SetSpecial1(pSpecial);
			}
			break;
		case 1:
			{
				CSmoke* pSpecial = new CSmoke;
				pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
				m_pPlayer->SetSpecial1(pSpecial);
				m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 2:
			{
				CEMP* pSpecial = new CEMP;
				m_pPlayer->SetSpecial1(pSpecial);
				m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 3:
			{
				CNuke* pSpecial = new CNuke;
				pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
				m_pPlayer->SetSpecial1(pSpecial);
				m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 4:
			{
				CReinforcements* pSpecial = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial);
				m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 5:
			{
				CAirStrike* pSpecial = new CAirStrike;
				m_pPlayer->SetSpecial1(pSpecial);
				m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
			}
			break;
		default:
			{
				CSpecial* pSpecial = new CSpecial;
				m_pPlayer->SetSpecial1(pSpecial);
			}
			break;
		}
		switch(m_vSpCount[m_nSpecialPos2])
		{
		case 0:
			{
				CSpecial* pSpecial = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial);
			}
			break;
		case 1:
			{
				CSmoke* pSpecial = new CSmoke;
				pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
				m_pPlayer->SetSpecial2(pSpecial);
				m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 2:
			{
				CEMP* pSpecial = new CEMP;
				m_pPlayer->SetSpecial2(pSpecial);
				m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 3:
			{
				CNuke* pSpecial = new CNuke;
				pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
				m_pPlayer->SetSpecial2(pSpecial);
				m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 4:
			{
				CReinforcements* pSpecial = new CReinforcements;
				m_pPlayer->SetSpecial2(pSpecial);
				m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
			}
			break;
		case 5:
			{
				CAirStrike* pSpecial = new CAirStrike;
				m_pPlayer->SetSpecial2(pSpecial);
				m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
			}
			break;
		default:
			{
				CSpecial* pSpecial = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial);
			}
			break;
		}
		return true;
	}

	// Ammo counts
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 84 && m_nMouseX <= 121
		&& m_nMouseY >= 225 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nShellCount > 0)
			m_nShellCount--;
		else
			m_nShellCount = 0;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 195 && m_nMouseX <= 225
		&& m_nMouseY >= 228 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nShellCount < m_nShellMaxCount)
			m_nShellCount++;
		else
			m_nShellCount = m_nShellMaxCount;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 267 && m_nMouseX <= 301
		&& m_nMouseY >= 225 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nMissileCount > 0)
			m_nMissileCount--;
		else
			m_nMissileCount = 0;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 374 && m_nMouseX <= 409
		&& m_nMouseY >= 228 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nMissileCount < m_nMissileMaxCount)
			m_nMissileCount++;
		else
			m_nMissileCount = m_nMissileMaxCount;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 432 && m_nMouseX <= 467
		&& m_nMouseY >= 225 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nArtilleryCount > 0)
			m_nArtilleryCount--;
		else
			m_nArtilleryCount = 0;
	}

	// Second Weapon type
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 537 && m_nMouseX <= 570
		&& m_nMouseY >= 228 && m_nMouseY <= 253))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_nArtilleryCount < m_nArtilleryMaxCount)
			m_nArtilleryCount++;
		else
			m_nArtilleryCount = m_nArtilleryMaxCount;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 143 && m_nMouseX <= 253
		&& m_nMouseY >= 349 && m_nMouseY <= 378))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		if(m_bUseMachineGun != true)
		{
			m_bUseMachineGun = true;
			m_bUseLaser = false;
			m_bUseFlame = false;
		}
		m_nSecondAmmo = 0;
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 303 && m_nMouseX <= 415
		&& m_nMouseY >= 349 && m_nMouseY <= 378))
	{
		if(CPlayer::GetInstance()->GetLaserAccess())
		{
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(m_bUseLaser != true)
			{
				m_bUseMachineGun = false;
				m_bUseLaser = true;
				m_bUseFlame = false;
			}
			m_nSecondAmmo = 1;
		}
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 479 && m_nMouseX <= 592
		&& m_nMouseY >= 349 && m_nMouseY <= 378))
	{
		if(CPlayer::GetInstance()->GetFlamerAccess())
		{
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(m_bUseFlame != true)
			{
				m_bUseMachineGun = false;
				m_bUseLaser = false;
				m_bUseFlame = true;
			}
			m_nSecondAmmo = 2;
		}
	}

	//Specials
	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 84 && m_nMouseX <= 118
		&& m_nMouseY >= 446 && m_nMouseY <= 474))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		m_nSpecialPos1 -= 1;

		if(m_nSpecialPos1 < 0)
			m_nSpecialPos1 = m_nSpecialCount;

		if(m_nSpecialPos1 == m_nSpecialPos2 && m_nSpecialPos1 != 0)
		{
			m_nSpecialPos1 -= 1;
			if(m_nSpecialPos1 < 0)
				m_nSpecialPos1 = m_nSpecialCount;
		}
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 253 && m_nMouseX <= 287
		&& m_nMouseY >= 446 && m_nMouseY <= 474))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		m_nSpecialPos1 += 1;

		if(m_nSpecialPos1 > m_nSpecialCount)
			m_nSpecialPos1 = 0;

		if(m_nSpecialPos1 == m_nSpecialPos2 && m_nSpecialPos1 != 0)
		{
			m_nSpecialPos1 += 1;
			if(m_nSpecialPos1 > m_nSpecialCount)
				m_nSpecialPos1 = 0;
		}
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 384 && m_nMouseX <= 419
		&& m_nMouseY >= 446 && m_nMouseY <= 474))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		m_nSpecialPos2 -= 1;

		if(m_nSpecialPos2 < 0)
			m_nSpecialPos2 = m_nSpecialCount;

		if(m_nSpecialPos1 == m_nSpecialPos2 && m_nSpecialPos2 != 0)
		{
			m_nSpecialPos2 -= 1;
			if(m_nSpecialPos2 < 0)
				m_nSpecialPos2 = m_nSpecialCount;
		}
	}

	if((m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0)) && (m_nMouseX >= 552 && m_nMouseX <= 587
		&& m_nMouseY >= 446 && m_nMouseY <= 474))
	{
		m_pAudio->SFXPlaySound(m_nClick, false);
		m_nSpecialPos2 += 1;

		if(m_nSpecialPos2 > m_nSpecialCount)
			m_nSpecialPos2 = 0;

		if(m_nSpecialPos1 == m_nSpecialPos2 && m_nSpecialPos2 != 0)
		{
			m_nSpecialPos2 += 1;
			if(m_nSpecialPos2 > m_nSpecialCount)
				m_nSpecialPos2 = 0;
		}
			
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
		
		if(m_nPosition!=1)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=1;
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

		if(m_nPosition!=2)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=2;
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

		if(m_nPosition!=3)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=3;
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

		if(m_nPosition!=4)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=4;
	}
	else if(m_nMouseX >= 267 && m_nMouseX <= 301
	&& m_nMouseY >= 225 && m_nMouseY <= 253)
	{		
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(177,132,0);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=5)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=5;
	}
	else if(m_nMouseX >= 374 && m_nMouseX <= 409
	&& m_nMouseY >= 228 && m_nMouseY <= 253)
	{
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(177,132,0);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=6)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=6;
	}
	else if(m_nMouseX >= 432 && m_nMouseX <= 467
	&& m_nMouseY >= 225 && m_nMouseY <= 253)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
		m_dShellMax =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(177,132,0);
		m_dArtilleryMax =	D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(255,255,255);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=7)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=7;
	}
	else if(m_nMouseX >= 537 && m_nMouseX <= 570
	&& m_nMouseY >= 228 && m_nMouseY <= 253)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
		m_dShellMax =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax =	D3DCOLOR_XRGB(177,132,0);
		m_dSPOneMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(255,255,255);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=8)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=8;
	}
	else if(m_nMouseX >= 143 && m_nMouseX <= 253
	&& m_nMouseY >= 349 && m_nMouseY <= 378)
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

		if(m_nPosition!=9)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=9;
	}
	else if(m_nMouseX >= 303 && m_nMouseX <= 415
	&& m_nMouseY >= 349 && m_nMouseY <= 378)
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

		if(m_nPosition!=10)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=10;
	}
	else if(m_nMouseX >= 479 && m_nMouseX <= 592
	&& m_nMouseY >= 349 && m_nMouseY <= 378)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
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

		if(m_nPosition!=11)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=11;
	}
	else if(m_nMouseX >= 84 && m_nMouseX <= 118
	&& m_nMouseY >= 446 && m_nMouseY <= 474)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
		m_dShellMax =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax =	D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin =		D3DCOLOR_XRGB(177,132,0);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(255,255,255);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=12)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=12;
	}
	else if(m_nMouseX >= 253 && m_nMouseX <= 287
	&& m_nMouseY >= 446 && m_nMouseY <= 474)
	{		
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(177,132,0);
		m_dSPTwoMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=13)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=13;
	}
	else if(m_nMouseX >= 384 && m_nMouseX <= 419
	&& m_nMouseY >= 446 && m_nMouseY <= 474)
	{
		m_dShellMin = D3DCOLOR_XRGB(255,255,255);
		m_dShellMax = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin = D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin = D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin = D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax = D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin = D3DCOLOR_XRGB(177,132,0);
		m_dSPTwoMax = D3DCOLOR_XRGB(255,255,255);
		m_dBack = D3DCOLOR_XRGB(255,255,255);
		m_dContinue = D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=14)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=14;
	}
	else if(m_nMouseX >= 552 && m_nMouseX <= 587
	&& m_nMouseY >= 446 && m_nMouseY <= 474)
	{
		m_dShellMin =		D3DCOLOR_XRGB(255,255,255);
		m_dShellMax =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMin =		D3DCOLOR_XRGB(255,255,255);
		m_dRocketMax =		D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMin =	D3DCOLOR_XRGB(255,255,255);
		m_dArtilleryMax =	D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPOneMax =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMin =		D3DCOLOR_XRGB(255,255,255);
		m_dSPTwoMax =		D3DCOLOR_XRGB(177,132,0);
		m_dBack =			D3DCOLOR_XRGB(255,255,255);
		m_dContinue =		D3DCOLOR_XRGB(255,255,255);

		if(m_nPosition!=15)
		{
			m_pAudio->SFXPlaySound(m_nButton,false);
		}

		m_nPosition=15;
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

		m_nPosition=0;
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
	// Specials
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

	font->Print(m_sLoad.c_str(),250,50,2.5f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sCannon.c_str(),50,150,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sShell.c_str(),125,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_nShellCount,buffer,10);
	font->Print(buffer,140,230,0.75f,D3DCOLOR_XRGB(255,255,255));

	font->Print(m_sRocket.c_str(),300,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	if(m_bMissile)
	{
		_itoa_s(m_nMissileCount,buffer,10);
		font->Print(buffer,320,230,0.75f,D3DCOLOR_XRGB(255,255,255));
	}
	font->Print(m_sArtillery.c_str(),450,190,0.9f,D3DCOLOR_XRGB(177,132,0));
	if(m_bArtillery)
	{
		_itoa_s(m_nArtilleryCount,buffer,10);
		font->Print(buffer,485,230,0.75f,D3DCOLOR_XRGB(255,255,255));
	}

	font->Print(m_sSecond.c_str(),50,275,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sMachine.c_str(),125,315,0.9f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sLaser.c_str(),300,315,0.9f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sFlame.c_str(),450,315,0.9f,D3DCOLOR_XRGB(177,132,0));

	font->Print(m_sSpecOne.c_str(),50,400,1.0f,D3DCOLOR_XRGB(177,132,0));

	switch(m_vSpCount[m_nSpecialPos1])
	{
	case 0:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sNone.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 1:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sSmoke.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 2:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sEMP.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 3:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sNuke.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 4:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sReinforce.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 5:
		{
			if(m_vSpCount[m_nSpecialPos1] != -1)
				font->Print(m_sAirStrike.c_str(),135,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	default:
		break;
	}


	font->Print(m_sSpecTwo.c_str(),350,400,1.0f,D3DCOLOR_XRGB(177,132,0));

	switch(m_vSpCount[m_nSpecialPos2])
	{
	case 0:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
				font->Print(m_sNone.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 1:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
				font->Print(m_sSmoke.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 2:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
				font->Print(m_sEMP.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 3:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
				font->Print(m_sNuke.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 4:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
				font->Print(m_sReinforce.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	case 5:
		{
			if(m_vSpCount[m_nSpecialPos2] != -1)
					font->Print(m_sAirStrike.c_str(),435,450,1.0f,D3DCOLOR_XRGB(177,132,0));
		}
		break;
	default:
		break;
	}

	font->Print(m_sBack.c_str(),75,555,1.0f,D3DCOLOR_XRGB(177,132,0));
	font->Print(m_sContinue.c_str(),625,555,1.0f,D3DCOLOR_XRGB(177,132,0));
	

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

void CLoadOutState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("LoadOutState");
				TiXmlNode* pButton = pState->FirstChild("Load");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton=pState->FirstChild("Cannon");
				pText = pButton->FirstChild()->ToText();
				m_sCannon=pText->Value();
				pButton=pState->FirstChild("Shell");
				pText = pButton->FirstChild()->ToText();
				m_sShell=pText->Value();
				pButton=pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket = pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton = pState->FirstChild("Second");
				pText = pButton->FirstChild()->ToText();
				m_sSecond=pText->Value();
				pButton=pState->FirstChild("Machine");
				pText = pButton->FirstChild()->ToText();
				m_sMachine=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton=pState->FirstChild("Flame");
				pText = pButton->FirstChild()->ToText();
				m_sFlame=pText->Value();
				pButton=pState->FirstChild("SpecOne");
				pText = pButton->FirstChild()->ToText();
				m_sSpecOne=pText->Value();
				pButton=pState->FirstChild("SpecTwo");
				pText = pButton->FirstChild()->ToText();
				m_sSpecTwo=pText->Value();
				pButton=pState->FirstChild("None");
				pText = pButton->FirstChild()->ToText();
				m_sNone=pText->Value();
				pButton=pState->FirstChild("Smoke");
				pText = pButton->FirstChild()->ToText();
				m_sSmoke=pText->Value();
				pButton=pState->FirstChild("EMP");
				pText = pButton->FirstChild()->ToText();
				m_sEMP=pText->Value();
				pButton=pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Reinforce");
				pText = pButton->FirstChild()->ToText();
				m_sReinforce=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("LoadOutState");
				TiXmlNode* pButton = pState->FirstChild("Load");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton=pState->FirstChild("Cannon");
				pText = pButton->FirstChild()->ToText();
				m_sCannon=pText->Value();
				pButton=pState->FirstChild("Shell");
				pText = pButton->FirstChild()->ToText();
				m_sShell=pText->Value();
				pButton=pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket = pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton = pState->FirstChild("Second");
				pText = pButton->FirstChild()->ToText();
				m_sSecond=pText->Value();
				pButton=pState->FirstChild("Machine");
				pText = pButton->FirstChild()->ToText();
				m_sMachine=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton=pState->FirstChild("Flame");
				pText = pButton->FirstChild()->ToText();
				m_sFlame=pText->Value();
				pButton=pState->FirstChild("SpecOne");
				pText = pButton->FirstChild()->ToText();
				m_sSpecOne=pText->Value();
				pButton=pState->FirstChild("SpecTwo");
				pText = pButton->FirstChild()->ToText();
				m_sSpecTwo=pText->Value();
				pButton=pState->FirstChild("None");
				pText = pButton->FirstChild()->ToText();
				m_sNone=pText->Value();
				pButton=pState->FirstChild("Smoke");
				pText = pButton->FirstChild()->ToText();
				m_sSmoke=pText->Value();
				pButton=pState->FirstChild("EMP");
				pText = pButton->FirstChild()->ToText();
				m_sEMP=pText->Value();
				pButton=pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Reinforce");
				pText = pButton->FirstChild()->ToText();
				m_sReinforce=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("LoadOutState");
				TiXmlNode* pButton = pState->FirstChild("Load");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton=pState->FirstChild("Cannon");
				pText = pButton->FirstChild()->ToText();
				m_sCannon=pText->Value();
				pButton=pState->FirstChild("Shell");
				pText = pButton->FirstChild()->ToText();
				m_sShell=pText->Value();
				pButton=pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket = pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton = pState->FirstChild("Second");
				pText = pButton->FirstChild()->ToText();
				m_sSecond=pText->Value();
				pButton=pState->FirstChild("Machine");
				pText = pButton->FirstChild()->ToText();
				m_sMachine=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton=pState->FirstChild("Flame");
				pText = pButton->FirstChild()->ToText();
				m_sFlame=pText->Value();
				pButton=pState->FirstChild("SpecOne");
				pText = pButton->FirstChild()->ToText();
				m_sSpecOne=pText->Value();
				pButton=pState->FirstChild("SpecTwo");
				pText = pButton->FirstChild()->ToText();
				m_sSpecTwo=pText->Value();
				pButton=pState->FirstChild("None");
				pText = pButton->FirstChild()->ToText();
				m_sNone=pText->Value();
				pButton=pState->FirstChild("Smoke");
				pText = pButton->FirstChild()->ToText();
				m_sSmoke=pText->Value();
				pButton=pState->FirstChild("EMP");
				pText = pButton->FirstChild()->ToText();
				m_sEMP=pText->Value();
				pButton=pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Reinforce");
				pText = pButton->FirstChild()->ToText();
				m_sReinforce=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("LoadOutState");
				TiXmlNode* pButton = pState->FirstChild("Load");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton=pState->FirstChild("Cannon");
				pText = pButton->FirstChild()->ToText();
				m_sCannon=pText->Value();
				pButton=pState->FirstChild("Shell");
				pText = pButton->FirstChild()->ToText();
				m_sShell=pText->Value();
				pButton=pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket = pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton = pState->FirstChild("Second");
				pText = pButton->FirstChild()->ToText();
				m_sSecond=pText->Value();
				pButton=pState->FirstChild("Machine");
				pText = pButton->FirstChild()->ToText();
				m_sMachine=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton=pState->FirstChild("Flame");
				pText = pButton->FirstChild()->ToText();
				m_sFlame=pText->Value();
				pButton=pState->FirstChild("SpecOne");
				pText = pButton->FirstChild()->ToText();
				m_sSpecOne=pText->Value();
				pButton=pState->FirstChild("SpecTwo");
				pText = pButton->FirstChild()->ToText();
				m_sSpecTwo=pText->Value();
				pButton=pState->FirstChild("None");
				pText = pButton->FirstChild()->ToText();
				m_sNone=pText->Value();
				pButton=pState->FirstChild("Smoke");
				pText = pButton->FirstChild()->ToText();
				m_sSmoke=pText->Value();
				pButton=pState->FirstChild("EMP");
				pText = pButton->FirstChild()->ToText();
				m_sEMP=pText->Value();
				pButton=pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Reinforce");
				pText = pButton->FirstChild()->ToText();
				m_sReinforce=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("Back");
				pText = pButton->FirstChild()->ToText();
				m_sBack=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		}
	}
}