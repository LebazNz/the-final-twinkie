#include "GamePlayState.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "ShopState.h"
#include "StatState.h"
#include "../Headers/FlyText.h"
#include "../Headers/GUI.h"
#include "../Headers/Game.h"
#include "../Headers/BitmapFont.h"
#include "../Headers/Camera.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../World and Tile/Tile.h"
#include "../World and Tile/TileManager.h"
#include "../Particle/ParticleManager.h"
#include "../Particle/Emitter.h"
#include "../Animation/AnimationManager.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"
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
#include "../Event and Messages/CreateJetMessage.h"
#include "../Event and Messages/DestrotJetMessage.h"
#include "../Event and Messages/CreatePickupMessage.h"
#include "../Event and Messages/DestroyPickupMessage.h"
#include "../Event and Messages/BossFireMessage.h"
#include "../Event and Messages/DestroyNaziBoss.h"
#include "../Event and Messages/CreateBoss.h"
#include "../Event and Messages/CreateFactoryMessage.h"
#include "../Event and Messages/DestroyFactoryMessage.h"
#include "../GameObjects/Bullet.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Turret.h"
#include "../GameObjects/Mine.h"
#include "../GameObjects/Tree.h"
#include "../GameObjects/Sapper.h"
#include "../GameObjects/Tank.h"
#include "../GameObjects/Jet.h"
#include "../Particle/Emitter.h"
#include "../GameObjects/Building.h"
#include "../GameObjects/Factory.h"
#include "../Boss/NaziBoss.h"
#include "../PickUps and Specials/Pickup.h"
#include "../PickUps and Specials/Special.h"
#include "../PickUps and Specials/Nuke.h"
#include "../PickUps and Specials/Smoke.h"
#include "../PickUps and Specials/EMP.h"
#include "../PickUps and Specials/Reinforcements.h"
#include "../PickUps and Specials/AirStrike.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
CGamePlayState* CGamePlayState::m_pSelf = nullptr;

CGamePlayState* CGamePlayState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGamePlayState;
	return m_pSelf;
}

void CGamePlayState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CGamePlayState::CGamePlayState(void)
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
	m_nMine = -1;
	m_nTree = -1;
	m_nDeadTree = -1;
	m_nBarricade = -1;
	m_nDeadBarr = -1;
	m_nEnemyCount = 0;
	gameEndTimer = 0.0f;
	m_bWinner = false;
	m_bGameOver = false;
}

CGamePlayState::~CGamePlayState(void)
{
}

void CGamePlayState::Enter(void)
{
	LoadText();
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

		m_pTM->Draw(m_nBackGround,0,0,0.8f,0.8f);
	
		m_pD3D->GetSprite()->Flush();	
		m_pD3D->SpriteEnd();
		m_pD3D->DeviceEnd();	

		m_pD3D->Present();

		m_pTile->Load("resource/files/NateLevel.xml");
		//m_pTile->Load("resource/files/graphic_layer.xml");

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
		m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/AC_testturret.png"));
		m_anEnemyIDs[2]=m_pTM->LoadTexture(_T("resource/graphics/Building.png"));
		m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
		m_anEnemyIDs[3]=m_pTM->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
		m_anEnemyIDs[4]=m_pTM->LoadTexture(_T("resource/graphics/Rocketeer.png"));
		m_anEnemyIDs[5]=m_pTM->LoadTexture(_T("resource/graphics/rubble.png"));
		m_anEnemyIDs[6]=m_pTM->LoadTexture(_T("resource/graphics/enemyTank.png"));
		m_anEnemyIDs[7]=m_pTM->LoadTexture(_T("resource/graphics/enemyTurret.png"));
		m_anEnemyIDs[8]=m_pTM->LoadTexture(_T("resource/graphics/SpecialSelect.png"));
		m_anEnemyIDs[9]=m_pTM->LoadTexture(_T("resource/graphics/sprites_naziBoss.png"));
		m_anEnemyIDs[10]=m_pTM->LoadTexture(_T("resource/graphics/factory_twinkie.png"));

		m_nPickupHealthID = m_pTM->LoadTexture(_T("resource/graphics/HealthPickUp.png"));
		m_nPickupAmmoID = m_pTM->LoadTexture(_T("resource/graphics/AmmoPickUp.png"));
		m_nPickupArmorID = m_pTM->LoadTexture(_T("resource/graphics/ArmorPickUp.png"));
		m_nPickupDoubleDID = m_pTM->LoadTexture(_T("resource/graphics/DoubleDamagePickUp.png"));
		m_nPickupNoReloadID = m_pTM->LoadTexture(_T("resource/graphics/NoReloadPickUp.png"));
		m_nPickupInvuID = m_pTM->LoadTexture(_T("resource/graphics/InvulnerabilityPickUp.png"));
		m_nPickupInfAmmoID = m_pTM->LoadTexture(_T("resource/graphics/InfAmmoPickUp.png"));
		m_nPickupMoneyID = m_pTM->LoadTexture(_T("resource/graphics/NukePickUp.png"));

		m_nTree = m_pTM->LoadTexture(_T("resource/graphics/tree.png"));
		m_nMine = m_pTM->LoadTexture(_T("resource/graphics/Mine.png"));
		m_nDeadTree = m_pTM->LoadTexture(_T("resource/graphics/stump.png"));
		m_nBarricade =m_pTM->LoadTexture(_T("resource/graphics/barr2.png"));
		m_nDeadBarr = m_pTM->LoadTexture(_T("resource/graphics/barr1.png"));
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
		m_pOF->RegisterClassType<CNaziBoss>("NaziBoss");
		m_pOF->RegisterClassType<CEMP>("CEMP");
		m_pOF->RegisterClassType<Factory>("CFactory");
		m_pOF->RegisterClassType<CJet>("CJet");

		m_pPlayer=CPlayer::GetInstance();
		CPlayer* player=dynamic_cast<CPlayer*>(m_pPlayer);
		player->SetImageID(m_nPlayerID);
		player->SetPosX(float(CGame::GetInstance()->GetWidth()/2));
		player->SetPosY(float(CGame::GetInstance()->GetHeight()/2));
		player->SetRotation(0);
		player->SetWidth(64);
		player->SetHeight(128);
		player->SetVelX(90);
		player->SetVelY(90);
		player->SetHealth(250);
		player->SetMaxHealth(250);
		player->SetArmor(50);
		player->SetMaxArmor(50);
		player->SetWeaponAmmo(40/*m_dGameData.nShellAmmo*/,40/*m_dGameData.nArtilleryAmmo*/,/*m_dGameData.nMissileAmmo*/40);
		player->SetMaxWeaponAmmo(40,40,40);
		player->SetMoney(m_dGameData.nMoney);
		tVector2D v2Pos = { player->GetPosX(), player->GetPosY() };
		CNuke* pNuke = new CNuke();
		pNuke->SetEmitter(m_PM->GetEmitter(FXNuke));
		CSmoke* pSmoke=new CSmoke();
		pSmoke->SetEmitter(m_PM->GetEmitter(FXSmoke));
		CReinforcements* pRF = new CReinforcements;
		CAirStrike* pAS = new CAirStrike;
		player->SetSpecial1(pSmoke);
		player->SetSpecial2(pAS);
		player->SetSpecial1Ammo(2);
		player->SetSpecial2Ammo(2);
		player->SetOldPos(v2Pos);
		player->SetSecondType(MACHINEGUN);
		//player->SetName(m_dGameData.szName);
		player->SetEmitterLeft(m_PM->GetEmitter(FXTreads));
		player->SetEmitterRight(m_PM->GetEmitter(FXTreads));


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
		m_pMS->ProcessMessages();
		m_pOM->AddObject(player);
		m_pOM->AddObject(PlayerTurret);
		PlayerTurret->Release();

		/*CSapper* sapper=(CSapper*)m_pOF->CreateObject("CSapper");
		sapper->SetImageID(m_anEnemyIDs[1]);
		sapper->SetPosX(500);
		sapper->SetPosY(500);
		sapper->SetHeight(32);
		sapper->SetWidth(32);
		sapper->SetPlayer(player);
		sapper->SetSight(400);
		sapper->SetVelX(45);
		sapper->SetVelY(45);
		sapper->SetHealth(35);
		sapper->SetMaxHealth(35);
		sapper->SetExplosion(m_PM->GetEmitter(FXSapper_Explosion));
		sapper->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(sapper);
		sapper->Release();*/

		//CTank* pTank=(CTank*)m_pOF->CreateObject("CTank");
		//pTank->SetImageID(m_anEnemyIDs[6]);
		//pTank->SetPosX(500);
		//pTank->SetPosY(200);
		//pTank->SetRotation(0);
		//pTank->SetWidth(64);
		//pTank->SetHeight(128);
		//pTank->SetPlayer(player);
		//pTank->SetRotationRate(0.75f);
		//pTank->SetSight(400);
		//pTank->SetVelX(30);
		//pTank->SetVelY(30);
		//pTank->SetHealth(300);
		//pTank->SetMaxHealth(300);
		//pTank->SetHasATurret(true);
		//m_pOM->AddObject(pTank);

		//CTurret* pTurret=(CTurret*)m_pOF->CreateObject("CTurret");
		//pTurret->SetImageID(m_anEnemyIDs[7]);
		//pTank->SetTurret(pTurret);
		//pTurret->SetPosX(pTank->GetPosX());
		//pTurret->SetPosY(pTank->GetPosY());
		//pTurret->SetOwner(pTank);
		//pTurret->SetBullet(BUL_SHELL);
		//pTurret->SetWidth(64);
		//pTurret->SetHeight(128);
		//pTurret->SetRotationPositon(32,98);
		//pTurret->SetUpVec(0,-1);
		//pTurret->SetDistance(300);
		////pTurret->SetFireRate(2.5f);
		//pTurret->SetTarget(player);
		//pTurret->SetRotationRate(1.0f);
		//m_pOM->AddObject(pTurret);
		//pTurret->Release();
		//pTank->Release();

		//pTank=(CTank*)m_pOF->CreateObject("CTank");
		//pTank->SetImageID(m_anEnemyIDs[6]);
		//pTank->SetPosX(200);
		//pTank->SetPosY(400);
		//pTank->SetRotation(0);
		//pTank->SetWidth(64);
		//pTank->SetHeight(128);
		//pTank->SetPlayer(player);
		//pTank->SetRotationRate(0.75f);
		//pTank->SetSight(400);
		//pTank->SetVelX(30);
		//pTank->SetVelY(30);
		//pTank->SetHealth(300);
		//pTank->SetHasATurret(true);
		//m_pOM->AddObject(pTank);
		//CTurret* pTurret=(CTurret*)m_pOF->CreateObject("CTurret");
		//pTurret->SetImageID(m_anEnemyIDs[7]);
		////pTank->SetTurret(pTurret);
		//pTurret->SetPosX(200);
		//pTurret->SetPosY(200);
		//pTurret->SetOwner(nullptr);
		//pTurret->SetBullet(BUL_SHELL);
		//pTurret->SetWidth(64);
		//pTurret->SetHeight(128);
		//pTurret->SetRotationPositon(32,98);
		//pTurret->SetUpVec(0,-1);
		//pTurret->SetDistance(300);
		//pTurret->SetHealth(200);
		//pTurret->SetMaxHealth(200);
		////pTurret->SetFireRate(2.5f);
		//pTurret->SetTarget(player);
		//pTurret->SetRotationRate(1.0f);
		//m_pOM->AddObject(pTurret);
		//pTurret->Release();
		////pTank->Release();

		/*CBuilding* building=(CBuilding*)m_pOF->CreateObject("CBuilding");
		building->SetPosX(450);
		building->SetPosY(400);
		building->SetHeight(128);
		building->SetWidth(128);
		building->SetHealth(50);
		building->SetMaxHealth(50);
		building->SetImageID(m_anEnemyIDs[2]);
		building->SetFlames(m_PM->GetEmitter(FXBuildingFlame));
		building->SetCanSpawn(true);
		building->SetSpawn(SAPPER);
		building->SetSpawnTime(5.0f);
		building->SetPlayer(player);
		building->SetRange(500);
		building->SetDead(false);
		building->SetDeathImage(m_anEnemyIDs[5]);
		m_pOM->AddObject(building);
		building->Release();*/

		/*CEnemy* enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(300);
		enemy->SetPosY(300);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;

		enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(325);
		enemy->SetPosY(325);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;

		enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(250);
		enemy->SetPosY(300);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;

		enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(300);
		enemy->SetPosY(275);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;

		enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(300);
		enemy->SetPosY(325);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;

		enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(250);
		enemy->SetPosY(250);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;*/

		/*CEnemy* enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(ROCKET);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(350);
		enemy->SetPosY(325);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetMaxHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(3.0f);
		enemy->SetFire(m_PM->GetEmitter(FXEnemyOnFire));
		m_pOM->AddObject(enemy);
		enemy->Release();
		enemy = nullptr;*/

		/*CTurret* turret=(CTurret*)m_pOF->CreateObject("CTurret");
		turret->SetImageID(m_anEnemyIDs[7]);
		turret->SetPosX(350);
		turret->SetPosY(325);
		turret->SetHeight(128);
		turret->SetWidth(64);
		turret->SetBullet(BUL_SHELL);
		turret->SetDistance(400);
		turret->SetHealth(50);
		turret->SetMaxHealth(50);
		turret->SetRotationRate(2.0f);
		turret->SetTarget(player);
		turret->SetUpVec(0,-1);
		turret->SetRotationPositon(32,98);
		m_pOM->AddObject(turret);
		turret->Release();*/

		//m_nPosition = 0;
		//m_bPaused = false;

		m_pGUI->SetHudID(m_anEnemyIDs[3]);
		m_pGUI->SetPlayer(player);
		m_pGUI->SetSelect(m_anEnemyIDs[8]);

		m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);

		

		player->SetMoney(m_dGameData.nMoney);
	}
	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	D3DXCreateTexture(m_pD3D->GetDirect3DDevice(), 125, 120, 0, D3DUSAGE_RENDERTARGET|D3DUSAGE_AUTOGENMIPMAP, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &MiniMap); 
	m_bWinner = false;
	m_bGameOver = false;
	gameEndTimer = 0.0f;

}

void CGamePlayState::Exit(void)
{
	m_nEnemyCount = 0;
	SaveGame(m_dGameData.szFileName);

	if(m_bPaused == false)
	{
		m_PM->RemoveAllBaseEmitters();
		m_PM->DeleteInstance();

		if(WinnerID != -1)
		{
			m_pTM->UnloadTexture(WinnerID);
			WinnerID = -1;
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
		CGame::GetInstance()->my_channel->stop();
		if(m_pGUI!=nullptr)
		{
			m_pGUI->DeleteInstance();
			m_pGUI=nullptr;
		}
	}
	
}

bool CGamePlayState::Input(void)
{
	if(m_bGameOver == false && (m_bWinner == false || m_nEnemyCount > 0))
	{
		if(m_bPaused)
		{
			if(m_pDI->KeyPressed(DIK_ESCAPE))
			{
				m_bPaused = !m_bPaused;
			}
			if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
			{
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
		if(m_pDI->KeyPressed(DIK_7))
		{
				CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,TANK,200,200);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_8))
		{
				CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,TURRET,100,100);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		// Enter ShopState
		if(m_pDI->KeyPressed(DIK_NUMPAD0))
		{
			CGame::GetInstance()->ChangeState(StatState::GetInstance());
			return true;
		}
		// Enter ShopState
		if(m_pDI->KeyPressed(DIK_NUMPAD1))
		{
			CGame::GetInstance()->ChangeState(StatState::GetInstance());
			return true;
		}
		return true;
	}
	return true;
}

void CGamePlayState::Update(float fDt)
{
	
	if(!m_bPaused)
	{
		Camera::GetInstance()->Update(dynamic_cast<CPlayer*>(m_pPlayer),0,0,fDt);
		m_PM->UpdateEverything(fDt);
		m_pOM->UpdateAllObjects(fDt);
		m_pOM->CheckCollisions();

		m_pES->ProcessEvents();
		m_pMS->ProcessMessages();
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

	if(m_nMouseX >= 315 && m_nMouseX <= 435
		&& m_nMouseY >= 295 && m_nMouseY <= 340)
	{
		m_nPosition = 0;
	}
	if(m_nMouseX >= 315 && m_nMouseX <= 435
		&& m_nMouseY >= 340 && m_nMouseY <= 390)
	{
		m_nPosition = 1;
	}
	if(m_nMouseX >= 315 && m_nMouseX <= 435
		&& m_nMouseY >= 390 && m_nMouseY <= 435)
	{
		m_nPosition = 2;
	}

	if(m_pPlayer->GetHealth() <= 0)
		m_bGameOver = true;

	if(m_bGameOver == true || (m_bWinner == true && m_nEnemyCount <= 0))
			gameEndTimer += fDt;
}

void CGamePlayState::Render(void)
{
	
	
	m_pD3D->Clear( 0, 255, 255 );
	if(m_bGameOver == false && (m_bWinner == false || m_nEnemyCount > 0))
	{
	IDirect3DSurface9 *current=0, *output=0;
	m_pD3D->GetDirect3DDevice()->GetRenderTarget(0, &current);

	MiniMap->GetSurfaceLevel(0,&output);
	m_pD3D->GetDirect3DDevice()->SetRenderTarget(0, output);
	m_pD3D->Clear( 0, 0, 0 );

	{

		m_pTM->Draw(m_nBackGround,int(Camera::GetInstance()->GetPosX()),
			int(Camera::GetInstance()->GetPosY()),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
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
		m_AM->Render();
		// Flush the sprites
		m_PM->RenderEverything();
		m_pD3D->GetSprite()->Draw(MiniMap, NULL, &D3DXVECTOR3(0,0,0),&D3DXVECTOR3(661,409,0), D3DCOLOR_ARGB(255,255,255,255));
		m_pGUI->Render();
		CPlayer::GetInstance()->Render();
		CPlayer::GetInstance()->GetTurret()->Render();
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

void CGamePlayState::MessageProc(CMessage* pMsg)
{
	CGamePlayState* pSelf = CGamePlayState::GetInstance();
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
					CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);
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
								
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX());
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY());
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
					Bullet->SetBulletType(BUL_SHELL);
					Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pSelf->m_pOM->AddObject(Bullet);
					Bullet->Release();
					Bullet = nullptr;
				}
				break;
			case BUL_ROCKET:
				{					
					CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);
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
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX());
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY());
								if(player->GetDoubleDamage())
									Bullet->SetDamage(45.0f*2);
								else
									Bullet->SetDamage(45.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoMissile();
									player->SetWeaponAmmo(player->GetWeaponAmmoShell(), player->GetWeaponAmmoArtillery(), --ammoChange);
									RECT rSelf;
									SetRect(&rSelf,(pSelf->m_nMouseX-C->GetPosX()-32),(pSelf->m_nMouseY-C->GetPosY()-32),(pSelf->m_nMouseX-C->GetPosX()+32),(pSelf->m_nMouseY-C->GetPosY()+32));
									Bullet->SetTargetRect(rSelf);
									tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX(),pSelf->m_nMouseY-C->GetPosY()};
									Bullet->SetTargetPos(vPos);
									Bullet->SetMissileTimer(0.25f);
								}
							}
						}
						else
						{
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY);
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
					CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);
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
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX());
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY());
								if(player->GetDoubleDamage())
									Bullet->SetDamage(15.0f*2);
								else
									Bullet->SetDamage(15.0f);
								if(player->GetInfAmmo() == false)
								{
									int ammoChange=player->GetWeaponAmmoArtillery();
									player->SetWeaponAmmo(player->GetWeaponAmmoShell(), --ammoChange,player->GetWeaponAmmoMissile());
									RECT rSelf;
									SetRect(&rSelf,(pSelf->m_nMouseX-C->GetPosX()-32),(pSelf->m_nMouseY-C->GetPosY()-32),(pSelf->m_nMouseX-C->GetPosX()+32),(pSelf->m_nMouseY-C->GetPosY()+32));
									Bullet->SetTargetRect(rSelf);
									tVector2D vPos = { pSelf->m_nMouseX-C->GetPosX(),pSelf->m_nMouseY-C->GetPosY()};
									Bullet->SetTargetPos(vPos);
								}
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
					CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);

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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX());
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY());
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
				CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);

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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*Up.fX-C->GetPosX());
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*Up.fY-C->GetPosY());
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
					Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+98*dir.fX-C->GetPosX());
					Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+98*dir.fY-C->GetPosY());
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
			CGame::GetInstance()->channel->stop();
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
					sapper->SetImageID(pSelf->m_anEnemyIDs[1]);
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

					CPlayer* player = CPlayer::GetInstance();
					
					CTank* tank = (CTank*)pSelf->m_pOF->CreateObject("CTank");
					tank->SetImageID(pSelf->m_nPlayerID);
					tank->SetPosX(pMessage->GetPosX());
					tank->SetPosY(pMessage->GetPosY());	
					tank->SetWidth(64);
					tank->SetHeight(128);
					tank->SetPlayer(player);
					tank->SetRotation(0);
					tank->SetRotationRate(0.75f);
					tank->SetSight(400);
					tank->SetVelX(30);
					tank->SetVelY(30);
					tank->SetHealth(300);
					tank->SetMaxHealth(300);
					tank->SetHasATurret(true);
					pSelf->m_pOM->AddObject(tank);

					CTurret* turret = (CTurret*)pSelf->m_pOF->CreateObject("CTurret");
					turret->SetImageID(pSelf->m_nPlayerTurretID);
					turret->SetPosX(tank->GetPosX());
					turret->SetPosY(tank->GetPosY());
					turret->SetWidth(64);
					turret->SetHeight(128);
					tank->SetTurret(turret);
					turret->SetOwner(tank);
					turret->SetBullet(BUL_LASER);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
					turret->SetHealth(200);
					turret->SetMaxHealth(200);
				  //turret->SetFireRate(2.5f);
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
					turret->SetBullet(BUL_LASER);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
					turret->SetHealth(200);
					turret->SetMaxHealth(200);
				  //turret->SetFireRate(2.5f);
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
					enemy->SetEType(RIFLE);
					enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
					enemy->SetPosX(pMessage->GetPosX());
					enemy->SetPosY(pMessage->GetPosY());
					enemy->SetHeight(32);
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
					enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
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
							CSapper* sapper =(CSapper*)pSelf->m_pOF->CreateObject("CSapper");
							sapper->SetImageID(pSelf->m_anEnemyIDs[1]);
							sapper->SetType(OBJ_HELP);
							sapper->SetPosX(pMessage->GetPosX());
							sapper->SetPosY(pMessage->GetPosY());
							sapper->SetHeight(32);
							sapper->SetWidth(32);
							sapper->SetHelpTarget(pSelf->m_pOM->GetTarget(sapper));
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
					case 1:
						{
							CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
							enemy->SetEType(RIFLE);
							enemy->SetType(OBJ_HELP);
							enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
							enemy->SetPosX(pMessage->GetPosX());
							enemy->SetPosY(pMessage->GetPosY());
							enemy->SetHeight(32);
							enemy->SetWidth(32);
							enemy->SetHelpTarget(pSelf->m_pOM->GetTarget(enemy));
							enemy->SetHealth(50);
							enemy->SetMaxHealth(50);
							enemy->SetVelX(30);
							enemy->SetVelY(30);
							enemy->SetMinDistance(200);
							enemy->SetMaxDistance(600);
							enemy->SetShotTimer(0.1f);
							enemy->SetFire(pSelf->m_PM->GetEmitter(pSelf->FXEnemyOnFire));
							pSelf->m_pOM->AddObject(enemy);
							enemy->Release();
							enemy = nullptr;
						}
						break;
					case 2:
						{
							CEnemy* enemy=(CEnemy*)pSelf->m_pOF->CreateObject("CEnemy");
							enemy->SetEType(ROCKET);
							enemy->SetImageID(pSelf->m_anEnemyIDs[4]);
							enemy->SetType(OBJ_HELP);
							enemy->SetPosX(pMessage->GetPosX());
							enemy->SetPosY(pMessage->GetPosY());	
							enemy->SetHeight(32);
							enemy->SetWidth(32);
							enemy->SetHelpTarget(pSelf->m_pOM->GetTarget(enemy));
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
			CEventSystem::GetInstance()->SendEvent("explode",pEnemy);
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
						pPickup->SetGiven(50);
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
			pMine->SetWidth(64);
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
					tVector2D norVec = Vector2DNormalize(Up);
					pBullet->SetWidth(32);
					pBullet->SetHeight(32);
					pBullet->SetScale(0.35f);
					pBullet->SetWhoFired(false);
					pBullet->SetVelX(300);
					pBullet->SetVelY(300);
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
					pBullet->SetBulletType(BUL_ROCKET);
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
			pTree->SetWidth(64);
			pTree->SetHeight(64);
			pTree->SetHealth(100);
			pTree->SetMaxHealth(100);
			if(pMessage->GetBarr() == true)
			{
				pTree->SetImageID(pSelf->m_nBarricade);
				pTree->SetDestroyedImage(pSelf->m_nDeadBarr);
			}
			else
			{
				pTree->SetImageID(pSelf->m_nTree);
				pTree->SetDestroyedImage(pSelf->m_nDeadTree);
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
			SetRect(&rSelf,(pSelf->m_nMouseX-C->GetPosX()-8),(pSelf->m_nMouseY-C->GetPosY()-8),(pSelf->m_nMouseX-C->GetPosX()+8),(pSelf->m_nMouseY-C->GetPosY()+8));
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
	case MSG_BOSSFIRE:
		{
			CBossFireMessage* Msg=dynamic_cast<CBossFireMessage*>(pMsg);
			switch(Msg->GetBulletType())
			{
			case BUL_SHELL:
				{
					CBullet* pBullet = (CBullet*)pSelf->m_pOF->CreateObject("CBullet");
					pBullet->SetWidth(32);
					pBullet->SetHeight(32);
					pBullet->SetScale(0.35f);
					pBullet->SetWhoFired(false);
					tVector2D Boss={0,-1};
					Boss=Vector2DRotate(Boss, Msg->GetFiringEntity()->GetBossRotation());
					tVector2D Total={0,-1};
					Total=Vector2DRotate(Total, Msg->GetFiringEntity()->GetTotalRotation());
					pBullet->SetRotation(Msg->GetFiringEntity()->GetTotalRotation());
					pBullet->SetPosX(Msg->GetFiringEntity()->GetPosX()+(103*Total.fX));
					pBullet->SetPosY(Msg->GetFiringEntity()->GetPosY()+Msg->GetFiringEntity()->GetWidth()/2+((103)*Total.fY));
					pBullet->SetDamage(75.0f);
					pBullet->SetVelX(300*Total.fX);
					pBullet->SetVelY(300*Total.fY);
					pBullet->SetBulletType(BUL_SHELL);
					pBullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			case BUL_MACHINEGUN:
				{
					CBullet* pBullet = (CBullet*)pSelf->m_pOF->CreateObject("CBullet");
					pBullet->SetWidth(32);
					pBullet->SetHeight(32);
					pBullet->SetScale(0.35f);
					pBullet->SetWhoFired(false);
					tVector2D Boss={0,-1};
					Boss=Vector2DRotate(Boss, Msg->GetFiringEntity()->GetBossRotation());
					tVector2D Total={0,-1};
					Total=Vector2DRotate(Total, Msg->GetFiringEntity()->GetTotalRotation());
					pBullet->SetRotation(Msg->GetFiringEntity()->GetTotalRotation());
					pBullet->SetPosX(Msg->GetFiringEntity()->GetPosX()+(75*Total.fX));
					pBullet->SetPosY(Msg->GetFiringEntity()->GetPosY()+((75)*Total.fY));
					pBullet->SetDamage(1.0f);
					pBullet->SetVelX(300*Total.fX);
					pBullet->SetVelY(300*Total.fY);
					pBullet->SetBulletType(BUL_SHELL);
					pBullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			}
		}
		break;
	case MSG_DESTROYNAZIBOSS:
		{
			CDestroyNaziBoss* Msg=dynamic_cast<CDestroyNaziBoss*>(pMsg);
			pSelf->m_pOM->RemoveObject(Msg->GetBoss());
		}
		break;
	case MSG_CREATEBOSS:
		{
			CCreateBoss* Msg=dynamic_cast<CCreateBoss*>(pMsg);
			switch(Msg->GetBossType())
			{
			case NAZI:
				{
					CNaziBoss* boss=(CNaziBoss*)pSelf->m_pOF->CreateObject("NaziBoss");
					boss->SetImageID(pSelf->m_anEnemyIDs[9]);
					boss->SetWidth(148);
					boss->SetHeight(260);
					boss->SetPosX(0);
					boss->SetPosY(300);
					boss->SetPlayer(CPlayer::GetInstance());
					boss->CreateTurrets();
					boss->SetHealth(1000);
					boss->SetMaxHealth(1000);
					pSelf->m_pOM->AddObject(boss);
					boss->Release();
				}
				break;
			}
		}
		break;
	case MSG_CREATEFACTORY:
		{
			CCreateFactoryMessage* Msg=dynamic_cast<CCreateFactoryMessage*>(pMsg);
			Factory* factory=(Factory*)pSelf->m_pOF->CreateObject("CFactory");
			factory->SetImageID(pSelf->m_anEnemyIDs[10]);
			factory->SetPosX(300);
			factory->SetPosY(300);
			factory->SetHeight(128);
			factory->SetWidth(128);
			factory->SetHealth(200);
			factory->SetMaxHealth(200);
			pSelf->m_pOM->AddObject(factory);
			factory->Release();

			CTurret* tur1=(CTurret*)pSelf->m_pOF->CreateObject("CTurret");
			tur1->SetPosX(factory->GetPosX()-200);
			tur1->SetPosY(factory->GetPosY());
			tur1->SetHealth(50);
			tur1->SetMaxHealth(50);
			tur1->SetImageID(pSelf->m_nPlayerTurretID);
			tur1->SetBullet(BUL_SHELL);
			tur1->SetWidth(64);
			tur1->SetHeight(128);
			tur1->SetRotationPositon(32,98);
			tur1->SetUpVec(0,-1);
			tur1->SetDistance(800);
			tur1->SetRotationRate(1.0f);
			tur1->SetTarget(CPlayer::GetInstance());
			pSelf->m_pOM->AddObject(tur1);

			CTurret* tur2=(CTurret*)pSelf->m_pOF->CreateObject("CTurret");
			tur2->SetPosX(factory->GetPosX()+200);
			tur2->SetPosY(factory->GetPosY());
			tur2->SetHealth(50);
			tur2->SetMaxHealth(50);
			tur2->SetImageID(pSelf->m_nPlayerTurretID);
			tur2->SetBullet(BUL_SHELL);
			tur2->SetWidth(64);
			tur2->SetHeight(128);
			tur2->SetRotationPositon(32,98);
			tur2->SetUpVec(0,-1);
			tur2->SetDistance(800);
			tur2->SetRotationRate(1.0f);
			tur2->SetTarget(CPlayer::GetInstance());
			pSelf->m_pOM->AddObject(tur2);

			factory->SetTurrets(tur1, tur2);
		}
		break;
	case MSG_DESTROYFACTORY:
		{
			CDestroyFactoryMessage* Msg=dynamic_cast<CDestroyFactoryMessage*>(pMsg);
			pSelf->m_pOM->RemoveObject(Msg->GetFactory());
		}
	default:
		{

		}
		break;
	};
}

void CGamePlayState::SetSavedGame(Data gameData)
{
	m_dGameData = gameData;
}

void CGamePlayState::SaveGame(const char* szFileName)
{
	CPlayer* pPlayer = CPlayer::GetInstance();

	TiXmlDocument doc;

	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "");

	TiXmlElement* pRoot = new TiXmlElement("Save_game_data");

	doc.LinkEndChild(pRoot);

	TiXmlElement* data = new TiXmlElement("game_data");

	data->SetAttribute("level",			m_nLevel);
	data->SetAttribute("money",			pPlayer->GetMoney());
	data->SetAttribute("hp",			pPlayer->GetMaxHealth());
	data->SetAttribute("armor",			pPlayer->GetMaxArmor());
	data->SetAttribute("ammo",			m_dGameData.nAmmo);
	data->SetAttribute("speed",			m_dGameData.nSpeed);
	data->SetAttribute("shellammo",		pPlayer->GetMaxWeaponAmmoShell());
	data->SetAttribute("missileammo",	pPlayer->GetMaxWeaponAmmoMissile());
	data->SetAttribute("artilleryammo", pPlayer->GetMaxWeaponAmmoArtillery());
	data->SetAttribute("shell",			1);
	data->SetAttribute("missile",		pPlayer->GetRocketAccess());
	data->SetAttribute("artillery",		pPlayer->GetArtilleryAccess());
	data->SetAttribute("airstrike",		pPlayer->GetAirStrikeAccess());
	data->SetAttribute("emp",			pPlayer->GetEMPAccess());
	data->SetAttribute("nuke",			pPlayer->GetNukeAccess());
	data->SetAttribute("reinforce",		1);
	data->SetAttribute("smoke",			pPlayer->GetSmokeBombAccess());
	data->SetAttribute("laser",			pPlayer->GetLaserAccess());
	data->SetAttribute("machinegun",	1);
	data->SetAttribute("filename",		m_dGameData.szFileName);


	data->SetAttribute("HeatLevel",			pPlayer->GetHeatLevel());
	data->SetAttribute("DamageLevel",		pPlayer->GetDamageLevel());
	data->SetAttribute("AmmoLevel",			pPlayer->GetAmmoLevel());
	data->SetAttribute("HealthLevel",		pPlayer->GetHealthLevel());
	data->SetAttribute("ArmorLevel",		pPlayer->GetArmorLevel());
	data->SetAttribute("SpeedLevel",		pPlayer->GetSpeedLevel());
	
	data->SetAttribute("Score",				pPlayer->GetScore());
	//data->SetAttribute("RocketAccess",		m_dGameData.bRocketAccess);
	//data->SetAttribute("LaserAccess",		m_dGameData.bLaserAccess);
	//data->SetAttribute("NukeAccess",		m_dGameData.bNukeAccess);
	//data->SetAttribute("EMPAccess",			m_dGameData.bEMPAccess);
	//data->SetAttribute("ArtilleryAccess",	m_dGameData.bArtilleryAccess);
	//data->SetAttribute("FlamerAccess",		m_dGameData.bFlamerAccess);
	//data->SetAttribute("AirStrikeAccess",	m_dGameData.bAirStrikeAccess);
	//data->SetAttribute("SmokeBombAccess",	m_dGameData.bSmokeBombAccess);

	char szName[32];
	strcpy_s(szName,32,pPlayer->GetUserName().c_str());


	TiXmlText* pText = new TiXmlText(szName);
	data->LinkEndChild(pText);

	pRoot->LinkEndChild(data);

	doc.SaveFile(szFileName);

	delete(pDec);
}

void CGamePlayState::LoadText(void)
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
				TiXmlNode* pState = pLanguage->FirstChild("GameState");
				TiXmlNode* pButton = pState->FirstChild("Paused");
				TiXmlText* pText = pButton->FirstChild()->ToText();
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
				TiXmlNode* pState = pLanguage->FirstChild("GameState");
				TiXmlNode* pButton = pState->FirstChild("Paused");
				TiXmlText* pText = pButton->FirstChild()->ToText();
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
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("GameState");
				TiXmlNode* pButton = pState->FirstChild("Paused");
				TiXmlText* pText = pButton->FirstChild()->ToText();
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
			}
			break;
		}
	}
}
