#include "SurvivalState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/BitmapFont.h"
#include "../GameObjects/Bullet.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Particle/ParticleManager.h"
#include "../Animation/AnimationManager.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "SurvivalState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/BitmapFont.h"
#include "../GameObjects/Bullet.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Particle/ParticleManager.h"
#include "../Animation/AnimationManager.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Event and Messages/CreateBulletMessage.h"
#include "../Event and Messages/DestroyBulletMessage.h"
#include "../Event and Messages/DestroyEnemyMessage.h"
#include "../Event and Messages/DestroyTurretMessage.h"
#include "../Event and Messages/DestroyBuildingMessage.h"
#include "../Event and Messages/CreateBuildingMessage.h"
#include "../Event and Messages/CreateMineMessage.h"
#include "../Event and Messages/DestroyMineMessage.h"
#include "../Event and Messages/SoldierFireMessage.h"
#include "../World and Tile/Tile.h"
#include "../World and Tile/TileManager.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Turret.h"
#include "../Headers/Camera.h"
#include "../GameObjects/Sapper.h"
#include "../GameObjects/Tank.h"
#include "../Particle/Emitter.h"
#include "../GameObjects/Building.h"
#include "../PickUps and Specials/Pickup.h"
#include "../Event and Messages/CreatePickupMessage.h"
#include "../Event and Messages/DestroyPickupMessage.h"
#include "../tinyxml/tinyxml.h"
#include "ShopState.h"
#include "SurvivalHS.h"
#include "../Headers/GUI.h"
#include "../PickUps and Specials/Special.h"
#include "../PickUps and Specials/Nuke.h"
#include "../PickUps and Specials/Smoke.h"
#include "StatState.h"
#include <time.h>
#include "../Headers/BitmapFont.h"
CSurvivalState* CSurvivalState::m_pSelf = nullptr;

CSurvivalState::CSurvivalState(void)
{
	m_pD3D	= nullptr;
	m_pDI	= nullptr;
	m_pTM	= nullptr;
	m_pFont = nullptr;
	m_pOM	= nullptr;
	m_pOF	= nullptr;
	m_PM	= nullptr;
	m_pMS	= nullptr;
	m_pTile = nullptr;
	m_AM	= nullptr;
	m_pES	= nullptr;
	m_pAudio = nullptr;
	srand((unsigned int)time);
	for(int i = 0; i < 16; ++i)
	{
		m_anEnemyIDs[i] = -1;
	}

	for(int i = 0; i < 4; ++i)
		m_anBulletImageIDs[i] = -1;
	
	m_nPlayerID = -1;
	m_nPosition = 0;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	m_bPaused = false;

	m_nCursor = -1;
	m_nMouseX = 0;
	m_nMouseY = 0;
	m_nButtonImageID=-1;
	m_nWavesRemaining = 1;
	m_nPickupHealthID = -1;
	m_nPickupAmmoID = -1;
	m_nPickupArmorID = -1;
	m_nPickupDoubleDID = -1;
	m_nPickupNoReloadID = -1;
	m_nPickupInvuID = -1;
	m_nPickupInfAmmoID = -1;
	m_nPickupMoneyID = -1;
	SoundOff = false;

	m_nGameMusic = -1;
	m_nSappSound = -1;
	m_nNukeSound = -1;

	for(int i = 0; i < 6; i++)
		m_anBulletSounds[i] = -1;

	for(int i = 0; i < 9; i++)
		m_anSoldierSounds[i] = -1;


}

CSurvivalState::~CSurvivalState(void)
{
}

CSurvivalState* CSurvivalState::GetInstance( void )
{
	if(!m_pSelf)
		m_pSelf = new CSurvivalState;
	return m_pSelf;
}

void CSurvivalState::DeleteInstance( void )
{
	if(m_pSelf)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CSurvivalState::Enter( void )
{
	SoundOff = false;
	LoadText();
	if(m_bPaused == false)
	{
		
		
		m_pD3D	= CSGD_Direct3D::GetInstance();
		m_pDI	= CSGD_DirectInput::GetInstance();
		m_pTM	= CSGD_TextureManager::GetInstance();
		m_pOM	= CObjectManager::GetInstance();
		m_pOF	= CFactory::GetInstance();
		m_PM	= CParticleManager::GetInstance();
		m_pMS	= CMessageSystem::GetInstance();
		m_pTile = CTileManager::GetInstance();
		m_AM	= CAnimationManager::GetInstance();
		m_pES = CEventSystem::GetInstance();
		m_pGUI = CGUI::GetInstance();
		m_pFont=CBitmapFont::GetInstance();
		m_pAudio = CSGD_XAudio2::GetInstance();
		m_pDI->ClearInput();
		cout<<"All Managers Loaded\n";
		for(int i = 0; i < 16; ++i)
		{
			m_anEnemyIDs[i] = m_pTM->LoadTexture( _T( "resource/graphics/JF_enemy1.png"), 	0 );
		}

		//m_AM->Load("AnimationInfo.xml");
		//m_AM->Save("AnimationInfo.xml");

		m_nBackGround = m_pTM->LoadTexture(_T("resource/graphics/loading.jpg"));

		m_pD3D->Clear( 0, 255, 255 );// Clear the background

		// Start D3D rendering
		m_pD3D->DeviceBegin();
		m_pD3D->SpriteBegin();	

		m_pTM->Draw(m_nBackGround,0,0,0.8f,0.8f);
	
		m_pD3D->GetSprite()->Flush();	
		m_pD3D->SpriteEnd();
		m_pD3D->DeviceEnd();	

		m_pD3D->Present();

		cout<<"Waiting\n";
	
		FXEnemy_Tails=m_PM->AddEmitter("resource/files/Enemy_Trail.xml");
		FXSapper_Explosion=m_PM->AddEmitter("resource/files/Explosion.xml");
		FXFlame=m_PM->AddEmitter("resource/files/Flame.xml");
		FXBuildingFlame=m_PM->AddEmitter("resource/files/Building Flame.xml");
		FXNuke=m_PM->AddEmitter("resource/files/Nuke.xml");
		FXTreads=m_PM->AddEmitter("resource/files/Tracks.xml");
		FXSmoke=m_PM->AddEmitter("resource/files/Smoke.xml");
		FXEnemyOnFire=m_PM->AddEmitter("resource/files/OnFire.xml");

		cout<<"All FX Loaded\n";

		m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
		m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 0 );
		m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[4] = m_pTM->LoadTexture( _T( "resource/graphics/Laser.png"), 	0 );
		m_nPlayerID=m_pTM->LoadTexture(_T("resource/graphics/Green Base.png"));
		m_nPlayerTurretID=m_pTM->LoadTexture(_T("resource/graphics/Green Turret.png"));
		m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/Nazi Sapper.png"));
		m_anEnemyIDs[2]=m_pTM->LoadTexture(_T("resource/graphics/Building.png"));
		m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
		m_anEnemyIDs[3]=m_pTM->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
		m_anEnemyIDs[4]=m_pTM->LoadTexture(_T("resource/graphics/Nazi Rifle.png"));
		m_anEnemyIDs[5]=m_pTM->LoadTexture(_T("resource/graphics/rubble.png"));
		m_anEnemyIDs[6]=m_pTM->LoadTexture(_T("resource/graphics/enemyTank.png"));
		m_anEnemyIDs[7]=m_pTM->LoadTexture(_T("resource/graphics/enemyTurret.png"));
		m_anEnemyIDs[8]=m_pTM->LoadTexture(_T("resource/graphics/SpecialSelect.png"));
		m_anEnemyIDs[13]=m_pTM->LoadTexture(_T("resource/graphics/GunSel.png"));

		m_nPickupHealthID = m_pTM->LoadTexture(_T("resource/graphics/HealthPickUp.png"));
		m_nPickupAmmoID = m_pTM->LoadTexture(_T("resource/graphics/AmmoPickUp.png"));
		m_nPickupArmorID = m_pTM->LoadTexture(_T("resource/graphics/ArmorPickUp.png"));
		m_nPickupDoubleDID = m_pTM->LoadTexture(_T("resource/graphics/DoubleDamagePickUp.png"));
		m_nPickupNoReloadID = m_pTM->LoadTexture(_T("resource/graphics/NoReloadPickUp.png"));
		m_nPickupInvuID = m_pTM->LoadTexture(_T("resource/graphics/InvulnerabilityPickUp.png"));
		m_nPickupInfAmmoID = m_pTM->LoadTexture(_T("resource/graphics/InfAmmoPickUp.png"));
		m_nPickupMoneyID = m_pTM->LoadTexture(_T("resource/graphics/MoneyPickUp.png"));

		cout<<"All Images Loaded\n";

		m_anBulletSounds[0] = m_pAudio->SFXLoadSound(_T("resource/sound/shell.wav"));
		m_anBulletSounds[1] = m_pAudio->SFXLoadSound(_T("resource/sound/rocket.wav"));
		m_anBulletSounds[2] = m_pAudio->SFXLoadSound(_T("resource/sound/artillery.wav"));
		m_anBulletSounds[3] = m_pAudio->SFXLoadSound(_T("resource/sound/machinegun.wav"));
		m_anBulletSounds[4] = m_pAudio->SFXLoadSound(_T("resource/sound/laser.wav"));
		m_anBulletSounds[5] = m_pAudio->SFXLoadSound(_T("resource/sound/fire.wav"));
		m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
		m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));

		m_anSoldierSounds[0] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt1.wav"));
		m_anSoldierSounds[1] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt2.wav"));
		m_anSoldierSounds[2] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt3.wav"));
		m_anSoldierSounds[3] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt4.wav"));
		m_anSoldierSounds[4] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt5.wav"));
		m_anSoldierSounds[5] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt6.wav"));
		m_anSoldierSounds[6] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt7.wav"));
		m_anSoldierSounds[7] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt8.wav"));
		m_anSoldierSounds[8] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt9.wav"));

		m_nSappSound = m_pAudio->SFXLoadSound(_T("resource/sound/sapper.wav"));
		m_nNukeSound = m_pAudio->SFXLoadSound(_T("resource/sound/nuke.wav"));

		cout<<"All Sounds Loaded\n";

		m_pMS->InitMessageSystem(&MessageProc);

		m_pOF->RegisterClassType<CEntity>("CEntity");
		m_pOF->RegisterClassType<CEnemy>("CEnemy");
		m_pOF->RegisterClassType<CBullet>("CBullet");
		m_pOF->RegisterClassType<CTurret>("CTurret");
		m_pOF->RegisterClassType<CTank>("CTank");
		m_pOF->RegisterClassType<CSapper>("CSapper");
		m_pOF->RegisterClassType<CBuilding>("CBuilding");
		m_pOF->RegisterClassType<CPickup>("CPickup");
//		m_pOF->RegisterClassType<CMine>("CMine");
//		m_pOF->RegisterClassType<CFlyText>("CFlyText");

		cout<<"All Classes Loaded\n";

		m_pPlayer=CPlayer::GetInstance();
		CPlayer* player=dynamic_cast<CPlayer*>(m_pPlayer);
		player->SetImageID(m_nPlayerID);
		player->SetPosX(float(CGame::GetInstance()->GetWidth()/2));
		player->SetPosY(float(CGame::GetInstance()->GetHeight()/2));
		player->SetFireSound(m_anBulletSounds[5]);
		player->SetNukeSound(m_nNukeSound);
		player->SetRotation(0);
		player->SetWidth(64);
		player->SetHeight(128);
		player->SetVelX(90);
		player->SetVelY(90);
		player->SetHealth(250);
		player->SetMaxHealth(250);
		player->SetArmor(150);
		player->SetMaxArmor(150);
		player->SetWeaponAmmo(40/*m_dGameData.nShellAmmo*/,40/*m_dGameData.nArtilleryAmmo*/,/*m_dGameData.nMissileAmmo*/40);
		player->SetMaxWeaponAmmo(40,40,40);
		player->SetMoney(m_dGameData.nMoney);
		tVector2D v2Pos = { player->GetPosX(), player->GetPosY() };
		CNuke* pNuke = new CNuke();
		pNuke->SetEmitter(m_PM->GetEmitter(FXNuke));
		CSmoke* pSmoke=new CSmoke();
		pSmoke->SetEmitter(m_PM->GetEmitter(FXSmoke));
		//CReinforcements* pRF = new CReinforcements;
		//CAirStrike* pAS = new CAirStrike;
		player->SetSpecial1(pNuke);
		player->SetSpecial2(pSmoke);
		player->SetSpecial1Ammo(1);
		player->SetSpecial2Ammo(5);
		pNuke = nullptr;
		pSmoke = nullptr;
		player->SetOldPos(v2Pos);
		player->SetSecondType(MACHINEGUN);
		
		//buffs LEAVE ON ALL SET TO FALSE AND 0 TIME
		player->SetDoubleDamage(false);
		player->SetDamageTimer(0.0f);
		player->SetNoReloadTimer(0.0f);
		player->SetInvul(false);
		player->SetInvulTimer(0.0f);
		player->SetInfAmmo(false);
		player->SetInfoAmmoTimer(0.0f);
		
		player->SetGunSel(1);

		CTurret* PlayerTurret=(CTurret*)m_pOF->CreateObject("CTurret");
		PlayerTurret->SetImageID(m_nPlayerTurretID);
		player->SetTurret(PlayerTurret);
		PlayerTurret->SetPosX(player->GetPosX());
		PlayerTurret->SetPosY(player->GetPosY());
		PlayerTurret->SetOwner(player);
		PlayerTurret->SetBullet(BUL_SHELL);
		PlayerTurret->SetWidth(64);
		PlayerTurret->SetHeight(128);
		PlayerTurret->SetRotationPositon(32,98);
		PlayerTurret->SetUpVec(0,-1);
		PlayerTurret->SetDistance(800);
		PlayerTurret->SetRotationRate(1.8f);
		PlayerTurret->SetFlamer(m_PM->GetEmitter(FXFlame));
		m_pTile->Load("resource/files/survivalmap.xml");
		m_pMS->ProcessMessages();
		m_pOM->AddObject(player);
		m_pOM->AddObject(PlayerTurret);
		PlayerTurret->Release();

		cout<<"Player Complete\n";


		m_pGUI->SetHudID(m_anEnemyIDs[3]);
		m_pGUI->SetPlayer(player);
		m_pGUI->SetSelect(m_anEnemyIDs[8]);
		m_pGUI->SetGunSel(m_anEnemyIDs[13]);
		m_pGUI->SetGunSelected(1);

		m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);

		player->SetMoney(0);
		cout<<"Hud Set\n";
	}
	//LoadText();
	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	D3DXCreateTexture(m_pD3D->GetDirect3DDevice(), 125, 120, 0, D3DUSAGE_RENDERTARGET|D3DUSAGE_AUTOGENMIPMAP, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &MiniMap); 

	m_nNumUnits = 0;
	cout<<"Loading Files\n";
	LoadWave("resource/files/48wavesofhell.xml",0);
	m_nGameMusic = m_pAudio->MusicLoadSong(_T("resource/sound/GameMusic.xwm"));
	if(m_nGameMusic != -1)
	{
		m_pAudio->MusicPlaySong(m_nGameMusic, true);
	}
}

void CSurvivalState::Exit( void )
{
	if(m_bPaused == false)
	{
		m_PM->RemoveAllBaseEmitters();
		m_PM->DeleteInstance();

		m_nNumUnits = 0;
		m_nCurrWave = 0;
		m_nWavesRemaining = 0;

	for(int i = 0; i < 6; i++)
		{
			if(m_anBulletSounds[i] != -1)
			{
				m_pAudio->SFXStopSound(m_anBulletSounds[i]);
				m_pAudio->SFXUnloadSound(m_anBulletSounds[i]);
				m_anBulletSounds[i] = -1;
			}
		}

		for(int i = 0; i < 9; i++)
		{
			if(m_anSoldierSounds[i] != -1)
			{
				m_pAudio->SFXStopSound(m_anSoldierSounds[i]);
				m_pAudio->SFXUnloadSound(m_anSoldierSounds[i]);
				m_anSoldierSounds[i] = -1;
			}
		}

		for(int i = 0; i < 9; i++)
		{
			if(m_anSoldierSounds[i] != -1)
			{
				m_pAudio->SFXStopSound(m_anSoldierSounds[i]);
				m_pAudio->SFXUnloadSound(m_anSoldierSounds[i]);
				m_anSoldierSounds[i] = -1;
			}
		}

		

		if(m_nSappSound != -1)
		{
			m_pAudio->SFXStopSound(m_nSappSound);
			m_pAudio->SFXUnloadSound(m_nSappSound);
			m_nSappSound = -1;
		}

		if(m_nNukeSound != -1)
		{
			m_pAudio->SFXStopSound(m_nNukeSound);
			m_pAudio->SFXUnloadSound(m_nNukeSound);
			m_nNukeSound = -1;
		}
		
		
	
		if(m_nGameMusic != -1)
		{
			m_pAudio->MusicStopSong(m_nGameMusic);
			m_pAudio->MusicUnloadSong(m_nGameMusic);
			m_nGameMusic = -1;

		}

		
		if(m_nButtonImageID != -1)
		{
			m_pTM->UnloadTexture(m_nButtonImageID);
			m_nButtonImageID = -1;
		}

		if(m_pEnemy != nullptr)
		{
			m_pEnemy->Release();
			m_pEnemy = nullptr;
		}

		if(m_nCursor != -1)
		{
			m_pTM->UnloadTexture(m_nCursor);
			m_nCursor = -1;
		}

		if(m_nPlayerID != -1)
		{
			m_pTM->UnloadTexture(m_nPlayerID);
			m_nPlayerID = -1;
		}

		if(m_nPickupHealthID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupHealthID);
			m_nPickupHealthID = -1;
		}

		if(m_nPickupAmmoID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupAmmoID);
			m_nPickupAmmoID = -1;
		}

		if(m_nPickupArmorID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupArmorID);
			m_nPickupArmorID = -1;
		}

		if(m_nPickupDoubleDID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupDoubleDID);
			m_nPickupDoubleDID = -1;
		}

		if(m_nPickupNoReloadID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupNoReloadID);
			m_nPickupNoReloadID = -1;
		}

		if(m_nPickupInvuID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupInvuID);
			m_nPickupInvuID = -1;
		}

		if(m_nPickupInfAmmoID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupInfAmmoID);
			m_nPickupInfAmmoID = -1;
		}

		if(m_nPickupMoneyID != -1)
		{
			m_pTM->UnloadTexture(m_nPickupMoneyID);
			m_nPickupMoneyID = -1;
		}

		for(int i = 0; i < 16; ++i)
		{
			if(m_anEnemyIDs[i] != -1)
			{
				m_pTM->UnloadTexture(m_anEnemyIDs[i]);
				m_anEnemyIDs[i] = -1;
			}
		}

		for(int i = 0; i < 3; ++i)
		{
			m_pTM->UnloadTexture(m_anBulletImageIDs[i]);
			m_anBulletImageIDs[i] = -1;
		}

		if(m_pOF != nullptr)
		{
			m_pOF->ShutdownObjectFactory();
			m_pOF	= nullptr;
		}

		if(m_pOM != nullptr)
		{
			m_pOM->RemoveAllObjects();
			m_pOM	= nullptr;
		}	

		if(m_pMS != nullptr)
		{
			m_pMS->ClearMessages();
			m_pMS->ShutDownMessageSystem();
			m_pMS	= nullptr;
		}			

		if(m_pES != nullptr)
		{
			m_pES->ClearEvents();
			m_pES->ShutdownEventSystem();
			m_pES = nullptr;
		}
	
		m_pD3D	= nullptr;
		m_pDI	= nullptr;
		m_pTM	= nullptr;
		m_pFont = nullptr;	
		m_PM	= nullptr;	
		if(m_pTile != nullptr)
		{
			m_pTile->DeleteInstance();
			m_pTile = nullptr;
		}
		m_AM	= nullptr;
	
		if(m_pGUI!=nullptr)
		{
			m_pGUI->DeleteInstance();
			m_pGUI=nullptr;
		}
		TurnSoundOff();
	}
}

bool CSurvivalState::Input( void )
{

	if(ARCADE == 0)
	{
		if(m_bPaused)
		{
			if(m_pDI->KeyPressed(DIK_ESCAPE))
			{
				m_bPaused = !m_bPaused;
			}
			if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
			{
				m_pAudio->SFXPlaySound(m_nClick, false);
				if(m_nPosition == 0)
				{
					m_bPaused = !m_bPaused;
				}
				else if(m_nPosition == 1)
				{
					CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
				}
				else if(m_nPosition == 2)
				{
					m_bPaused = false;
					CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
					return true;		
				}
			}
			if(m_pDI->KeyPressed(DIK_UP) || m_pDI->JoystickDPadPressed(DIR_UP))
			{
				if(m_nPosition == 0)
				{
					m_nPosition = 2;
				}
				else
				{
					m_nPosition -= 1;
				}
			}
			else if(m_pDI->KeyPressed(DIK_DOWN) || m_pDI->JoystickDPadPressed(DIR_DOWN))
			{
				if(m_nPosition == 2)
				{
					m_nPosition = 0;
				}
				else
				{
					m_nPosition += 1;
				}
			}
		}
		else
		{
			if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(7))
			{
				m_bPaused = !m_bPaused;
			}
		}
		if(m_pDI->KeyDown(DIK_LMENU)||m_pDI->KeyDown(DIK_RMENU))
		{
			if(m_pDI->KeyPressed(DIK_TAB))
			{
				m_bPaused=true;
			}
		}
	}
	else
	{
		if(m_bPaused)
		{
			if(m_pDI->JoystickButtonPressed(6))
			{
				m_bPaused = !m_bPaused;
			}
			if(m_pDI->JoystickButtonPressed(0))
			{
				m_pAudio->SFXPlaySound(m_nClick, false);
				if(m_nPosition == 0)
				{
					m_bPaused = !m_bPaused;
				}
				else if(m_nPosition == 1)
				{
					CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
				}
				else if(m_nPosition == 2)
				{
					m_bPaused = false;
					CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
					return true;		
				}
			}
			if(m_pDI->JoystickGetLStickDirPressed(DIR_UP))
			{
				m_pAudio->SFXPlaySound(m_nButton,false);
				if(m_nPosition == 0)
				{
					m_nPosition = 2;
				}
				else
				{
					m_nPosition -= 1;
				}
			}
			else if(m_pDI->JoystickGetLStickDirPressed(DIR_DOWN))
			{
				m_pAudio->SFXPlaySound(m_nButton,false);
				if(m_nPosition == 2)
				{
					m_nPosition = 0;
				}
				else
				{
					m_nPosition += 1;
				}
			}
		}
		else
		{
			if(m_pDI->JoystickButtonPressed(6))
			{
				m_bPaused = !m_bPaused;
			}
		}
		return true;
		
	}
	return true;
}

void CSurvivalState::Update( float fDt )
{
	
	if(!m_bPaused)
	{
		cout<<"Camera "<<Camera::GetInstance()<<endl;
		Camera::GetInstance()->Update(dynamic_cast<CPlayer*>(m_pPlayer),0,0,fDt);
		cout<<"Particle "<<m_PM->GetInstance()<<endl;
		m_PM->UpdateEverything(fDt);
		cout<<"Object "<<m_pOM->GetInstance()<<endl;
		m_pOM->UpdateAllObjects(fDt);
		m_pOM->CheckCollisions();
		cout<<"Audio "<<m_pAudio->GetInstance()<<endl;
		m_pAudio->Update();
		cout<<"Events "<<m_pES->GetInstance()<<endl;
		m_pES->ProcessEvents();
		cout<<"Messages "<<m_pMS->GetInstance()<<endl;
		m_pMS->ProcessMessages();
	}
	
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

	if(m_bPaused)
	{
		if(m_nMouseX >= 315 && m_nMouseX <= 482
			&& m_nMouseY >= 295 && m_nMouseY <= 340)
		{
			if(m_nPosition!=0)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 0;
		}
		if(m_nMouseX >= 315 && m_nMouseX <= 482
			&& m_nMouseY >= 340 && m_nMouseY <= 390)
		{
			if(m_nPosition!=1)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 1;
		}
		if(m_nMouseX >= 315 && m_nMouseX <= 482
			&& m_nMouseY >= 390 && m_nMouseY <= 435)
		{
			if(m_nPosition!=2)
				m_pAudio->SFXPlaySound(m_nButton,false);
			m_nPosition = 2;
		}
	}

	if(m_nNumUnits <= 0)
	{
		m_nWavesRemaining--;
		if(m_nWavesRemaining <= 0)
			CGame::GetInstance()->ChangeState(CSurvivalHS::GetInstance());
		else
		{
			m_nNumUnits = 0;
			m_nCurrWave++;
			GenerateWave();
		}
	}
	if(CPlayer::GetInstance()->GetHealth() <= 0)
		CGame::GetInstance()->ChangeState(CSurvivalHS::GetInstance());
}

void CSurvivalState::Render( void )
{
	m_pD3D->Clear( 0, 255, 255 );
	IDirect3DSurface9 *current=0, *output=0;
	m_pD3D->GetDirect3DDevice()->GetRenderTarget(0, &current);

	MiniMap->GetSurfaceLevel(0,&output);
	m_pD3D->GetDirect3DDevice()->SetRenderTarget(0, output);
	m_pD3D->Clear( 0, 0, 0 );

	{

	/*	m_pTM->Draw(m_nBackGround,int(Camera::GetInstance()->GetPosX()),
			int(Camera::GetInstance()->GetPosY()),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));*/
		// Render game entities
		m_pTile->Render();
		m_pOM->RenderAllObjects();
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	}
	m_pD3D->GetDirect3DDevice()->SetRenderTarget(0, current);
	{
		Camera* C=Camera::GetInstance();
		CGame* G=CGame::GetInstance();
		m_pTM->Draw(m_nBackGround,int(Camera::GetInstance()->GetPosX()),
			int(Camera::GetInstance()->GetPosY()),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
		// Render game entities
		m_pTile->Render();
		m_pOM->RenderAllObjects();
		//m_AM->Render();
		// Flush the sprites
		m_PM->RenderEverything();
		m_pD3D->GetSprite()->Draw(MiniMap, NULL, &D3DXVECTOR3(0,0,0),&D3DXVECTOR3(661,409,0), D3DCOLOR_ARGB(255,255,255,255));
		m_pGUI->Render();
		m_pD3D->GetSprite()->Flush();
		m_pFont->Print(m_sWave.c_str(), 539,547,.60f,UINT_MAX);
	}

	m_pD3D->GetSprite()->Flush();	

	if(m_bPaused)
	{
		CBitmapFont* font = CBitmapFont::GetInstance();
		font->Init(COptionsState::GetInstance()->GetLang());


		DWORD fScale1, fScale2, fScale3;
		switch(m_nPosition)
		{
		case 0:
			fScale1 = D3DCOLOR_XRGB(177,132,0);
			fScale2 = D3DCOLOR_XRGB(255,255,255);
			fScale3 = D3DCOLOR_XRGB(255,255,255);

			break;
		case 1:
			fScale1 = D3DCOLOR_XRGB(255,255,255);
			fScale2 = D3DCOLOR_XRGB(177,132,0);
			fScale3 = D3DCOLOR_XRGB(255,255,255);

			break;
		case 2:
			fScale1 = D3DCOLOR_XRGB(255,255,255);
			fScale2 = D3DCOLOR_XRGB(255,255,255);
			fScale3 = D3DCOLOR_XRGB(177,132,0);

			break;
		}
		m_pD3D->GetSprite()->Flush();
		m_pTM->Draw(m_nButtonImageID,(CGame::GetInstance()->GetWidth()/2)-85,CGame::GetInstance()->GetHeight()/2-10,0.75f,0.75f,nullptr,0,0,0,fScale1);
		m_pTM->Draw(m_nButtonImageID,(CGame::GetInstance()->GetWidth()/2)-85,CGame::GetInstance()->GetHeight()/2+40,0.75f,0.75f,nullptr,0,0,0,fScale2);
		m_pTM->Draw(m_nButtonImageID,(CGame::GetInstance()->GetWidth()/2)-85,CGame::GetInstance()->GetHeight()/2+90,0.75f,0.75f,nullptr,0,0,0,fScale3);

		m_pD3D->GetSprite()->Flush();
		font->Print(m_sPaused.c_str(),(CGame::GetInstance()->GetWidth()/2)-125,CGame::GetInstance()->GetHeight()/2-100,3.0f,D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sResume.c_str(),(CGame::GetInstance()->GetWidth()/2)-48,CGame::GetInstance()->GetHeight()/2,1.0f,		D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sOptions.c_str(),(CGame::GetInstance()->GetWidth()/2)-50,CGame::GetInstance()->GetHeight()/2+50,1.0f,	D3DCOLOR_XRGB(177,132,0));
		font->Print(m_sExit.c_str(),(CGame::GetInstance()->GetWidth()/2)-30,CGame::GetInstance()->GetHeight()/2+100,1.0f,	D3DCOLOR_XRGB(177,132,0));
	}

	//CBitmapFont::GetInstance()->Print("Wave ",(CGame::GetInstance()->GetWidth()/2)-125,CGame::GetInstance()->GetHeight()/2-100,3.0f,D3DCOLOR_XRGB(50,132,0));
	char buffer[10];
	_itoa_s(m_nCurrWave,buffer,10);
	CBitmapFont::GetInstance()->Print(buffer,(CGame::GetInstance()->GetWidth()/2+50)+140,CGame::GetInstance()->GetHeight()-52,.60f,D3DCOLOR_ARGB(255,255,255,255));
	
	
	//_itoa_s(m_nNumUnits,buffer,10);
	//CBitmapFont::GetInstance()->Print(buffer,(CGame::GetInstance()->GetWidth()/2+50)+125,CGame::GetInstance()->GetHeight()/2+200,3.0f,D3DCOLOR_XRGB(50,132,0));
	//
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);



}

void CSurvivalState::MessageProc( CMessage* pMsg )
{
	CSurvivalState* pSelf = CSurvivalState::GetInstance();
	Camera* C=Camera::GetInstance();
	switch(pMsg->GetMessageID())
	{
	case MSG_CREATEBULLET:
		{
			CEntity* pBullet = pSelf->m_pOF->CreateObject("CBullet");
			CBullet* Bullet = dynamic_cast<CBullet*>(pBullet);
			CCreateBulletMessage* pMessage = dynamic_cast<CCreateBulletMessage*>(pMsg);
			CPlayer* player=dynamic_cast<CPlayer*>(pSelf->m_pPlayer);
			switch(pMessage->GetBulletType())
			{
			case BUL_SHELL:
				{					
					Bullet->SetBulletSound(pSelf->m_anBulletSounds[0]);
					CEventSystem::GetInstance()->SendEvent("shoot",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.35f);

					if(pMessage->GetFiringEntity()->GetOwner() != nullptr)
					{
						if(pMessage->GetFiringEntity()->GetOwner()->GetType() == OBJ_PLAYER)
							Bullet->SetWhoFired(true);
					}
					else
						Bullet->SetWhoFired(false);

					if(pMessage->GetFiringEntity() != nullptr)
					{
						tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							if(player->GetWeaponAmmoShell()> 0)
							{

								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2f*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2f*abs(Up.fX));
								if(player->GetDoubleDamage())
									Bullet->SetDamage(35.0f*2);
								else
									Bullet->SetDamage(35.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoShell();
									player->SetWeaponAmmo(--ammoChange, player->GetWeaponAmmoArtillery(), player->GetWeaponAmmoMissile());
								}
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
							Bullet->SetDamage(35.0f);
						}
						Bullet->SetVelX(norVec.fX*400);
						Bullet->SetVelY(norVec.fY*400);
					}
					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_ROCKET:
				{					
					Bullet->SetBulletSound(pSelf->m_anBulletSounds[1]);
					CEventSystem::GetInstance()->SendEvent("shoot",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.35f);

					if(pMessage->GetFiringEntity()->GetOwner() != nullptr)
					{
						if(pMessage->GetFiringEntity()->GetOwner()->GetType() == OBJ_PLAYER)
							Bullet->SetWhoFired(true);
					}
					else
						Bullet->SetWhoFired(false);

					if(pMessage->GetFiringEntity() != nullptr)
					{
						//tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						//norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							if(player->GetWeaponAmmoMissile()> 0)
							{
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2f*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2f*abs(Up.fX));
								if(player->GetDoubleDamage())
									Bullet->SetDamage(45.0f*2);
								else
									Bullet->SetDamage(45.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoMissile();
									player->SetWeaponAmmo(player->GetWeaponAmmoShell(), player->GetWeaponAmmoArtillery(), --ammoChange);
								}
								RECT rSelf;
								SetRect(&rSelf,int(pSelf->m_nMouseX-C->GetPosX()-32),int(pSelf->m_nMouseY-C->GetPosY()-32),int(pSelf->m_nMouseX-C->GetPosX()+32),int(pSelf->m_nMouseY-C->GetPosY()+32));
								Bullet->SetTargetRect(rSelf);
								tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX()+16,pSelf->m_nMouseY-C->GetPosY()+16};
								Bullet->SetTargetPos(vPos);
								Bullet->SetMissileTimer(0.25f);
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
							Bullet->SetDamage(45.0f);
						}
						Bullet->SetVelX(/*norVec.fX**/300);
						Bullet->SetVelY(/*norVec.fY**/300);
					}
					Bullet->SetBulletType(BUL_ROCKET);
					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_ROCKET]);
					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_ARTILLERY:
				{					
					Bullet->SetBulletSound(pSelf->m_anBulletSounds[2]);
					CEventSystem::GetInstance()->SendEvent("shoot",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.35f);

					if(pMessage->GetFiringEntity()->GetOwner() != nullptr)
					{
						if(pMessage->GetFiringEntity()->GetOwner()->GetType() == OBJ_PLAYER)
							Bullet->SetWhoFired(true);
					}
					else
						Bullet->SetWhoFired(false);

					if(pMessage->GetFiringEntity() != nullptr)
					{
						tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							if(player->GetWeaponAmmoMissile()> 0)
							{
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2f*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2f*abs(Up.fX));
								if(player->GetDoubleDamage())
									Bullet->SetDamage(15.0f*2);
								else
									Bullet->SetDamage(15.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoArtillery();
									player->SetWeaponAmmo(player->GetWeaponAmmoShell(), --ammoChange,player->GetWeaponAmmoMissile());
								}
								RECT rSelf;
								SetRect(&rSelf,(pSelf->m_nMouseX-32),(pSelf->m_nMouseY-32),(pSelf->m_nMouseX+32),(pSelf->m_nMouseY+32));
								Bullet->SetTargetRect(rSelf);
								tVector2D vPos = { float(pSelf->m_nMouseX-16),float(pSelf->m_nMouseY-16)};
								Bullet->SetTargetPos(vPos);
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
							Bullet->SetDamage(15.0f);
						}
						Bullet->SetVelX(norVec.fX*400);
						Bullet->SetVelY(norVec.fY*400);
					}
					Bullet->SetBulletType(BUL_ARTILLERY);
					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_ARTILLERY]);
					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_MACHINEGUN:
				{
					Bullet->SetBulletSound(pSelf->m_anBulletSounds[3]);
					CEventSystem::GetInstance()->SendEvent("shoot",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.15f);
					if(pMessage->GetFiringEntity()->GetOwner()->GetType() == OBJ_PLAYER)
						Bullet->SetWhoFired(true);
					else
						Bullet->SetWhoFired(false);
					if(pMessage->GetFiringEntity() != nullptr)
					{

						tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2f*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2f*abs(Up.fX));
							if(player->GetDoubleDamage())
								Bullet->SetDamage(5.0f*2);
							else
								Bullet->SetDamage(5.0f);
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
							Bullet->SetDamage(5.0f);
						}
						Bullet->SetVelX(norVec.fX*400);
						Bullet->SetVelY(norVec.fY*400);
					}


					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);

					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_LASER:
				{
					Bullet->SetBulletSound(pSelf->m_anBulletSounds[4]);
					CEventSystem::GetInstance()->SendEvent("shoot",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.15f);
					if(pMessage->GetFiringEntity()->GetOwner()->GetType() == OBJ_PLAYER)
						Bullet->SetWhoFired(true);
					else
						Bullet->SetWhoFired(false);
					if(pMessage->GetFiringEntity() != nullptr)
					{

						tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2f*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2f*abs(Up.fX));
							if(player->GetDoubleDamage())
								Bullet->SetDamage(2.0f*2);
							else
								Bullet->SetDamage(2.0f);
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
							Bullet->SetDamage(2.0f);
						}
						Bullet->SetVelX(norVec.fX*500);
						Bullet->SetVelY(norVec.fY*500);
					}


					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_LASER]);

					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_FLAME:
				{
					CTurret* tur=dynamic_cast<CCreateBulletMessage*>(pMsg)->GetFiringEntity();
					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetScale(0.35f);
					float velocityX;
					float velocityY;
					tVector2D vel;
					tVector2D dir=pMessage->GetFiringEntity()->GetLook();
					do
					{
						velocityX=(float)(((rand()%361)/180.0)-1.0);
						velocityY=(float)(((rand()%361)/180.0)-1.0);
						vel.fX=velocityX;
						vel.fY=velocityY;
					}while(abs(AngleBetweenVectors(tur->GetFlamer()->GetDir(), vel))>abs(AngleBetweenVectors(tur->GetFlamer()->GetDir(), Vector2DRotate(tur->GetFlamer()->GetDir(), tur->GetFlamer()->GetAngle()))));
					Bullet->SetVelX(vel.fX*200);
					Bullet->SetVelY(vel.fY*200);
					Bullet->SetWhoFired(true);
					Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*dir.fX-C->GetPosX()+11.2f*abs(dir.fY));
					Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*dir.fY-C->GetPosY()+11.2f*abs(dir.fX));
					Bullet->SetBulletType(BUL_FLAME);
					Bullet->SetFlameTimer(1.0f);
					if(player->GetDoubleDamage())
						Bullet->SetDamage(1.0f*2);
					else
						Bullet->SetDamage(1.0f);
					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			};

		}
		break;
	case MSG_DESTROYBULLET:
		{
			CBullet* pBullet = dynamic_cast<CDestroyBulletMessage*>(pMsg)->GetBullet();
			pSelf->m_pOM->RemoveObject(pBullet);
			
		}
		break;
	case MSG_CREATEENEMY:
		{
			CCreateEnemyMessage* pMessage = dynamic_cast<CCreateEnemyMessage*>(pMsg);
			switch(pMessage->GetEnemyType())
			{
			case SAPPER:
				{
					CSapper* sapper =(CSapper*)pSelf->m_pOF->CreateObject("CSapper");
					sapper->SetSoldierSounds(pSelf->m_anSoldierSounds);
					sapper->SetExplode(pSelf->m_nSappSound);
					sapper->SetPosX(pMessage->GetPosX());
					sapper->SetPosY(pMessage->GetPosY());
					sapper->SetHeight(32);
					sapper->SetWidth(32);
					CPlayer* player = CPlayer::GetInstance();
					sapper->SetPlayer(player);
					sapper->SetSight(100000);
					loop:
					for(unsigned int i = 0; i < pSelf->m_vRECTS.size();i++)
					{
						RECT* temp = new RECT;
						do 
						{
							if(IntersectRect(temp,&sapper->GetRect(),&pSelf->m_vRECTS[i]))
							{
								sapper->SetPosX(float(rand()%2264+644));
								sapper->SetPosY(float(rand()%2264+644));
							}
							else 
								break;

						} while (true);
						temp = nullptr;
					}
					for(unsigned int k = 0; k < pSelf->m_vRECTS.size();k++)
					{
						RECT* temp2 = new RECT;
						if(IntersectRect(temp2,&sapper->GetRect(),&pSelf->m_vRECTS[k]))
						{
							goto loop;
						}
						temp2 = nullptr;
					}
					
					if(pMessage->GetKind() == 0)
					{
						sapper->SetVelX(45.0f);
						sapper->SetVelY(45.0f);
						sapper->SetHealth(35);
						sapper->SetMaxHealth(35);
						sapper->SetDamage(10.0f);
						sapper->SetImageID(pSelf->m_anEnemyIDs[1]);
					}
					else if(pMessage->GetKind() == 1)
					{
						sapper->SetVelX(55.0f);
						sapper->SetVelY(55.0f);
						sapper->SetHealth(60);
						sapper->SetDamage(15);
						sapper->SetMaxHealth(60);
						sapper->SetDamage(20.0f);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/AlienSapper.png"));
						sapper->SetImageID(nID);

					}
					else if(pMessage->GetKind() == 2)
					{
						sapper->SetVelX(65.0f);
						sapper->SetVelY(65.0f);
						sapper->SetHealth(100);
						sapper->SetMaxHealth(100);
						sapper->SetDamage(20);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/RobotSapper.png"),D3DCOLOR_ARGB(255,255,255,255));
						sapper->SetImageID(nID);
					}
					sapper->SetExplosion(pSelf->m_PM->GetEmitter(pSelf->FXSapper_Explosion));
					sapper->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(sapper);
					sapper->Release();
					sapper = nullptr;



				}
				break;
			case TANK:
				{
					// TO DO: SET UP MESSAGES TO GET POSITIONS
					pSelf->m_pEnemy = pSelf->m_pOF->CreateObject("CTank");
					
					pSelf->m_pEnemy->SetPosX(pMessage->GetPosX());
					pSelf->m_pEnemy->SetPosY(pMessage->GetPosY());	
					pSelf->m_pEnemy->SetWidth(64);
					pSelf->m_pEnemy->SetHeight(128);
					CPlayer* player = CPlayer::GetInstance();
					CTank* tank = dynamic_cast<CTank*>(pSelf->m_pEnemy);
					tank->SetPlayer(player);
					tank->SetRotation(0);
					tank->SetRotationRate(0.75f);
					tank->SetSight(10000);
				
					tankloop:
					for(unsigned int i = 0; i < pSelf->m_vRECTS.size();i++)
					{
						RECT* temp = new RECT;
						do 
						{
							if(IntersectRect(temp,&tank->GetSpawnRect(),&pSelf->m_vRECTS[i]))
							{
								tank->SetPosX(float(rand()%2264+644));
								tank->SetPosY(float(rand()%2264+644));
							}
							else
								break;

						} while (true);
						temp = nullptr;
					}
					for(unsigned int k = 0; k < pSelf->m_vRECTS.size();k++)
					{
						RECT* temp2 = new RECT;
							RECT potato = tank->GetSpawnRect();
						if(IntersectRect(temp2,&tank->GetSpawnRect(),&pSelf->m_vRECTS[k]))
						{
							goto tankloop;
						}
						temp2 = nullptr;
					}
					//RECT* potato = new RECT;
					//potato = &tank->GetSpawnRect();
					pSelf->m_vRECTS.push_back(tank->GetSpawnRect());
					tank->SetHasATurret(true);
					pSelf->m_pOM->AddObject(tank);
					pSelf->m_pTurret = pSelf->m_pOF->CreateObject("CTurret");
									
					pSelf->m_pTurret->SetPosX(pSelf->m_pEnemy->GetPosX());
					pSelf->m_pTurret->SetPosY(pSelf->m_pEnemy->GetPosY());
					pSelf->m_pTurret->SetWidth(64);
					pSelf->m_pTurret->SetHeight(128);
					if(pMessage->GetKind() == 0)
					{
						tank->SetVelX(30);
						tank->SetVelY(30);
						tank->SetHealth(200);
						tank->SetMaxHealth(200);
						tank->SetDamage(20);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/enemyTank.png"));
						pSelf->m_pEnemy->SetImageID(nID);
						int nIDTurret = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/enemyTurret.png"));
						pSelf->m_pTurret->SetImageID(nIDTurret);	
						pSelf->m_pTurret->SetDamage(15);
					}
					else if(pMessage->GetKind() == 1)
					{
						tank->SetVelX(40);
						tank->SetVelY(40);
						tank->SetHealth(300);
						tank->SetMaxHealth(300);
						tank->SetDamage(20);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/RobotTankBase.png"));
						pSelf->m_pEnemy->SetImageID(nID);
						int nIDTurret = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/RobotTankTurret.png"));
						pSelf->m_pTurret->SetImageID(nIDTurret);	
						pSelf->m_pTurret->SetDamage(20);
					}
					else if(pMessage->GetKind() == 2)
					{
						tank->SetVelX(50);
						tank->SetVelY(50);
						tank->SetHealth(400);
						tank->SetMaxHealth(400);
						tank->SetDamage(20);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/AlienTankBase.png"));
						pSelf->m_pEnemy->SetImageID(nID);
						int nIDTurret = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/AlienTankTurret.png"));
						pSelf->m_pTurret->SetImageID(nIDTurret);	
						pSelf->m_pTurret->SetDamage(25);
					}

					CTurret* turret = dynamic_cast<CTurret*>(pSelf->m_pTurret);
					tank->SetTurret(turret);
					turret->SetOwner(pSelf->m_pEnemy);
					turret->SetBullet(BUL_LASER);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(1000);
					//pTurret->SetFireRate(2.5f);
					turret->SetTarget(player);
					turret->SetRotationRate(1.0f);
					pSelf->m_pOM->AddObject(pSelf->m_pTurret);
					pSelf->m_pTurret->Release();
					pSelf->m_pEnemy->Release();
					pSelf->m_pEnemy = nullptr;
					pSelf->m_pTurret = nullptr;
				}
				break;
			case TURRET:
				{
					// TO DO: SET UP MESSAGE TO GET POSITIONS
					CPlayer* player = CPlayer::GetInstance();

					pSelf->m_pTurret = pSelf->m_pOF->CreateObject("CTurret");
					pSelf->m_pTurret->SetImageID(pSelf->m_nPlayerTurretID);					
					pSelf->m_pTurret->SetPosX(pMessage->GetPosX());
					pSelf->m_pTurret->SetPosY(pMessage->GetPosY());
					pSelf->m_pTurret->SetWidth(64);
					pSelf->m_pTurret->SetHeight(128);

					CTurret* turret = dynamic_cast<CTurret*>(pSelf->m_pTurret);

					turret->SetOwner(nullptr);
					turret->SetBullet(BUL_SHELL);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
					//turret->SetFireRate(2.5f);
					turret->SetTarget(player);
					turret->SetRotationRate(1.0f);
					pSelf->m_pOM->AddObject(turret);
					pSelf->m_pTurret->Release();
					pSelf->m_pTurret = nullptr;

				}
				break;

			case RIFLE:
				{
					CPlayer* player = CPlayer::GetInstance();
					CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
					enemy->SetEType(RIFLE);
					enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
					enemy->SetPosX(pMessage->GetPosX());
					enemy->SetPosY(pMessage->GetPosY());
					enemy->SetHeight(32);
					enemy->SetWidth(32);
					enemy->SetPlayer(player);
					enemy->SetDamage(1);
					enemy->SetMaxDistance(10000);
					rifleloop:
					for(unsigned int i = 0; i < pSelf->m_vRECTS.size();i++)
					{
						RECT* temp = new RECT;
						do 
						{
							if(IntersectRect(temp,&enemy->GetRect(),&pSelf->m_vRECTS[i]))
							{
								enemy->SetPosX(float(rand()%2264+644));
								enemy->SetPosY(float(rand()%2264+644));
							}
							else
								break;

						} while (true);
						temp = nullptr;
					}
					for(unsigned int k = 0; k < pSelf->m_vRECTS.size();k++)
					{
						RECT* temp2 = new RECT;
						RECT potato = enemy->GetRect();
						if(IntersectRect(temp2,&enemy->GetRect(),&pSelf->m_vRECTS[k]))
						{
							goto rifleloop;
						}
						temp2 = nullptr;
					}
					if(pMessage->GetKind() == 0)
					{
						enemy->SetVelX(45);
						enemy->SetVelY(45);
						enemy->SetHealth(50);
						enemy->SetMaxHealth(50);
						enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
						enemy->SetDamage(1);
					}
					else if(pMessage->GetKind() == 1)
					{
						enemy->SetVelX(55);
						enemy->SetVelY(55);
						enemy->SetHealth(60);
						enemy->SetMaxHealth(60);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/AlienSoldier.png"),0);
						enemy->SetImageID(nID);
						enemy->SetDamage(1);

					}
					else if(pMessage->GetKind() == 2)
					{
						enemy->SetVelX(65);
						enemy->SetVelY(65);
						enemy->SetHealth(70);
						enemy->SetMaxHealth(70);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/RobotSoldier.png"),0);
						enemy->SetImageID(nID);
						enemy->SetDamage(1);
					}
					enemy->SetMinDistance(200);
					enemy->SetMaxDistance(600);
					enemy->SetShotTimer(0.1f);
					enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(enemy);
					enemy->Release();
				}
				break;
			case ROCKET:
				{
					CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
					enemy->SetEType(ROCKET);
					enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
					enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
					enemy->SetPosX(pMessage->GetPosX());
					enemy->SetPosY(pMessage->GetPosY());
					enemy->SetHeight(64);
					enemy->SetWidth(32);
					enemy->SetPlayer(CPlayer::GetInstance());
					enemy->SetMaxDistance(10000);
					enemy->SetVelX(45);
					enemy->SetVelY(45);
					enemy->SetHealth(50);
					enemy->SetMaxHealth(50);
					enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
					rocketloop:
					for(unsigned int i = 0; i < pSelf->m_vRECTS.size();i++)
					{
						RECT* temp = new RECT;
						do 
						{
							if(IntersectRect(temp,&enemy->GetRect(),&pSelf->m_vRECTS[i]))
							{
								enemy->SetPosX(float(rand()%2264+644));
								enemy->SetPosY(float(rand()%2264+644));
							}
							else
								break;

						} while (true);
						temp = nullptr;
					}
					for(unsigned int k = 0; k < pSelf->m_vRECTS.size();k++)
					{
						RECT* temp2 = new RECT;
						RECT potato = enemy->GetRect();
						if(IntersectRect(temp2,&enemy->GetRect(),&pSelf->m_vRECTS[k]))
						{
							goto rocketloop;
						}
						temp2 = nullptr;
					}
					if(pMessage->GetKind() == 0)
					{
						enemy->SetVelX(45);
						enemy->SetVelY(45);
						enemy->SetHealth(50);
						enemy->SetMaxHealth(50);
						enemy->SetDamage(10);
						enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/Rocketeer.png"),0);
					}
					else if(pMessage->GetKind() == 1)
					{
						enemy->SetVelX(55);
						enemy->SetVelY(55);
						enemy->SetHealth(60);
						enemy->SetMaxHealth(60);
						enemy->SetDamage(10);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/AlienRocket.png"),0);
						enemy->SetImageID(nID);

					}
					else if(pMessage->GetKind() == 2)
					{
						enemy->SetVelX(65);
						enemy->SetVelY(65);
						enemy->SetHealth(70);
						enemy->SetMaxHealth(70);
						enemy->SetDamage(10);
						int nID = pSelf->m_pTM->LoadTexture( _T( "resource/graphics/RobotRocket.png"),0);
						enemy->SetImageID(nID);
					}
					enemy->SetMinDistance(200);
					enemy->SetMaxDistance(600);
					enemy->SetShotTimer(3.0f);
					enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(enemy);
					enemy->Release();
					enemy = nullptr;
				}
				break;
			default:
				{
				}
				break;
			};
		}
		break;
	case MSG_DESTROYENEMY:
		{
			CEnemy* pEnemy = dynamic_cast<CDestroyEnemyMessage*>(pMsg)->GetEnemy();
			CEventSystem::GetInstance()->SendEvent("explode",pEnemy);
			pSelf->m_PM->RemoveAttachedEmitter(pEnemy->GetTail());
			
				pSelf->m_nNumUnits--;
			int score = CPlayer::GetInstance()->GetScore()+int(pEnemy->GetMaxHealth()/2)+20;
			CPlayer::GetInstance()->SetScore(score);
			if(pEnemy->GetHealth() <= 0)
			{
				int nRandNum = rand()%12;
				if(nRandNum <= 7)
				{
					CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,pEnemy,nRandNum);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
			}
			pSelf->m_pOM->RemoveObject(pEnemy);
		}
		break;
	case MSG_DESTROYTURRET:
		{
			CTurret* pTurret = dynamic_cast<CDestroyTurretMessage*>(pMsg)->GetTurret();
			pSelf->m_pOM->RemoveObject(pTurret);
		}
		break;	
	case MSG_DESTROYBUILDING:
		{
			dynamic_cast<CDestroyBuildingMessage*>(pMsg)->GetBuilding()->GetFlames()->ActivateEmitter();
			dynamic_cast<CDestroyBuildingMessage*>(pMsg)->GetBuilding()->SetDead(true);
		}
		break;
	case MSG_CREATEPICKUP:
		{
			CEntity* pEntity = pSelf->m_pOF->CreateObject("CPickup");
			CPickup* pPickup = dynamic_cast<CPickup*>(pEntity);
			CCreatePickupMessage* pMessage = dynamic_cast<CCreatePickupMessage*>(pMsg);
			pPickup->SetWidth(32);
			pPickup->SetHeight(32);
			switch(pMessage->GetPickUpType())
			{
			case 0:
				{
					pPickup->SetImageID(pSelf->m_nPickupHealthID);
					pPickup->SetGiven(50);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 1:
				{
					pPickup->SetImageID(pSelf->m_nPickupAmmoID);
					pPickup->SetGiven(50);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 2:
				{
					pPickup->SetImageID(pSelf->m_nPickupArmorID);
					pPickup->SetGiven(50);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 3:
				{
					pPickup->SetImageID(pSelf->m_nPickupDoubleDID);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 4:
				{
					pPickup->SetImageID(pSelf->m_nPickupNoReloadID);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 5:
				{
					pPickup->SetImageID(pSelf->m_nPickupInvuID);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 6:
				{
					pPickup->SetImageID(pSelf->m_nPickupInfAmmoID);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			case 7:
				{
					pPickup->SetImageID(pSelf->m_nPickupMoneyID);
					pPickup->SetGiven(50);
					pPickup->SetPickUpType(pMessage->GetPickUpType());
				}
				break;
			}

			pPickup->SetPosX(pMessage->GetEntity()->GetPosX());
			pPickup->SetPosY(pMessage->GetEntity()->GetPosY());

			pPickup->SetAliveTime(25.0f);

			pSelf->m_pOM->AddObject(pPickup);

			pPickup->Release();
			pPickup = nullptr;
		}
		break;
	case MSG_DESTROYPICKUP:
		{
			CPickup* pPickup = dynamic_cast<CDestroyPickupMessage*>(pMsg)->GetPickUp();
			pSelf->m_pOM->RemoveObject(pPickup);
		}
		break;
	case MSG_CREATEBUILDING:
		{

			CCreateBuildingMessage *pMessage = dynamic_cast<CCreateBuildingMessage*>(pMsg);

			CEntity* m_pBuilding = pSelf->m_pOF->CreateObject("CBuilding");
			m_pBuilding->SetPosX(pMessage->GetPosX());
			m_pBuilding->SetPosY(pMessage->GetPosY());
			m_pBuilding->SetHeight(128);
			m_pBuilding->SetWidth(128);
			m_pBuilding->SetHealth(50);
			m_pBuilding->SetImageID(pSelf->m_anEnemyIDs[2]);

			CBuilding* pBuilding = dynamic_cast<CBuilding*>(m_pBuilding);
			pBuilding->SetFlames(pSelf->m_PM->GetEmitter(pSelf->FXBuildingFlame));
			pBuilding->SetSpawn(pMessage->GetType());
			pBuilding->SetCanSpawn(pMessage->GetSpawn());
			pBuilding->SetSpawnTime(pMessage->GetTime());
			pBuilding->SetPlayer((CPlayer*)pSelf->m_pPlayer);
			pBuilding->SetRange(500);
			pSelf->m_pOM->AddObject(m_pBuilding);

			m_pBuilding->Release();
		}
		break;
	case MSG_CREATEMINE:
		{
		}
		break;
	case MSG_DESTROYMINE:
		{
		}
		break;
	case MSG_SOLDIERFIRE:
		{
			CBullet* pBullet = (CBullet*)pSelf->m_pOF->CreateObject("CBullet");
			SoldierFireMessage* pMessage = dynamic_cast<SoldierFireMessage*>(pMsg);
			tVector2D Up={0,-1};
			Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
			pBullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+(pMessage->GetFiringEntity()->GetWidth())*Up.fX);
			pBullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+(pMessage->GetFiringEntity()->GetHeight())*Up.fY);
			switch(pMessage->GetBulletType())
			{
			case BUL_SHELL:
				{
					pBullet->SetBulletSound(pSelf->m_anBulletSounds[3]);
					CEventSystem::GetInstance()->SendEvent("shoot",pBullet);
					
					tVector2D norVec = Vector2DNormalize(Up);
					pBullet->SetWidth(32);
					pBullet->SetHeight(32);
					pBullet->SetScale(0.35f);
					pBullet->SetWhoFired(false);
					pBullet->SetVelX(norVec.fX*400);
					pBullet->SetVelY(norVec.fY*400);
					pBullet->SetDamage((float)pMessage->GetFiringEntity()->GetDamage());
					pBullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pBullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			case BUL_ROCKET:
				{
					pBullet->SetBulletSound(pSelf->m_anBulletSounds[0]);
					CEventSystem::GetInstance()->SendEvent("shoot",pBullet);

					tVector2D norVec = Vector2DNormalize(Up);
					pBullet->SetWidth(32);
					pBullet->SetHeight(32);
					pBullet->SetScale(0.35f);
					pBullet->SetWhoFired(false);
					pBullet->SetVelX(300);
					pBullet->SetVelY(300);
					pBullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
					pBullet->SetDamage((float)pMessage->GetFiringEntity()->GetDamage());
					if(pMessage->GetFiringEntity()->GetType() == OBJ_ENEMY)
					{
						pBullet->SetTargetRect(pSelf->m_pPlayer->GetRect());					
						tVector2D vPos = {pSelf->m_pPlayer->GetPosX()-C->GetPosX(), pSelf->m_pPlayer->GetPosY()-C->GetPosY()};
						pBullet->SetTargetPos(vPos);
					}
					else if(pMessage->GetFiringEntity()->GetType() == OBJ_HELP)
					{
						pBullet->SetTargetRect(pMessage->GetFiringEntity()->GetHelpTarget()->GetRect());					
						tVector2D vPos = {pMessage->GetFiringEntity()->GetHelpTarget()->GetPosX()-C->GetPosX(), pMessage->GetFiringEntity()->GetHelpTarget()->GetPosY()-C->GetPosY()};
						pBullet->SetTargetPos(vPos);
						pBullet->SetWhoFired(true);
					}
					pBullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_ROCKET]);
					pBullet->SetBulletType(BUL_ROCKET);
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			}

		}
		break;
	};
}

bool CSurvivalState::LoadWave(const char* szFileName, int nGamedata)
{
		// Create a TinyXML Document
	TiXmlDocument document;
	// Attempt to load the document from the file
	m_nCurrWave = 0;
	if(document.LoadFile(szFileName) == false)
	{
		return false;
	}

	// Access the root node (Frame_List) in the document
	TiXmlElement* pRoot = document.RootElement();
	if(pRoot == nullptr)
		return false;

	int howMany;
	pRoot->Attribute("Number",&howMany);
	this->m_nWavesRemaining = howMany;
	TiXmlElement* pUnit = pRoot->FirstChildElement("Wave");
	
	for (int i = 0; i < howMany; i++)
	{
		cout<<"Wave "<<i<<endl;
		CWave* wave = new CWave;
		TiXmlElement* pSapper = pUnit->FirstChildElement("Sappers");
		int nNumSappers = atoi(pSapper->FirstChild()->Value());
		wave->m_nSap = nNumSappers;
		
		TiXmlElement* pFootSoldier = pUnit->FirstChildElement("FootSoldiers");
		int nNumFootSoldeirs = atoi(pFootSoldier->FirstChild()->Value());
		wave->m_nFoot = nNumFootSoldeirs;
		

		TiXmlElement* pRocketeer = pUnit->FirstChildElement("Rocketeers");
		int nNumRocketeers = atoi(pRocketeer->FirstChild()->Value());
		wave->m_nRocket = nNumRocketeers;

		TiXmlElement* pTank = pUnit->FirstChildElement("Tanks");
		int nNumTanks = atoi(pTank->FirstChild()->Value());
		wave->m_nTanks = nNumTanks;

		m_vWave.push_back(wave);
		pUnit = pUnit->NextSiblingElement();
		wave = nullptr;
		//wave = nullptr;
	}
		
	cout<<"All Waves Loaded\n";
	GenerateWave();
	return true;

}

void CSurvivalState::GenerateWave()
{
	m_vRECTS.clear();
	m_vRECTS.push_back(m_pPlayer->GetRect());
	m_nWavesRemaining = 100;

	cout<<"CurrWave "<<m_nCurrWave<<endl;
	
	for(int i = 0; i < m_vWave[m_nCurrWave]->m_nSap; i++)
	{
		CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, SAPPER, float(rand()%2064+544), float(rand()%1828+544), rand()%3);
		CMessageSystem::GetInstance()->SndMessage(msg);
		msg = nullptr;
		m_nNumUnits++;
		
	}

	for(int i = 0; i < m_vWave[m_nCurrWave]->m_nFoot; i++)
	{
	CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, RIFLE, float(rand()%2064+544), float(rand()%2228+544), rand()%3);
	CMessageSystem::GetInstance()->SndMessage(msg);
	msg = nullptr;
	m_nNumUnits++;
	}

	for(int i = 0; i < m_vWave[m_nCurrWave]->m_nRocket; i++)
	{
	CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, ROCKET, float(rand()%2064+544), float(rand()%2228+544), rand()%3);
	CMessageSystem::GetInstance()->SndMessage(msg);
	msg = nullptr;
	m_nNumUnits++;
	}

	for(int i = 0; i < m_vWave[m_nCurrWave]->m_nTanks; i++)
	{
		CCreateEnemyMessage* msg=new CCreateEnemyMessage(MSG_CREATEENEMY, TANK, float(rand()%2064+544), float(rand()%2528+544), rand()%3);
		CMessageSystem::GetInstance()->SndMessage(msg);
		msg = nullptr;
		m_nNumUnits++;
	}
}

void CSurvivalState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("SurvivalState");
				TiXmlNode* pButton = pState->FirstChild("Wave");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sWave=pText->Value();
				pButton = pState->FirstChild("Paused");
				pText = pButton->FirstChild()->ToText();
				m_sPaused=pText->Value();
				pButton=pState->FirstChild("Resume");
				pText = pButton->FirstChild()->ToText();
				m_sResume=pText->Value();
				pButton = pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("SurvivalState");
				TiXmlNode* pButton = pState->FirstChild("Wave");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sWave=pText->Value();
				pButton = pState->FirstChild("Paused");
				pText = pButton->FirstChild()->ToText();
				m_sPaused=pText->Value();
				pButton=pState->FirstChild("Resume");
				pText = pButton->FirstChild()->ToText();
				m_sResume=pText->Value();
				pButton = pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("SurvivalState");
				TiXmlNode* pButton = pState->FirstChild("Wave");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sWave=pText->Value();
				pButton = pState->FirstChild("Paused");
				pText = pButton->FirstChild()->ToText();
				m_sPaused=pText->Value();
				pButton=pState->FirstChild("Resume");
				pText = pButton->FirstChild()->ToText();
				m_sResume=pText->Value();
				pButton = pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		case 3:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("German");
				TiXmlNode* pState = pLanguage->FirstChild("SurvivalState");
				TiXmlNode* pButton = pState->FirstChild("Wave");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sWave=pText->Value();
				pButton = pState->FirstChild("Paused");
				pText = pButton->FirstChild()->ToText();
				m_sPaused=pText->Value();
				pButton=pState->FirstChild("Resume");
				pText = pButton->FirstChild()->ToText();
				m_sResume=pText->Value();
				pButton = pState->FirstChild("Options");
				pText = pButton->FirstChild()->ToText();
				m_sOptions=pText->Value();
				pButton=pState->FirstChild("Exit");
				pText = pButton->FirstChild()->ToText();
				m_sExit=pText->Value();
			}
			break;
		}
	}
}

void CSurvivalState::TurnSoundOff(void)
{
	if(SoundOff == true)
		return;
	SoundOff = true;

	CPlayer *player = CPlayer::GetInstance();

	player->SetNukeSound(-1);
	player->SetFireSound(-1);

	if(m_nGameMusic != -1)
	{
		if(m_pAudio->MusicIsSongPlaying(m_nGameMusic) == true)
			m_pAudio->MusicStopSong(m_nGameMusic);

		m_pAudio->MusicUnloadSong(m_nGameMusic);
		m_nGameMusic = -1;
	}

	if(m_nNukeSound != -1)
	{
		if(m_pAudio->SFXIsSoundPlaying(m_nNukeSound) == true)
			m_pAudio->SFXStopSound(m_nNukeSound);

		m_pAudio->SFXUnloadSound(m_nNukeSound);
		m_nNukeSound = -1;
	}

	if(m_nSappSound != -1)
	{
		if(m_pAudio->SFXIsSoundPlaying(m_nSappSound) == true)
			m_pAudio->SFXStopSound(m_nSappSound);

		m_pAudio->SFXUnloadSound(m_nSappSound);
		m_nSappSound = -1;
	}

	for(int i = 0; i < 6; i++)
	{
		if(m_anBulletSounds[i] != -1)
		{
			if(m_pAudio->SFXIsSoundPlaying(m_anBulletSounds[i]) == true)
				m_pAudio->SFXStopSound(m_anBulletSounds[i]);

			m_pAudio->SFXUnloadSound(m_anBulletSounds[i]);
			m_anBulletSounds[i] = -1;
		}

	}

	for(int i = 0; i < 9; i++)
	{
		if(m_anSoldierSounds[i] != -1)
		{
			if(m_pAudio->SFXIsSoundPlaying(m_anSoldierSounds[i]) == true)
				m_pAudio->SFXStopSound(m_anSoldierSounds[i]);

			m_pAudio->SFXUnloadSound(m_anSoldierSounds[i]);
			m_anSoldierSounds[i] = -1;
		}

	}
}