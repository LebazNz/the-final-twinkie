#include "LoadGameState.h"

#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "OptionsState.h"
#include "ShopState.h"
#include "GetNameState.h"
#include "../GameObjects/Player.h"
#include "../PickUps and Specials/AirStrike.h"
#include "../PickUps and Specials/EMP.h"
#include "../PickUps and Specials/Nuke.h"
#include "../PickUps and Specials/Reinforcements.h"
#include "../PickUps and Specials/Smoke.h"
#include "../PickUps and Specials/Special.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
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
	m_pAudio = nullptr;
	m_PM = nullptr;
	m_pPlayer = nullptr;
	
	m_nBGImageID = -1;
	m_nPosition = 0;
	m_nCount = 0;
	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nCursor = -1;
	m_nButtonImageID =-1;
	m_nMusic = -1;
}

CLoadGameState::~CLoadGameState(void)
{
}

void CLoadGameState::Enter(void)
{
	Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"blahblah",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pAudio = CSGD_XAudio2::GetInstance();
	m_pPlayer = CPlayer::GetInstance();
	m_PM = CParticleManager::GetInstance();
	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));

	FXSmoke=m_PM->AddEmitter("resource/files/Smoke.xml");
	FXNuke=m_PM->AddEmitter("resource/files/Nuke.xml");

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

	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));

	LoadText();
}

void CLoadGameState::Exit(void)
{
	if(m_nMusic != -1)
	{
		if(m_pAudio->MusicIsSongPlaying(m_nMusic))
			m_pAudio->MusicStopSong(m_nMusic);

		m_pAudio->MusicUnloadSong(m_nMusic);
		m_nMusic = -1;
		CMainMenuState::GetInstance()->SetSong(-1);
	}
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
	if(ARCADE == 0)
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
		m_pAudio->SFXPlaySound(m_nButton,false);
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
		m_pAudio->SFXPlaySound(m_nButton,false);
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
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame1.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						delete pSpecial;
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						delete pSpecial;
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
						
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 1)
		{
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame2.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 2)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame3.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
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
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 3)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame1.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame1.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
			else if(vSavedData[m_nPosition-1].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-1] = data;
				m_nCount--;
				m_nPosition-=1;
			}
		}
		else if(m_nPosition == 4)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
		}
		else if(m_nPosition == 5)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			remove("savedGame3.xml");
			Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			vSavedData[m_nPosition-3] = data;
			m_nCount--;
			m_nPosition-=3;			
		}
	}
	}
	else
	{
			// Exit the game when the user presses esc
		if(m_pDI->JoystickButtonPressed(6))
		{
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			return true;
		}

		// Move the cursor position
		if( m_pDI->JoystickGetLStickDirPressed(DIR_LEFT))
	{
		m_pAudio->SFXPlaySound(m_nButton,false);
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
	else if(m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT))
	{
		m_pAudio->SFXPlaySound(m_nButton,false);
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

	if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
	{
		if(m_nPosition == 0)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame1.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						
						
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						delete pSpecial;
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						delete pSpecial;
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
						
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(m_PM->GetEmitter(FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 1)
		{
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame2.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 2)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition].nLevel != 0)
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			else
			{
				strcpy_s(vSavedData[m_nPosition].szFileName,"savedGame3.xml");
				CGamePlayState::GetInstance()->SetSavedGame(vSavedData[m_nPosition]);
			}
			if(vSavedData[m_nPosition].nLevel == 0)
			{
				m_pPlayer->SetAirStrikeAccess(0);
				m_pPlayer->SetAmmoLevel(0);
				m_pPlayer->SetAlienBoss(0);
				m_pPlayer->SetAllUpgrades(0);
				m_pPlayer->SetAmmoMod(1);
				m_pPlayer->SetArmor(0);
				m_pPlayer->SetArmorLevel(0);
				m_pPlayer->SetArmorMod(1);
				m_pPlayer->SetArtilleryAccess(0);
				m_pPlayer->SetDamageMod(1);
				m_pPlayer->SetDamageLevel(0);
				m_pPlayer->SetEMPAccess(0);
				m_pPlayer->SetHealth(250);
				m_pPlayer->SetMaxHealth(250);
				m_pPlayer->SetArmor(50);
				m_pPlayer->SetMaxArmor(50);
				m_pPlayer->SetHealthLevel(0);
				m_pPlayer->SetHealthMod(1);
				m_pPlayer->SetHeatLevel(0);
				m_pPlayer->SetHeatModifier(1);
				m_pPlayer->SetIamBoss(0);
				m_pPlayer->SetLaserAccess(0);
				m_pPlayer->SetLevel(1);
				m_pPlayer->SetMaxWeaponAmmo(40,-1, -1);
				m_pPlayer->SetMoney(0);
				m_pPlayer->SetNaziBoss(0);
				m_pPlayer->SetNukeAccess(0);
				m_pPlayer->SetNukem(0);
				m_pPlayer->SetRobotBoss(0);
				m_pPlayer->SetRocketAccess(0);
				m_pPlayer->SetSapperAbsorb(0);
				m_pPlayer->SetScore(0);
				m_pPlayer->SetPurchaseLevel(0);
				m_pPlayer->SetSmokeBombAccess(0);
				m_pPlayer->SetSparta(0);
				m_pPlayer->SetSpeedLevel(0);
				m_pPlayer->SetSpeedMod(1);
				m_pPlayer->SetSecondType(0);
				m_pPlayer->SetFlamerAccess(0);
				CReinforcements* pSpecial2 = new CReinforcements;
				m_pPlayer->SetSpecial1(pSpecial2);
				m_pPlayer->SetSpecial1Ammo(pSpecial2->GetAmmoCount());
				CSpecial* pSpecial1 = new CSpecial;
				m_pPlayer->SetSpecial2(pSpecial1);	
				m_pPlayer->SetSpecial2Ammo(pSpecial1->GetAmmoCount());
				pSpecial1 = nullptr;
				pSpecial2 = nullptr;
				CGame::GetInstance()->ChangeState(CGetNameState::GetInstance());
				return true;
			}
			else
			{
				m_pPlayer->SetName(vSavedData[m_nPosition].szName);
				if(vSavedData[m_nPosition].bAirStrike == 0)
					m_pPlayer->SetAirStrikeAccess(false);
				else
					m_pPlayer->SetAirStrikeAccess(true);
				m_pPlayer->SetAmmoLevel(vSavedData[m_nPosition].nAmmoLevel);
				if(vSavedData[m_nPosition].bAlienBoss == 0)
					m_pPlayer->SetAlienBoss(false);
				else
					m_pPlayer->SetAlienBoss(true);
				if(vSavedData[m_nPosition].bAllUpgrades == 0)
					m_pPlayer->SetAllUpgrades(false);
				else
					m_pPlayer->SetAllUpgrades(true);
				m_pPlayer->SetAmmoMod(vSavedData[m_nPosition].fAmmoMod);
				m_pPlayer->SetArmor(float(vSavedData[m_nPosition].nArmor));
				m_pPlayer->SetArmorLevel(vSavedData[m_nPosition].nArmorLevel);
				m_pPlayer->SetArmorMod(vSavedData[m_nPosition].fArmorMod);
				if(vSavedData[m_nPosition].bArtillery == 0)
					m_pPlayer->SetArtilleryAccess(false);
				else
					m_pPlayer->SetArtilleryAccess(true);
				m_pPlayer->SetDamageMod(vSavedData[m_nPosition].fDamageMod);
				m_pPlayer->SetDamageLevel(vSavedData[m_nPosition].nDamageLevel);
				if(vSavedData[m_nPosition].bEMP == 0)
					m_pPlayer->SetEMPAccess(false);
				else
					m_pPlayer->SetEMPAccess(true);
				m_pPlayer->SetHealthLevel(vSavedData[m_nPosition].nHealthLevel);
				m_pPlayer->SetHealthMod(vSavedData[m_nPosition].fHealthMod);
				m_pPlayer->SetHeatLevel(vSavedData[m_nPosition].nHeatLevel);
				m_pPlayer->SetHeatModifier(vSavedData[m_nPosition].fHeatModifier);
				if(vSavedData[m_nPosition].bIamBoss == 0)
					m_pPlayer->SetIamBoss(false);
				else
					m_pPlayer->SetIamBoss(true);
				if(vSavedData[m_nPosition].nLaser == 0)
					m_pPlayer->SetLaserAccess(false);
				else
					m_pPlayer->SetLaserAccess(true);
				m_pPlayer->SetLevel(vSavedData[m_nPosition].nLevel);
				m_pPlayer->SetMaxWeaponAmmo(vSavedData[m_nPosition].nShellAmmo,vSavedData[m_nPosition].nArtilleryAmmo, vSavedData[m_nPosition].nMissileAmmo);
				m_pPlayer->SetMoney(vSavedData[m_nPosition].nMoney);
				if(vSavedData[m_nPosition].bNaziBoss == 0)
					m_pPlayer->SetNaziBoss(false);
				else
					m_pPlayer->SetNaziBoss(true);
				if(vSavedData[m_nPosition].bNuke == 0)
					m_pPlayer->SetNukeAccess(false);
				else
					m_pPlayer->SetNukeAccess(true);
				if(vSavedData[m_nPosition].bNukem == 0)
					m_pPlayer->SetNukem(false);
				else
					m_pPlayer->SetNukem(true);
				if(vSavedData[m_nPosition].bRobotBoss == 0)
					m_pPlayer->SetRobotBoss(false);
				else
					m_pPlayer->SetRobotBoss(true);
				if(vSavedData[m_nPosition].bMissile == 0)
					m_pPlayer->SetRocketAccess(false);
				else
					m_pPlayer->SetRocketAccess(true);
				if(vSavedData[m_nPosition].bSapperAbsorb == 0)
					m_pPlayer->SetSapperAbsorb(false);
				else
					m_pPlayer->SetSapperAbsorb(true);
				m_pPlayer->SetScore(vSavedData[m_nPosition].nScore);
				m_pPlayer->SetPurchaseLevel(vSavedData[m_nPosition].fPurchaseLevel);
				if(vSavedData[m_nPosition].bSmoke == 0)
					m_pPlayer->SetSmokeBombAccess(false);
				else
					m_pPlayer->SetSmokeBombAccess(true);
				if(vSavedData[m_nPosition].bSparta == 0)
					m_pPlayer->SetSparta(false);
				else
					m_pPlayer->SetSparta(true);
				m_pPlayer->SetSpeedLevel(vSavedData[m_nPosition].nSpeedLevel);
				m_pPlayer->SetSpeedMod(vSavedData[m_nPosition].fSpeedMod);
				m_pPlayer->SetSecondType(vSavedData[m_nPosition].nSecondType);
				if(vSavedData[m_nPosition].nFlame == 0)
					m_pPlayer->SetFlamerAccess(false);
				else
					m_pPlayer->SetFlamerAccess(true);
				switch(vSavedData[m_nPosition].nSpecialOne)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 4:
					{
						CReinforcements* pSpecial = new CReinforcements;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 5:
					{
						CAirStrike* pSpecial = new CAirStrike;
						m_pPlayer->SetSpecial1(pSpecial);
						m_pPlayer->SetSpecial1Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				}
				switch(vSavedData[m_nPosition].nSpecialTwo)
				{
				case 0:
					{
						CSpecial* pSpecial = new CSpecial;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 1:
					{
						CSmoke* pSpecial = new CSmoke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXSmoke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 2:
					{
						CEMP* pSpecial = new CEMP;
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
					}
					break;
				case 3:
					{
						CNuke* pSpecial = new CNuke;
						pSpecial->SetEmitter(CGamePlayState::GetInstance()->m_PM->GetEmitter(CGamePlayState::GetInstance()->FXNuke));
						m_pPlayer->SetSpecial2(pSpecial);
						m_pPlayer->SetSpecial2Ammo(pSpecial->GetAmmoCount());
						pSpecial = nullptr;
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
						pSpecial = nullptr;
					}
					break;
				}
				CGame::GetInstance()->ChangeState(CShopState::GetInstance());
				return true;
			}
		}
		else if(m_nPosition == 3)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame1.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame1.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
			else if(vSavedData[m_nPosition-1].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-1] = data;
				m_nCount--;
				m_nPosition-=1;
			}
		}
		else if(m_nPosition == 4)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			if(vSavedData[m_nPosition-3].nLevel != 0)
			{
				remove("savedGame2.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame2.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-3] = data;
				m_nCount--;
				m_nPosition-=3;
			}
			else if(vSavedData[m_nPosition-2].nLevel != 0)
			{
				remove("savedGame3.xml");
				Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				vSavedData[m_nPosition-2] = data;
				m_nCount--;
				m_nPosition-=2;
			}
		}
		else if(m_nPosition == 5)
		{	
			m_pAudio->SFXPlaySound(m_nClick, false);
			remove("savedGame3.xml");
			Data data = {"AAA",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"savedGame3.xml",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			vSavedData[m_nPosition-3] = data;
			m_nCount--;
			m_nPosition-=3;			
		}
	}
	}
	return true;
}

void CLoadGameState::Update(float fDt)
{
	if(ARCADE == 0)
	{
		if(m_pDI->JoystickGetLStickXAmount() > 0)
			m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()+5);
		if(m_pDI->JoystickGetLStickXAmount() < 0)
			m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()-5);
		if(m_pDI->JoystickGetLStickYAmount() > 0)
			m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()+5);
		if(m_pDI->JoystickGetLStickYAmount() < 0)
			m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()-5);
	}

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	if(m_nMouseX >= 45 && m_nMouseX <= 215
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		if(m_nPosition!=0)
			m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPosition = 0;
	}
	if(m_nMouseX >= 295 && m_nMouseX <= 465
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		if(m_nPosition!=1)
			m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPosition = 1;
	}
	if(m_nMouseX >= 550 && m_nMouseX <= 720
		&& m_nMouseY >= 455 && m_nMouseY <= 495)
	{
		if(m_nPosition!=2)
			m_pAudio->SFXPlaySound(m_nButton,false);
		m_nPosition = 2;
	}
	if(m_nMouseX >= 45 && m_nMouseX <= 215
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[0].nLevel != 0)
		{
			if(m_nPosition!=3)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 3;
		}
	}
	if(m_nMouseX >= 295 && m_nMouseX <= 465
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[1].nLevel != 0)
		{
			if(m_nPosition!=4)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 4;
		}
	}
	if(m_nMouseX >= 550 && m_nMouseX <= 720
		&& m_nMouseY >= 505 && m_nMouseY <= 545)
	{
		if(vSavedData[2].nLevel != 0)
		{
			if(m_nPosition!=5)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 5;
		}
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
		font->Print(m_sNewGame.c_str(),80,480,1.0f,D3DCOLOR_XRGB(177,132,0));
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
		font->Print(m_sLoad.c_str(),100,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sDelete.c_str(),100,525,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sName.c_str(),80,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sLevel.c_str(),80,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sMoney.c_str(),80,440,0.75f,D3DCOLOR_XRGB(255,0,0));
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
		font->Print(m_sNewGame.c_str(),332,480,1.0f,D3DCOLOR_XRGB(177,132,0));
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
		font->Print(m_sLoad.c_str(),352,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sDelete.c_str(),352,525,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sName.c_str(),332,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sLevel.c_str(),332,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sMoney.c_str(),332,440,0.75f,D3DCOLOR_XRGB(255,0,0));
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
		font->Print(m_sNewGame.c_str(),585,480,1.0f,D3DCOLOR_XRGB(177,132,0));
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
		font->Print(m_sLoad.c_str(),605,480,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sDelete.c_str(),605,525,1.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sName.c_str(),585,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sLevel.c_str(),585,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(m_sMoney.c_str(),585,440,0.75f,D3DCOLOR_XRGB(255,0,0));
		font->Print(vSavedData[2].szName,655,360,0.75f,D3DCOLOR_XRGB(255,0,0));
		char buffer[10];
		_itoa_s(vSavedData[2].nLevel,buffer,10);
		font->Print(buffer,655,400,0.75f,D3DCOLOR_XRGB(255,0,0));
		_itoa_s(vSavedData[2].nMoney,buffer,10);
		font->Print(buffer,655,440,0.75f,D3DCOLOR_XRGB(255,0,0));
	}

	/*char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	font->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	font->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(177,132,0));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(177,132,0));*/

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
		if(gameData->Attribute("Score"		, &info.nScore)==nullptr)
		{
			info.nScore = 0;
		}
		else
		{
			CPlayer::GetInstance()->SetScore(info.nScore);
		}

		if(gameData->Attribute("bNaziBoss"		, &info.bNaziBoss) == nullptr)
			info.bNaziBoss = 0;
		if(gameData->Attribute("bAlienBoss"		, &info.bAlienBoss) == nullptr)
			info.bAlienBoss = 0;
		if(gameData->Attribute("bRobotBoss"		, &info.bRobotBoss) == nullptr)
			info.bRobotBoss = 0;
		if(gameData->Attribute("bSparta"		, &info.bSparta) == nullptr)
			info.bSparta = 0;
		if(gameData->Attribute("bSapperAbsorb"		, &info.bSapperAbsorb) == nullptr)
			info.bSapperAbsorb = 0;
		if(gameData->Attribute("bNukem"		, &info.bNukem) == nullptr)
			info.bNukem = 0;
		if(gameData->Attribute("bIamBoss"		, &info.bIamBoss) == nullptr)
			info.bIamBoss = 0;
		if(gameData->Attribute("bAllUpgrades"		, &info.bAllUpgrades) == nullptr)
			info.bAllUpgrades = 0;
		// bNaziBoss",		
		// bAlienBoss",	
		// bRobotBoss",	
		// bSparta",		
		// bSapperAbsorb",	
		// bNukem",		
		// bIamBoss",		
		// bAllUpgrades",	

		if(gameData->Attribute("specialone"		, &info.nSpecialOne) == nullptr)
			info.nSpecialOne = 0;
		if(gameData->Attribute("specialtwo"		, &info.nSpecialTwo) == nullptr)
			info.nSpecialTwo = 0;
		if(gameData->Attribute("secondammo"		, &info.nSecondType) == nullptr)
			info.nSecondType = 0;
		if(gameData->Attribute("flame"			, &info.nFlame) == nullptr)
			info.nFlame = 0;

		strcpy_s(info.szFileName,32,szFileName);

		vSavedData[nGameData] = info;

		

	return true;
}

void CLoadGameState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("LoadGameState");
				TiXmlNode* pButton = pState->FirstChild("NewGame");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sNewGame=pText->Value();
				pButton=pState->FirstChild("Load");
				pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton = pState->FirstChild("Delete");
				pText = pButton->FirstChild()->ToText();
				m_sDelete=pText->Value();
				pButton=pState->FirstChild("Name");
				pText = pButton->FirstChild()->ToText();
				m_sName=pText->Value();
				pButton=pState->FirstChild("Level");
				pText = pButton->FirstChild()->ToText();
				m_sLevel=pText->Value();
				pButton=pState->FirstChild("Money");
				pText = pButton->FirstChild()->ToText();
				m_sMoney=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("LoadGameState");
				TiXmlNode* pButton = pState->FirstChild("NewGame");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sNewGame=pText->Value();
				pButton=pState->FirstChild("Load");
				pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton = pState->FirstChild("Delete");
				pText = pButton->FirstChild()->ToText();
				m_sDelete=pText->Value();
				pButton=pState->FirstChild("Name");
				pText = pButton->FirstChild()->ToText();
				m_sName=pText->Value();
				pButton=pState->FirstChild("Level");
				pText = pButton->FirstChild()->ToText();
				m_sLevel=pText->Value();
				pButton=pState->FirstChild("Money");
				pText = pButton->FirstChild()->ToText();
				m_sMoney=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("LoadGameState");
				TiXmlNode* pButton = pState->FirstChild("NewGame");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sNewGame=pText->Value();
				pButton=pState->FirstChild("Load");
				pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton = pState->FirstChild("Delete");
				pText = pButton->FirstChild()->ToText();
				m_sDelete=pText->Value();
				pButton=pState->FirstChild("Name");
				pText = pButton->FirstChild()->ToText();
				m_sName=pText->Value();
				pButton=pState->FirstChild("Level");
				pText = pButton->FirstChild()->ToText();
				m_sLevel=pText->Value();
				pButton=pState->FirstChild("Money");
				pText = pButton->FirstChild()->ToText();
				m_sMoney=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("LoadGameState");
				TiXmlNode* pButton = pState->FirstChild("NewGame");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sNewGame=pText->Value();
				pButton=pState->FirstChild("Load");
				pText = pButton->FirstChild()->ToText();
				m_sLoad=pText->Value();
				pButton = pState->FirstChild("Delete");
				pText = pButton->FirstChild()->ToText();
				m_sDelete=pText->Value();
				pButton=pState->FirstChild("Name");
				pText = pButton->FirstChild()->ToText();
				m_sName=pText->Value();
				pButton=pState->FirstChild("Level");
				pText = pButton->FirstChild()->ToText();
				m_sLevel=pText->Value();
				pButton=pState->FirstChild("Money");
				pText = pButton->FirstChild()->ToText();
				m_sMoney=pText->Value();
			}
			break;
		}
	}
}
