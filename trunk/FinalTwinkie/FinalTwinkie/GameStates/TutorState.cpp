#include "TutorState.h"
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
#include "../Event and Messages/CreateTreeMessage.h"
#include "../Event and Messages/DestroyTreeMessage.h"
#include "../Event and Messages/CreateFlyTextMessage.h"
#include "../Event and Messages/DestroyFlyTextMessage.h"
#include "../Event and Messages/DestrotJetMessage.h"
#include "../Event and Messages/CreateJetMessage.h"
#include "../World and Tile/Tile.h"
#include "../World and Tile/TileManager.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Turret.h"
#include "../GameObjects/Mine.h"
#include "../GameObjects/Tree.h"
#include "../GameObjects//Jet.h"
#include "../Headers/Camera.h"
#include "../GameObjects/Sapper.h"
#include "../GameObjects/Tank.h"
#include "../Particle/Emitter.h"
#include "../GameObjects/Building.h"
#include "../PickUps and Specials/Pickup.h"
#include "../Event and Messages/CreatePickupMessage.h"
#include "../Event and Messages/DestroyPickupMessage.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
#include "ShopState.h"
#include "../Headers/FlyText.h"
#include "../Headers/GUI.h"
#include "../PickUps and Specials/Special.h"
#include "../PickUps and Specials/Nuke.h"
#include "../PickUps and Specials/Smoke.h"
#include "StatState.h"

CTutorState* CTutorState::m_pSelf = nullptr;

CTutorState* CTutorState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CTutorState;
	return m_pSelf;
}

void CTutorState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CTutorState::CTutorState(void)
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
	m_pAudio = nullptr;


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

	m_nPickupHealthID = -1;
	m_nPickupAmmoID = -1;
	m_nPickupArmorID = -1;
	m_nPickupDoubleDID = -1;
	m_nPickupNoReloadID = -1;
	m_nPickupInvuID = -1;
	m_nPickupInfAmmoID = -1;
	m_nPickupMoneyID = -1;
	m_nLevel = 1;
	WinnerID = -1;
	GameOverID = -1;
	m_nBox = -1;
	m_nMine = -1;
	m_nTree = -1;
	m_nDeadTree = -1;
	m_nBarricade = -1;
	m_nDeadBarr = -1;
	m_nGameMusic = -1;
	m_nMineSound = -1;
	m_nSappSound = -1;
	m_nNukeSound = -1;
	m_nDeadBullet = -1;
	for(int i = 0; i < 6; i++)
		m_anBulletSounds[i] = -1;

	for(int i = 0; i < 9; i++)
		m_anSoldierSounds[i] = -1;

	m_nEnemyCount = 0;
	gameEndTimer = 0.0f;
	m_bWinner = false;
	m_bGameOver = false;
	m_fWordTimer = 0.0f;

	for(int i = 0; i < 3; ++i)
		m_anSupportIDs[i] = -1;
}

CTutorState::~CTutorState(void)
{
}

void CTutorState::Enter(void)
{
	CGame::GetInstance()->isTutor = true;
	m_bActivePad = false;
	SoundOff = false;
	LoadWords();
	if(m_bPaused == false)
	{
		m_nEnemyCount = 0;

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
		m_pFont = CBitmapFont::GetInstance();
		m_pFont->Init(COptionsState::GetInstance()->GetLang());
		m_pAudio = CSGD_XAudio2::GetInstance();

		m_pDI->ClearInput();
		for(int i = 0; i < 16; ++i)
		{
			m_anEnemyIDs[i] = m_pTM->LoadTexture( _T( "resource/graphics/JF_enemy1.png"), 	0 );
		}

		m_AM->Load("AnimationInfo.xml");
		//m_AM->Save("AnimationInfo.xml");

		m_nBackGround = m_pTM->LoadTexture(_T("resource/graphics/loading.jpg"));

		m_pD3D->Clear( 0, 255, 255 );// Clear the background

		// Start D3D rendering
		m_pD3D->DeviceBegin();
		m_pD3D->SpriteBegin();	

		m_pTM->Draw(m_nBackGround,0,0,0.8f,0.6f);
	
		m_pD3D->GetSprite()->Flush();	
		m_pD3D->SpriteEnd();
		m_pD3D->DeviceEnd();	

		m_pD3D->Present();
		
		GameOverID = m_pTM->LoadTexture(_T("resource/graphics/gameover.png"));
		WinnerID = m_pTM->LoadTexture(_T("resource/graphics/winner.png"));
		

		FXEnemy_Tails=m_PM->AddEmitter("resource/files/Enemy_Trail.xml");
		FXSapper_Explosion=m_PM->AddEmitter("resource/files/Explosion.xml");
		FXFlame=m_PM->AddEmitter("resource/files/Flame.xml");
		FXBuildingFlame=m_PM->AddEmitter("resource/files/Building Flame.xml");
		FXNuke=m_PM->AddEmitter("resource/files/Nuke.xml");
		FXTreads=m_PM->AddEmitter("resource/files/Tracks.xml");
		FXSmoke=m_PM->AddEmitter("resource/files/Smoke.xml");
		FXEnemyOnFire=m_PM->AddEmitter("resource/files/OnFire.xml");
		FXAirStrike = m_PM->AddEmitter("resource/files/AirStrike.xml");

		m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
		m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 0 );
		m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[4] = m_pTM->LoadTexture( _T( "resource/graphics/Laser.png"), 	0 );
		m_nPlayerID=m_pTM->LoadTexture(_T("resource/graphics/Green Base.png"));
		m_nPlayerTurretID=m_pTM->LoadTexture(_T("resource/graphics/Green Turret.png"));
		m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/sapper_pirate.png"));
		m_anEnemyIDs[2]=m_pTM->LoadTexture(_T("resource/graphics/Building.png"));
		m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
		m_anEnemyIDs[3]=m_pTM->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
		m_anEnemyIDs[4]=m_pTM->LoadTexture(_T("resource/graphics/missile.png"));
		m_anEnemyIDs[5]=m_pTM->LoadTexture(_T("resource/graphics/rubble.png"));
		m_anEnemyIDs[6]=m_pTM->LoadTexture(_T("resource/graphics/enemyTank.png"));
		m_anEnemyIDs[7]=m_pTM->LoadTexture(_T("resource/graphics/enemyTurret.png"));
		m_anEnemyIDs[8]=m_pTM->LoadTexture(_T("resource/graphics/SpecialSelect.png"));

		m_anEnemyIDs[13]=m_pTM->LoadTexture(_T("resource/graphics/GunSel.png"));
		m_anEnemyIDs[14]=m_pTM->LoadTexture(_T("resource/graphics/Rifle_Pirate.png"));
		m_anEnemyIDs[15]=m_pTM->LoadTexture(_T("resource/graphics/Rocketeer.png"));

		m_nPickupHealthID = m_pTM->LoadTexture(_T("resource/graphics/HealthPickUp.png"));
		m_nPickupAmmoID = m_pTM->LoadTexture(_T("resource/graphics/AmmoPickUp.png"));
		m_nPickupArmorID = m_pTM->LoadTexture(_T("resource/graphics/ArmorPickUp.png"));
		m_nPickupDoubleDID = m_pTM->LoadTexture(_T("resource/graphics/DoubleDamagePickUp.png"));
		m_nPickupNoReloadID = m_pTM->LoadTexture(_T("resource/graphics/NoReloadPickUp.png"));
		m_nPickupInvuID = m_pTM->LoadTexture(_T("resource/graphics/InvulnerabilityPickUp.png"));
		m_nPickupInfAmmoID = m_pTM->LoadTexture(_T("resource/graphics/InfAmmoPickUp.png"));
		m_nPickupMoneyID = m_pTM->LoadTexture(_T("resource/graphics/MoneyPickUp.png"));

		m_nTree = m_pTM->LoadTexture(_T("resource/graphics/tree.png"));
		m_nMine = m_pTM->LoadTexture(_T("resource/graphics/Mine.png"));
		m_nDeadTree = m_pTM->LoadTexture(_T("resource/graphics/stump.png"));
		m_nBarricade =m_pTM->LoadTexture(_T("resource/graphics/barr2.png"));
		m_nDeadBarr = m_pTM->LoadTexture(_T("resource/graphics/barr1.png"));
		m_nBox = m_pTM->LoadTexture(_T("resource/graphics/textBox.jpg"));

		m_anSupportIDs[0] = m_pTM->LoadTexture(_T("resource/graphics/Support_Sapper.png"));
		m_anSupportIDs[1] = m_pTM->LoadTexture(_T("resource/graphics/Support_Rifle.png"));
		m_anSupportIDs[2] = m_pTM->LoadTexture(_T("resource/graphics/Support_Rocket.png"));

		// SOUNDS
		////////////////////////////////////////////////////////
		
		m_anBulletSounds[0] = m_pAudio->SFXLoadSound(_T("resource/sound/shell.wav"));
		m_anBulletSounds[1] = m_pAudio->SFXLoadSound(_T("resource/sound/rocket.wav"));
		m_anBulletSounds[2] = m_pAudio->SFXLoadSound(_T("resource/sound/artillery.wav"));
		m_anBulletSounds[3] = m_pAudio->SFXLoadSound(_T("resource/sound/machinegun.wav"));
		m_anBulletSounds[4] = m_pAudio->SFXLoadSound(_T("resource/sound/laser.wav"));
		m_anBulletSounds[5] = m_pAudio->SFXLoadSound(_T("resource/sound/fire.wav"));

		m_anSoldierSounds[0] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt1.wav"));
		m_anSoldierSounds[1] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt2.wav"));
		m_anSoldierSounds[2] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt3.wav"));
		m_anSoldierSounds[3] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt4.wav"));
		m_anSoldierSounds[4] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt5.wav"));
		m_anSoldierSounds[5] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt6.wav"));
		m_anSoldierSounds[6] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt7.wav"));
		m_anSoldierSounds[7] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt8.wav"));
		m_anSoldierSounds[8] = m_pAudio->SFXLoadSound(_T("resource/sound/hurt9.wav"));

		m_nMineSound = m_pAudio->SFXLoadSound(_T("resource/sound/mine.wav"));
		m_nSappSound = m_pAudio->SFXLoadSound(_T("resource/sound/sapper.wav"));
		m_nNukeSound = m_pAudio->SFXLoadSound(_T("resource/sound/nuke.wav"));
		m_nDeadBullet = m_pAudio->SFXLoadSound(_T("resource/sound/explode.wav"));
		
		///////////////////////////////////////////////////////
		//////////////////////////////////////////////////////
		m_pMS->InitMessageSystem(&MessageProc);

		m_pOF->RegisterClassType<CEntity>("CEntity");
		m_pOF->RegisterClassType<CEnemy>("CEnemy");
		m_pOF->RegisterClassType<CBullet>("CBullet");
		m_pOF->RegisterClassType<CTurret>("CTurret");
		m_pOF->RegisterClassType<CTank>("CTank");
		m_pOF->RegisterClassType<CSapper>("CSapper");
		m_pOF->RegisterClassType<CBuilding>("CBuilding");
		m_pOF->RegisterClassType<CPickup>("CPickup");
		m_pOF->RegisterClassType<CMine>("CMine");
		m_pOF->RegisterClassType<CTree>("CTree");
		m_pOF->RegisterClassType<CFlyText>("CFlyText");

		m_pPlayer=CPlayer::GetInstance();
		CPlayer* player=dynamic_cast<CPlayer*>(m_pPlayer);
		player->SetImageID(m_nPlayerID);
		player->SetFireSound(m_anBulletSounds[5]);
		player->SetNukeSound(m_nNukeSound);
		player->SetPosX(float(CGame::GetInstance()->GetWidth()/2));
		player->SetPosY(float(CGame::GetInstance()->GetHeight()/2));
		player->SetRotation(0);
		player->SetWidth(64);
		player->SetHeight(128);
		player->SetVelX(90);
		player->SetVelY(90);
		player->SetStartVelX(player->GetVelX());
		player->SetStartVelY(player->GetVelY());
		player->SetHealth(250);
		player->SetMaxHealth(250);
		player->SetArmor(50);
		player->SetMaxArmor(50);
		player->SetWeaponAmmo(40/*m_dGameData.nShellAmmo*/,40/*m_dGameData.nArtilleryAmmo*/,/*m_dGameData.nMissileAmmo*/40);
		player->SetMaxWeaponAmmo(40,40,40);
		player->SetMoney(0);
		tVector2D v2Pos = { player->GetPosX(), player->GetPosY() };
		CNuke* pNuke = new CNuke();
		pNuke->SetEmitter(m_PM->GetEmitter(FXNuke));
		CSmoke* pSmoke=new CSmoke();
		pSmoke->SetEmitter(m_PM->GetEmitter(FXSmoke));
		player->SetSpecial1(pNuke);
		player->SetSpecial2(pSmoke);
		player->SetSpecial1Ammo(1);
		player->SetSpecial2Ammo(2);
		pNuke = nullptr;
		pSmoke = nullptr;
		player->SetOldPos(v2Pos);
		player->SetSecondType(MACHINEGUN);
		//player->SetName(m_dGameData.szName);
		//player->SetEmitterLeft(m_PM->GetEmitter(FXTreads));
		//player->SetEmitterRight(m_PM->GetEmitter(FXTreads));
		player->SetRocketAccess(true);
		player->SetArtilleryAccess(true);
		player->SetGunSel(1);

		//buffs LEAVE ON ALL SET TO FALSE AND 0 TIME
		player->SetDoubleDamage(false);
		player->SetDamageTimer(0.0f);
		player->SetNoReloadTimer(0.0f);
		player->SetInvul(false);
		player->SetInvulTimer(0.0f);
		player->SetInfAmmo(false);
		player->SetInfoAmmoTimer(0.0f);

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
		PlayerTurret->SetRotationRate(1.0f);
		PlayerTurret->SetFlamer(m_PM->GetEmitter(FXFlame));

		// Create and add everything to the objectmanager first so player is always above
		m_pTile->Load("resource/files/tutorial.xml");
		m_pMS->ProcessMessages();
		m_pOM->AddObject(player);
		m_pOM->AddObject(PlayerTurret);
		PlayerTurret->Release();

		
		m_nPosition = 0;
		m_bPaused = false;

		m_pGUI->SetHudID(m_anEnemyIDs[3]);
		m_pGUI->SetPlayer(player);
		m_pGUI->SetSelect(m_anEnemyIDs[8]);
		m_pGUI->SetGunSel(m_anEnemyIDs[13]);
		m_pGUI->SetGunSelected(1);

		m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);

		
		m_nBoxIndex = 0;
		player->SetMoney(0);
	}
	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	D3DXCreateTexture(m_pD3D->GetDirect3DDevice(), 125, 120, 0, D3DUSAGE_RENDERTARGET|D3DUSAGE_AUTOGENMIPMAP, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &MiniMap); 
	m_bWinner = false;
	m_bGameOver = false;
	m_bWordBox = true;
	m_nBoxIndex = -1;
	gameEndTimer = 0.0f;
	m_fWordTimer = 0.0f;
	m_nButton = m_pAudio->SFXLoadSound(_T("resource/sound/button.wav"));
	m_nClick = m_pAudio->SFXLoadSound(_T("resource/sound/click.wav"));
	m_nGameMusic = m_pAudio->MusicLoadSong(_T("resource/sound/GameMusic.xwm"));
	if(m_nGameMusic != -1)
	{
		m_pAudio->MusicPlaySong(m_nGameMusic, true);
	}

}

void CTutorState::Exit(void)
{
	m_nEnemyCount = 0;
	m_nBoxIndex = 0;
	m_fWordTimer = 0.0f;

	CGame::GetInstance()->isTutor = false;

		m_PM->RemoveAllBaseEmitters();
		m_PM->DeleteInstance();

		if(WinnerID != -1)
		{
			m_pTM->UnloadTexture(WinnerID);
			WinnerID = -1;
		}

		if(m_nBox != -1)
		{
			m_pTM->UnloadTexture(m_nBox);
			m_nBox = -1;
		}

		if(m_nDeadTree != -1)
		{
			m_pTM->UnloadTexture(m_nDeadTree);
			m_nDeadTree = -1;
		}

		if(GameOverID != -1)
		{
			m_pTM->UnloadTexture(GameOverID);
			GameOverID = -1;
		}

		if(m_nMine != -1)
		{
			m_pTM->UnloadTexture(m_nMine);
			m_nMine = -1;
		}

		if(m_nBarricade != -1)
		{
			m_pTM->UnloadTexture(m_nBarricade);
			m_nBarricade = -1;
		}

		if(m_nDeadBarr != -1)
		{
			m_pTM->UnloadTexture(m_nDeadBarr);
			m_nDeadBarr = -1;
		}
		
		

		if(m_nTree != -1)
		{
			m_pTM->UnloadTexture(m_nTree);
			m_nTree = -1;
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

		if(m_pMS != nullptr)
		{
			m_pMS->ShutDownMessageSystem();
			m_pMS	= nullptr;
		}

		if(m_pOM != nullptr)
		{
			m_pOM->RemoveAllObjects();
			CObjectManager::DeleteInstance();
			m_pOM	= nullptr;
		}

		if(m_pOF != nullptr)
		{
			m_pOF->ShutdownObjectFactory();
			m_pOF	= nullptr;
		}

		if(m_pES != nullptr)
		{
			m_pES->ClearEvents();
			m_pES->ShutdownEventSystem();
			m_pES = nullptr;
		}
	
	m_bWinner = false;
	m_bGameOver = false;
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
	/*	if(m_pPlayer!=nullptr)
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->DeleteInstance();
		}*/
		
		if(m_pGUI!=nullptr)
		{
			m_pGUI->DeleteInstance();
			m_pGUI=nullptr;
		}
	}
	


bool CTutorState::Input(void)
{
	if(m_bGameOver == false && (m_bWinner == false || m_nEnemyCount > 0))
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
						m_pDI->ClearInput();
					}
					else if(m_nPosition == 1)
					{
						m_bPaused = true;
						CGame::GetInstance()->ChangeState(COptionsState::GetInstance());
						return true;
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
			return true;
		}
		else
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
			else
			{
				if(m_pDI->JoystickButtonPressed(6))
				{
					m_bPaused = !m_bPaused;
				}
			}
			return true;
		}
	}
	return true;
}

void CTutorState::Update(float fDt)
{
	
	if(!m_bPaused && m_bGameOver == false && m_bWinner == false)
	{
		Camera::GetInstance()->Update(dynamic_cast<CPlayer*>(m_pPlayer),0,0,fDt);
		m_PM->UpdateEverything(fDt);
		m_pAudio->Update();
		m_pOM->UpdateAllObjects(fDt);
		m_pOM->CheckCollisions();

		m_pES->ProcessEvents();
		m_pMS->ProcessMessages();

		if(m_bWordBox == true)
		{
		if(m_fWordTimer >= 0.0f)
			m_fWordTimer -= fDt;
		else
			m_bWordBox = false;
		}
	}

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

	if(m_pPlayer->GetHealth() <= 0)
		m_bGameOver = true;

	if(m_bGameOver == true || m_bWinner == true)
	{
		gameEndTimer += fDt;
		if(SoundOff == false)
			TurnSoundOff();
	}
			


}

void CTutorState::IncrementBox(void)
{
	m_nBoxIndex++;
	m_bWordBox = true;
	m_fWordTimer = 8.0f;

	if(m_nBoxIndex >= 12)
	{
		
		m_nEnemyCount = 0;
		m_bWinner =true;
	}
}

void CTutorState::Render(void)
{
	
	
	m_pD3D->Clear( 0, 255, 255 );
	if(m_bGameOver == false && (m_bWinner == false || m_nEnemyCount > 0))
	{
	IDirect3DSurface9 *current=0, *output=0;
	m_pD3D->GetDirect3DDevice()->GetRenderTarget(0, &current);

	MiniMap->GetSurfaceLevel(0,&output);
	m_pD3D->GetDirect3DDevice()->SetRenderTarget(0, output);
	m_pD3D->Clear( 0, 0, 0 );
	//Main Screen
	{

		m_pTM->Draw(m_nBackGround,int(Camera::GetInstance()->GetPosX()),
			int(Camera::GetInstance()->GetPosY()),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
		// Render game entities
		m_pTile->Render();
		m_pOM->RenderAllObjects();
		
		CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			
	}
	m_pD3D->GetDirect3DDevice()->SetRenderTarget(0, current);

	// HUD
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
		m_pFont->Print(m_sObj.c_str(), 539,547,.60f,UINT_MAX);
		CPlayer::GetInstance()->Render();
		CPlayer::GetInstance()->GetTurret()->Render();
	}

	m_pD3D->GetSprite()->Flush();	

	if(m_bWordBox == true && m_nBoxIndex < 12)
	{
		if(m_nBoxIndex < 6)
		{
		m_pTM->Draw(m_nBox,485,420,1.3f,1.3f);
		}
		else
			m_pTM->Draw(m_nBox,5,5,1.3f,1.3f);
		m_pD3D->GetSprite()->Flush();

		switch(m_nBoxIndex)
			{
			case 0:
				{
					m_pFont->Print(m_asInfo[0].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 1:
				{

					m_pFont->Print(m_asInfo[1].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 2:
				{
					m_pFont->Print(m_asInfo[2].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 3:
				{
					m_pFont->Print(m_asInfo[3].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 4:
				{
					m_pFont->Print(m_asInfo[4].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 5:
				{
					m_pFont->Print(m_asInfo[5].c_str(),515,440,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 6:
				{
					m_pFont->Print(m_asInfo[6].c_str(),35,25,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 7:
				{
					m_pFont->Print(m_asInfo[7].c_str(),35,25,0.6f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 8:
				{
					m_pFont->Print(m_asInfo[8].c_str(),35,25,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 9:
				{
					m_pFont->Print(m_asInfo[9].c_str(),35,25,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 10:
				{
					m_pFont->Print(m_asInfo[10].c_str(),35,25,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;

				case 11:
				{
					m_pFont->Print(m_asInfo[11].c_str(),35,25,0.7f,D3DCOLOR_XRGB(0,0,0));
				}
				break;
				/*
				case 12:
				{
					m_pFont->Print(m_asInfo[12].c_str(),30,30,1.0f,0);
				}
				break;*/

			default:
				{
					
				}
				break;

			}
	}
	
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

	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
	}
	else if(m_bGameOver == true)
	{
		if(gameEndTimer <= 5.0f)
			m_pTM->Draw(GameOverID,0,0,0.8f,0.7f);
		else
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	}
	else if(m_bWinner == true && m_nEnemyCount <= 0)
	{
		if(gameEndTimer <= 5.0f)
			m_pTM->Draw(WinnerID,0,0,0.8f,0.7f);
		else
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());

	}
}

void CTutorState::MessageProc(CMessage* pMsg)
{
	CTutorState* pSelf = CTutorState::GetInstance();
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
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+90*Up.fY-C->GetPosY()+11.2*abs(Up.fX));
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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY+11.2*abs(Up.fX));
							Bullet->SetDamage(35.0f);
						}
						Bullet->SetVelX(norVec.fX*400);
						Bullet->SetVelY(norVec.fY*400);
					}
					Bullet->SetBulletType(BUL_SHELL);
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
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						if(Bullet->GetWhoFired())
						{
							if(player->GetWeaponAmmoMissile()> 0)
							{
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2*abs(Up.fX));
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
									SetRect(&rSelf,(int)(pSelf->m_nMouseX-C->GetPosX()-32),(int)(pSelf->m_nMouseY-C->GetPosY()-32),(int)(pSelf->m_nMouseX-C->GetPosX()+32),(int)(pSelf->m_nMouseY-C->GetPosY()+32));
									Bullet->SetTargetRect(rSelf);
									tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX()+16,pSelf->m_nMouseY-C->GetPosY()+16};
									Bullet->SetTargetPos(vPos);
									Bullet->SetMissileTimer(0.25f);
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY+11.2*abs(Up.fX));
							Bullet->SetDamage(45.0f);
						}
						Bullet->SetVelX(300);
						Bullet->SetVelY(300);
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
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2*abs(Up.fY));
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2*abs(Up.fX));
								if(player->GetDoubleDamage())
									Bullet->SetDamage(15.0f*2);
								else
									Bullet->SetDamage(15.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoArtillery();
									player->SetWeaponAmmo(player->GetWeaponAmmoShell(), --ammoChange,player->GetWeaponAmmoMissile());
									RECT rSelf;
									SetRect(&rSelf,(int)(pSelf->m_nMouseX-C->GetPosX()-32),(int)(pSelf->m_nMouseY-C->GetPosY()-32),(int)(pSelf->m_nMouseX-C->GetPosX()+32),(int)(pSelf->m_nMouseY-C->GetPosY()+32));
									Bullet->SetTargetRect(rSelf);
									tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX(),pSelf->m_nMouseY-C->GetPosY()};
									Bullet->SetTargetPos(vPos);
								}
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY+11.2*abs(Up.fX));
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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2*abs(Up.fX));
							if(player->GetDoubleDamage())
									Bullet->SetDamage(5.0f*2);
								else
									Bullet->SetDamage(5.0f);
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY+11.2*abs(Up.fX));
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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX()+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY()+11.2*abs(Up.fX));
							if(player->GetDoubleDamage())
									Bullet->SetDamage(2.0f*2);
								else
									Bullet->SetDamage(2.0f);
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX+11.2*abs(Up.fY));
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY+11.2*abs(Up.fX));
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
					Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*dir.fX-C->GetPosX()+11.2*abs(dir.fY));
					Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*dir.fY-C->GetPosY()+11.2*abs(dir.fX));
					Bullet->SetBulletType(BUL_FLAME);
					Bullet->SetFlameTimer(1.0f);
					if(player->GetDoubleDamage())
						Bullet->SetDamage(1.0f*2);
					else
						Bullet->SetDamage(1.0f);
					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
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
			pSelf->m_nEnemyCount++;

			CCreateEnemyMessage* pMessage = dynamic_cast<CCreateEnemyMessage*>(pMsg);
			switch(pMessage->GetEnemyType())
			{
			case SAPPER:
				{
					CSapper* sapper =(CSapper*)pSelf->m_pOF->CreateObject("CSapper");
					sapper->SetSoldierSounds(pSelf->m_anSoldierSounds);
					sapper->SetExplode(pSelf->m_nSappSound);
					sapper->SetImageID(pSelf->m_anEnemyIDs[1]);
					sapper->SetEType(SAPPER);
					sapper->SetPosX(pMessage->GetPosX());
					sapper->SetPosY(pMessage->GetPosY());
					sapper->SetHeight(32);
					sapper->SetWidth(32);
					CPlayer* player = CPlayer::GetInstance();
					sapper->SetPlayer(player);
					sapper->SetSight(400);
					sapper->SetVelX(45);
					sapper->SetVelY(45);
					sapper->SetHealth(35);
					sapper->SetMaxHealth(35);
					sapper->SetExplosion(pSelf->m_PM->GetEmitter(pSelf->FXSapper_Explosion));
					sapper->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(sapper);
					sapper->Release();
					sapper = nullptr;
				}
				break;
			case TANK:
				{
					pSelf->m_pEnemy = pSelf->m_pOF->CreateObject("CTank");
					pSelf->m_pEnemy->SetImageID(pSelf->m_anEnemyIDs[6]);
					pSelf->m_pEnemy->SetPosX(pMessage->GetPosX());
					pSelf->m_pEnemy->SetPosY(pMessage->GetPosY());	
					pSelf->m_pEnemy->SetWidth(64);
					pSelf->m_pEnemy->SetHeight(128);

					CPlayer* player = CPlayer::GetInstance();
					
					CTank* tank = (CTank*)pSelf->m_pOF->CreateObject("CTank");
					tank->SetImageID(pSelf->m_nPlayerID);
					tank->SetPosX(pMessage->GetPosX());
					tank->SetPosY(pMessage->GetPosY());	
					tank->SetEType(TANK);
					tank->SetWidth(64);
					tank->SetHeight(128);
					tank->SetPlayer(player);
					tank->SetRotation(0);
					tank->SetRotationRate(0.75f);
					tank->SetSight(400);
					tank->SetVelX(30);
					tank->SetVelY(30);
					tank->SetStartVelX(tank->GetVelX());
					tank->SetStartVelY(tank->GetVelY());
					tank->SetHealth(300);
					tank->SetMaxHealth(300);
					tank->SetHasATurret(true);
					pSelf->m_pOM->AddObject(tank);

					CTurret* turret = (CTurret*)pSelf->m_pOF->CreateObject("CTurret");
					turret->SetImageID(pSelf->m_anEnemyIDs[7]);					
					turret->SetPosX(pSelf->m_pEnemy->GetPosX());
					turret->SetPosY(pSelf->m_pEnemy->GetPosY());
					turret->SetWidth(64);
					turret->SetHeight(128);

					tank->SetTurret(turret);
					turret->SetOwner(tank);
					turret->SetBullet(BUL_SHELL);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
					turret->SetHealth(200);
					turret->SetMaxHealth(200);
					turret->SetFireRate(2.5f);
					turret->SetTarget(CPlayer::GetInstance());
					turret->SetRotationRate(1.0f);
					turret->SetFlamer(pSelf->m_PM->GetEmitter(pSelf->FXFlame));
					pSelf->m_pOM->AddObject(turret);
					turret->Release();
					turret = nullptr;
					tank->Release();
					tank = nullptr;
					
				}
				break;
			case TURRET:
				{
					CTurret* turret = (CTurret*)pSelf->m_pOF->CreateObject("CTurret");
					turret->SetImageID(pSelf->m_nPlayerTurretID);
					turret->SetPosX(pMessage->GetPosX());
					turret->SetPosY(pMessage->GetPosY());
					turret->SetWidth(64);
					turret->SetHeight(128);

					
					turret->SetOwner(nullptr);
					turret->SetBullet(BUL_SHELL);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
					turret->SetHealth(200);
					turret->SetMaxHealth(200);
				    turret->SetFireRate(2.5f);
					turret->SetTarget(CPlayer::GetInstance());
					turret->SetRotationRate(1.0f);
					turret->SetFlamer(pSelf->m_PM->GetEmitter(pSelf->FXFlame));
					pSelf->m_pOM->AddObject(turret);
					turret->Release();
					turret = nullptr;
				
				}
				break;

			case RIFLE:
				{
					CPlayer* player = CPlayer::GetInstance();
					CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
					enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
					enemy->SetEType(RIFLE);
					enemy->SetImageID(pSelf->m_anEnemyIDs[14]);
					enemy->SetPosX(pMessage->GetPosX());
					enemy->SetPosY(pMessage->GetPosY());
					enemy->SetHeight(64);
					enemy->SetWidth(32);
					enemy->SetPlayer(player);
					enemy->SetHealth(50);
					enemy->SetMaxHealth(50);
					enemy->SetVelX(30);
					enemy->SetVelY(30);
					enemy->SetMinDistance(200);
					enemy->SetMaxDistance(600);
					enemy->SetShotTimer(0.1f);
					enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(enemy);
				}
				break;
			case ROCKET:
				{
					CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
					enemy->SetEType(ROCKET);
					enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
					enemy->SetImageID(pSelf->m_anEnemyIDs[15]);
					enemy->SetPosX(pMessage->GetPosX());
					enemy->SetPosY(pMessage->GetPosY());
					enemy->SetHeight(64);
					enemy->SetWidth(32);
					enemy->SetPlayer(CPlayer::GetInstance());
					enemy->SetHealth(50);
					enemy->SetMaxHealth(50);
					enemy->SetVelX(30);
					enemy->SetVelY(30);
					enemy->SetMinDistance(200);
					enemy->SetMaxDistance(600);
					enemy->SetShotTimer(3.0f);
					enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
					pSelf->m_pOM->AddObject(enemy);
					enemy->Release();
					enemy = nullptr;
				}
				break;
			case HELP:
				{
					int randNum = rand()%2;
					switch(randNum)
					{
					case 0:
						{
							CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
							enemy->SetEType(RIFLE);
							enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
							enemy->SetType(OBJ_HELP);
							enemy->SetImageID(pSelf->m_anSupportIDs[1]);
							enemy->SetPosX(pMessage->GetPosX());
							enemy->SetPosY(pMessage->GetPosY());
							enemy->SetHeight(64);
							enemy->SetWidth(32);
							enemy->SetHelpTarget(pSelf->m_pOM->GetTarget(enemy));
							enemy->SetHealth(50);
							enemy->SetMaxHealth(50);
							enemy->SetVelX(30);
							enemy->SetVelY(30);
							enemy->SetMinDistance(200);
							enemy->SetMaxDistance(600);
							enemy->SetShotTimer(0.1f);
							enemy->SetDamage(2);
							enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
							pSelf->m_pOM->AddObject(enemy);
							enemy->Release();
							enemy = nullptr;
						}
						break;
					case 1:
						{
							CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
							enemy->SetSoldierSounds(pSelf->m_anSoldierSounds);
							enemy->SetEType(ROCKET);
							enemy->SetImageID(pSelf->m_anSupportIDs[2]);
							enemy->SetType(OBJ_HELP);
							enemy->SetPosX(pMessage->GetPosX());
							enemy->SetPosY(pMessage->GetPosY());	
							enemy->SetHeight(64);
							enemy->SetWidth(32);
							enemy->SetHelpTarget(pSelf->m_pOM->GetTarget(enemy));
							enemy->SetHealth(50);
							enemy->SetMaxHealth(50);
							enemy->SetVelX(30);
							enemy->SetVelY(30);
							enemy->SetMinDistance(200);
							enemy->SetMaxDistance(600);
							enemy->SetShotTimer(3.0f);
							enemy->SetDamage(35);
							enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
							pSelf->m_pOM->AddObject(enemy);
							enemy->Release();
							enemy = nullptr;
						}
						break;
					}
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
			pSelf->m_nEnemyCount--;
			CEnemy* pEnemy = dynamic_cast<CDestroyEnemyMessage*>(pMsg)->GetEnemy();
	
			pSelf->m_PM->RemoveAttachedEmitter(pEnemy->GetTail());

			int nRandNum = rand()%12;
			if(nRandNum <= 7)
			{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,pEnemy,nRandNum);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
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
			CCreatePickupMessage* pMessage = dynamic_cast<CCreatePickupMessage*>(pMsg);	
			
			if(pMessage->GetEntity()->GetType() != OBJ_HELP)
			{
				CEntity* pEntity = pSelf->m_pOF->CreateObject("CPickup");
				CPickup* pPickup = dynamic_cast<CPickup*>(pEntity);
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
						pPickup->SetGiven(150);
						pPickup->SetPickUpType(pMessage->GetPickUpType());
					}
					break;
				}

				pPickup->SetPosX(pMessage->GetEntity()->GetPosX());
				pPickup->SetPosY(pMessage->GetEntity()->GetPosY());

				pPickup->SetAliveTime(150.0f);

				pSelf->m_pOM->AddObject(pPickup);

				pPickup->Release();
				pPickup = nullptr;
			}
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
			m_pBuilding->SetMaxHealth(50);
			m_pBuilding->SetImageID(pSelf->m_anEnemyIDs[2]);

			CBuilding* pBuilding = dynamic_cast<CBuilding*>(m_pBuilding);
			pBuilding->SetFlames(pSelf->m_PM->GetEmitter(pSelf->FXBuildingFlame));
			pBuilding->SetSpawn(pMessage->GetType());
			pBuilding->SetCanSpawn(pMessage->GetSpawn());
			pBuilding->SetSpawnTime(pMessage->GetTime());
			pBuilding->SetPlayer((CPlayer*)pSelf->m_pPlayer);
			pBuilding->SetDead(false);
			pBuilding->SetDeathImage(pSelf->m_anEnemyIDs[5]);
			pBuilding->SetRange(500);
			pSelf->m_pOM->AddObject(m_pBuilding);

			m_pBuilding->Release();
		}
		break;
	case MSG_CREATEMINE:
		{
			CCreateMineMessage* pMessage = dynamic_cast<CCreateMineMessage*>(pMsg);
			CMine* pMine = (CMine*)pSelf->m_pOF->CreateObject("CMine");
			pMine->SetPosX(pMessage->GetPosX());
			pMine->SetPosY(pMessage->GetPosY());
			pMine->SetWidth(32);
			pMine->SetHeight(32);
			pMine->SetHealth(100);
			pMine->SetMaxHealth(100);
			pMine->SetImageID(pSelf->m_nMine);
			pMine->SetDamage(75);
			pSelf->m_pOM->AddObject(pMine);
			pMine->Release();
			
		}
		break;
	case MSG_DESTROYMINE:
		{
			if(pSelf->m_nMineSound != -1)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(pSelf->m_nMineSound);

			CMine* pMine = dynamic_cast<CDestroyMineMessage*>(pMsg)->GetMine();
			pSelf->m_pOM->RemoveObject(pMine);
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
					pBullet->SetDamage(1);
					pBullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pBullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
					if(pMessage->GetFiringEntity()->GetType() == OBJ_HELP)
						pBullet->SetWhoFired(true);
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
					pBullet->SetVelX(norVec.fX*300);
					pBullet->SetVelY(norVec.fY*300);
					pBullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
					pBullet->SetDamage(15.0f);
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
					pBullet->SetBulletType(BUL_SHELL);
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			}

		}
		break;

	case MSG_CREATETREE:
		{
			CCreateTreeMessage* pMessage = dynamic_cast<CCreateTreeMessage*>(pMsg);
			CTree* pTree = (CTree*)pSelf->m_pOF->CreateObject("CTree");
			pTree->SetPosX(pMessage->GetPosX());
			pTree->SetPosY(pMessage->GetPosY());
			
			pTree->SetHealth(100);
			pTree->SetMaxHealth(100);
			if(pMessage->GetBarr() == true)
			{
				pTree->SetImageID(pSelf->m_nBarricade);
				pTree->SetDestroyedImage(pSelf->m_nDeadBarr);
				pTree->SetWidth(32);
				pTree->SetHeight(32);
			}
			else
			{
				pTree->SetImageID(pSelf->m_nTree);
				pTree->SetDestroyedImage(pSelf->m_nDeadTree);
				pTree->SetWidth(64);
				pTree->SetHeight(64);
			}
			pTree->SetHit(false);
			pSelf->m_pOM->AddObject(pTree);
			pTree->Release();
		}
		break;

	case MSG_DESTROYTREE:
		{
			CTree* pTree = dynamic_cast<CDestroyTreeMessage*>(pMsg)->GetTree();
			pSelf->m_pOM->RemoveObject(pTree);
		}
		break;
	case MSG_CREATEFLYTEXT:
		{
			CCreateFlyTextMessage* pMessage = dynamic_cast<CCreateFlyTextMessage*>(pMsg);
			CFlyText* pFlyText = (CFlyText*)pSelf->m_pOF->CreateObject("CFlyText");
			pFlyText->SetFlyText(pMessage->GetPickUp()->GetPickUpType(),1.5f,D3DCOLOR_XRGB(0,0,0),pMessage->GetPickUp()->GetPosX(),pMessage->GetPickUp()->GetPosY());
			pSelf->m_pOM->AddObject(pFlyText);
			pFlyText->Release();
		}
		break;
	case MSG_DESTROYFLYTEXT:
		{
			CFlyText* pFlyText = dynamic_cast<CDestroyFlyTextMessage*>(pMsg)->GetPickup();
			pSelf->m_pOM->RemoveObject(pFlyText);
		}
		break;
	case MSG_CREATEJET:
		{
			CCreateJetMessage* pMessage = dynamic_cast<CCreateJetMessage*>(pMsg);
			CJet* pJet = (CJet*)pSelf->m_pOF->CreateObject("CJet");
			RECT rSelf;
			SetRect(&rSelf,(int)(pSelf->m_nMouseX-C->GetPosX()-8),(int)(pSelf->m_nMouseY-C->GetPosY()-8),(int)(pSelf->m_nMouseX-C->GetPosX()+8),(int)(pSelf->m_nMouseY-C->GetPosY()+8));
			pJet->SetTargetRect(rSelf);
			tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX(),pSelf->m_nMouseY-C->GetPosY()};
			pJet->SetTargetPos(vPos);
			pJet->SetHeight(128);
			pJet->SetWidth(128);
			pJet->SetVelY(-300);
			pJet->SetEmitter(pSelf->m_PM->GetEmitter(pSelf->FXAirStrike));
			pSelf->m_pOM->AddObject(pJet);
			pJet->Release();
			pJet = nullptr;
		}
		break;
	case MSG_DESTROYJET:
		{
			CJet* pJet = dynamic_cast<CDestrotJetMessage*>(pMsg)->GetJet();
			pSelf->m_pOM->RemoveObject(pJet);
		}
		break;
	default:
		{

		}
		break;
	};
}

void CTutorState::LoadWords(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("TutorState");
				if(m_bActivePad == false)
				{	
					TiXmlNode* pButton=pState->FirstChild("Keyboard");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();

				}
				else
				{
					TiXmlNode* pButton=pState->FirstChild("Pad");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();
				}
				TiXmlNode* pButton = pState->FirstChild("e");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_asInfo[4]=pText->Value();
				pButton=pState->FirstChild("f");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[5]=pText->Value();
				pButton=pState->FirstChild("g");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[6]=pText->Value();
				pButton=pState->FirstChild("h");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[7]=pText->Value();
				pButton=pState->FirstChild("i");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[8]=pText->Value();
				pButton=pState->FirstChild("j");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[9]=pText->Value();
				pButton=pState->FirstChild("k");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[10]=pText->Value();
				pButton=pState->FirstChild("l");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[11]=pText->Value();
				pButton=pState->FirstChild("Obj");
				pText = pButton->FirstChild()->ToText();
				m_sObj=pText->Value();
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
				TiXmlNode* pState = pLanguage->FirstChild("TutorState");
				if(m_bActivePad == false)
				{	
					TiXmlNode* pButton=pState->FirstChild("Keyboard");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();

				}
				else
				{
					TiXmlNode* pButton=pState->FirstChild("Pad");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();
				}
				TiXmlNode* pButton = pState->FirstChild("e");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_asInfo[4]=pText->Value();
				pButton=pState->FirstChild("f");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[5]=pText->Value();
				pButton=pState->FirstChild("g");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[6]=pText->Value();
				pButton=pState->FirstChild("h");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[7]=pText->Value();
				pButton=pState->FirstChild("i");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[8]=pText->Value();
				pButton=pState->FirstChild("j");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[9]=pText->Value();
				pButton=pState->FirstChild("k");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[10]=pText->Value();
				pButton=pState->FirstChild("l");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[11]=pText->Value();
				pButton=pState->FirstChild("Obj");
				pText = pButton->FirstChild()->ToText();
				m_sObj=pText->Value();
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
				TiXmlNode* pState = pLanguage->FirstChild("TutorState");
				if(m_bActivePad == false)
				{	
					TiXmlNode* pButton=pState->FirstChild("Keyboard");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();

				}
				else
				{
					TiXmlNode* pButton=pState->FirstChild("Pad");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();
				}
				TiXmlNode* pButton = pState->FirstChild("e");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_asInfo[4]=pText->Value();
				pButton=pState->FirstChild("f");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[5]=pText->Value();
				pButton=pState->FirstChild("g");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[6]=pText->Value();
				pButton=pState->FirstChild("h");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[7]=pText->Value();
				pButton=pState->FirstChild("i");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[8]=pText->Value();
				pButton=pState->FirstChild("j");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[9]=pText->Value();
				pButton=pState->FirstChild("k");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[10]=pText->Value();
				pButton=pState->FirstChild("l");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[11]=pText->Value();
				pButton=pState->FirstChild("Obj");
				pText = pButton->FirstChild()->ToText();
				m_sObj=pText->Value();
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
				TiXmlNode* pState = pLanguage->FirstChild("TutorState");
				if(m_bActivePad == false)
				{	
					TiXmlNode* pButton=pState->FirstChild("Keyboard");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();

				}
				else
				{
					TiXmlNode* pButton=pState->FirstChild("Pad");
					TiXmlNode* pLine=pButton->FirstChild("a");
					TiXmlText* pText=pLine->FirstChild()->ToText();
					m_asInfo[0]=pText->Value();
					pLine=pButton->FirstChild("b");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[1]=pText->Value();
					pLine=pButton->FirstChild("c");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[2]=pText->Value();
					pLine=pButton->FirstChild("d");
					pText=pLine->FirstChild()->ToText();
					m_asInfo[3]=pText->Value();
				}
				TiXmlNode* pButton = pState->FirstChild("e");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_asInfo[4]=pText->Value();
				pButton=pState->FirstChild("f");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[5]=pText->Value();
				pButton=pState->FirstChild("g");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[6]=pText->Value();
				pButton=pState->FirstChild("h");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[7]=pText->Value();
				pButton=pState->FirstChild("i");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[8]=pText->Value();
				pButton=pState->FirstChild("j");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[9]=pText->Value();
				pButton=pState->FirstChild("k");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[10]=pText->Value();
				pButton=pState->FirstChild("l");
				pText = pButton->FirstChild()->ToText();
				m_asInfo[11]=pText->Value();
				pButton=pState->FirstChild("Obj");
				pText = pButton->FirstChild()->ToText();
				m_sObj=pText->Value();
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

void CTutorState::TurnSoundOff(void)
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
	
	
		if(m_nDeadBullet != -1)
		{
			if(m_pAudio->SFXIsSoundPlaying(m_nDeadBullet) == true)
				m_pAudio->SFXStopSound(m_nDeadBullet);

			m_pAudio->SFXUnloadSound(m_nDeadBullet);
			m_nDeadBullet = -1;
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

		if(m_nMineSound != -1)
		{
			if(m_pAudio->SFXIsSoundPlaying(m_nMineSound) == true)
				m_pAudio->SFXStopSound(m_nMineSound);

			m_pAudio->SFXUnloadSound(m_nMineSound);
			m_nMineSound = -1;
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

		for(int i = 0; i < 3; ++i)
		{
			if(m_anSupportIDs[i] != -1)
			{
				m_pTM->UnloadTexture(m_anSupportIDs[i]);
				m_anSupportIDs[i] = -1;
			}
		}

}
	