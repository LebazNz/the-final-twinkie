#include "GamePlayState.h"
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
#include "../Headers/GUI.h"
#include "../PickUps and Specials/Special.h"
#include "../PickUps and Specials/Nuke.h"

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
}

CGamePlayState::~CGamePlayState(void)
{
}

void CGamePlayState::Enter(void)
{
	if(m_bPaused == false)
	{
		m_pD3D	= CSGD_Direct3D::GetInstance();
		m_pDI	= CSGD_DirectInput::GetInstance();
		m_pTM	= CSGD_TextureManager::GetInstance();
		//m_pFont = CBitmapFont::GetInstance();
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

		m_nBackGround = m_pTM->LoadTexture(_T("resource/graphics/backgroundwall.png"));

		FXEnemy_Tails=m_PM->AddEmitter("resource/files/Enemy_Trail.xml");
		FXSapper_Explosion=m_PM->AddEmitter("resource/files/Explosion.xml");
		FXFlame=m_PM->AddEmitter("resource/files/Flame.xml");
		FXBuildingFlame=m_PM->AddEmitter("resource/files/Building Flame.xml");
		FXNuke=m_PM->AddEmitter("resource/files/Nuke.xml");

		m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
		m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 0 );
		m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_nPlayerID=m_pTM->LoadTexture(_T("resource/graphics/Green Base.png"));
		m_nPlayerTurretID=m_pTM->LoadTexture(_T("resource/graphics/Green Turret.png"));
		m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/AC_testturret.png"));
		m_anEnemyIDs[2]=m_pTM->LoadTexture(_T("resource/graphics/Building.png"));
		m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
		m_anEnemyIDs[3]=m_pTM->LoadTexture(_T("resource/graphics/123sprites_HUD.png"));
		m_anEnemyIDs[4]=m_pTM->LoadTexture(_T("resource/graphics/missile.png"));
		m_anEnemyIDs[5]=m_pTM->LoadTexture(_T("resource/graphics/rubble.png"));

		m_nPickupHealthID = m_pTM->LoadTexture(_T("resource/graphics/HealthPickUp.png"));
		m_nPickupAmmoID = m_pTM->LoadTexture(_T("resource/graphics/AmmoPickUp.png"));
		m_nPickupArmorID = m_pTM->LoadTexture(_T("resource/graphics/ArmorPickUp.png"));
		m_nPickupDoubleDID = m_pTM->LoadTexture(_T("resource/graphics/DoubleDamagePickUp.png"));
		m_nPickupNoReloadID = m_pTM->LoadTexture(_T("resource/graphics/NoReloadPickUp.png"));
		m_nPickupInvuID = m_pTM->LoadTexture(_T("resource/graphics/InvulnerabilityPickUp.png"));
		m_nPickupInfAmmoID = m_pTM->LoadTexture(_T("resource/graphics/InfAmmoPickUp.png"));
		m_nPickupMoneyID = m_pTM->LoadTexture(_T("resource/graphics/NukePickUp.png"));

		m_pMS->InitMessageSystem(&MessageProc);

		m_pOF->RegisterClassType<CEntity>("CEntity");
		m_pOF->RegisterClassType<CEnemy>("CEnemy");
		m_pOF->RegisterClassType<CBullet>("CBullet");
		m_pOF->RegisterClassType<CTurret>("CTurret");
		m_pOF->RegisterClassType<CTank>("CTank");
		m_pOF->RegisterClassType<CSapper>("CSapper");
		m_pOF->RegisterClassType<CBuilding>("CBuilding");
		m_pOF->RegisterClassType<CPickup>("CPickup");

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
		player->SetWeaponAmmo(m_dGameData.nShellAmmo,m_dGameData.nArtilleryAmmo,m_dGameData.nMissileAmmo);
		player->SetMaxWeaponAmmo(40,-1,-1);
		player->SetMoney(m_dGameData.nMoney);
		tVector2D v2Pos = { player->GetPosX(), player->GetPosY() };
		CNuke* pNuke = new CNuke;
		pNuke->SetEmitter(m_PM->GetEmitter(FXNuke));
		player->SetSpecial(pNuke);
		player->SetSpecial1Ammo(1);
		player->SetSpecial2Ammo(0);
		player->SetOldPos(v2Pos);
		player->SetSecondType(FLAME);
		m_pOM->AddObject(player);

	
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
		m_pOM->AddObject(PlayerTurret);
		PlayerTurret->Release();

		CSapper* sapper=(CSapper*)m_pOF->CreateObject("CSapper");
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
		sapper->SetExplosion(m_PM->GetEmitter(FXSapper_Explosion));
		m_pOM->AddObject(sapper);
		sapper->Release();

		CTank* pTank=(CTank*)m_pOF->CreateObject("CTank");
		pTank->SetImageID(m_nPlayerID);
		pTank->SetPosX(500);
		pTank->SetPosY(200);
		pTank->SetRotation(0);
		pTank->SetWidth(64);
		pTank->SetHeight(128);
		pTank->SetPlayer(player);
		pTank->SetRotationRate(0.75f);
		pTank->SetSight(400);
		pTank->SetVelX(30);
		pTank->SetVelY(30);
		pTank->SetHealth(300);
		pTank->SetHasATurret(true);
		m_pOM->AddObject(pTank);

		CTurret* pTurret=(CTurret*)m_pOF->CreateObject("CTurret");
		pTurret->SetImageID(m_nPlayerTurretID);
		pTank->SetTurret(pTurret);
		pTurret->SetPosX(pTank->GetPosX());
		pTurret->SetPosY(pTank->GetPosY());
		pTurret->SetOwner(pTank);
		pTurret->SetBullet(BUL_SHELL);
		pTurret->SetWidth(64);
		pTurret->SetHeight(128);
		pTurret->SetRotationPositon(32,98);
		pTurret->SetUpVec(0,-1);
		pTurret->SetDistance(300);
		//pTurret->SetFireRate(2.5f);
		pTurret->SetTarget(player);
		pTurret->SetRotationRate(1.0f);
		m_pOM->AddObject(pTurret);
		pTurret->Release();
		pTank->Release();

		pTank=(CTank*)m_pOF->CreateObject("CTank");
		pTank->SetImageID(m_nPlayerID);
		pTank->SetPosX(200);
		pTank->SetPosY(400);
		pTank->SetRotation(0);
		pTank->SetWidth(64);
		pTank->SetHeight(128);
		pTank->SetPlayer(player);
		pTank->SetRotationRate(0.75f);
		pTank->SetSight(400);
		pTank->SetVelX(30);
		pTank->SetVelY(30);
		pTank->SetHealth(300);
		pTank->SetHasATurret(true);
		m_pOM->AddObject(pTank);

		pTurret=(CTurret*)m_pOF->CreateObject("CTurret");
		pTurret->SetImageID(m_nPlayerTurretID);
		pTank->SetTurret(pTurret);
		pTurret->SetPosX(pTank->GetPosX());
		pTurret->SetPosY(pTank->GetPosY());
		pTurret->SetOwner(pTank);
		pTurret->SetBullet(BUL_SHELL);
		pTurret->SetWidth(64);
		pTurret->SetHeight(128);
		pTurret->SetRotationPositon(32,98);
		pTurret->SetUpVec(0,-1);
		pTurret->SetDistance(300);
		//pTurret->SetFireRate(2.5f);
		pTurret->SetTarget(player);
		pTurret->SetRotationRate(1.0f);
		m_pOM->AddObject(pTurret);
		pTurret->Release();
		pTank->Release();

		//m_nPosition = 0;
		//m_bPaused = false;

		CBuilding* building=(CBuilding*)m_pOF->CreateObject("CBuilding");
		building->SetPosX(200);
		building->SetPosY(200);
		building->SetHeight(128);
		building->SetWidth(128);
		building->SetHealth(5);
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

		building->Release();

		CEnemy* enemy=(CEnemy*)m_pOF->CreateObject("CEnemy");
		enemy->SetEType(RIFLE);
		enemy->SetImageID(m_anEnemyIDs[4]);
		enemy->SetPosX(300);
		enemy->SetPosY(300);
		enemy->SetHeight(32);
		enemy->SetWidth(32);
		enemy->SetPlayer(player);
		enemy->SetHealth(50);
		enemy->SetVelX(30);
		enemy->SetVelY(30);
		enemy->SetMinDistance(200);
		enemy->SetMaxDistance(600);
		enemy->SetShotTimer(0.1f);
		m_pOM->AddObject(enemy);

		m_pGUI->SetHudID(m_anEnemyIDs[3]);
		m_pGUI->SetPlayer(player);

		m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);

		m_pTile->Load("resource/files/graphic_layer.xml");

		player->SetMoney(m_dGameData.nMoney);
	}
	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();

	D3DXCreateTexture(m_pD3D->GetDirect3DDevice(), 125, 120, 0, D3DUSAGE_RENDERTARGET|D3DUSAGE_AUTOGENMIPMAP, D3DFMT_R8G8B8, D3DPOOL_DEFAULT, &MiniMap); 

}

void CGamePlayState::Exit(void)
{
	SaveGame(m_dGameData.szFileName);

	if(m_bPaused == false)
	{
		m_PM->RemoveAllBaseEmitters();
		m_PM->DeleteInstance();

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
	if(m_bPaused)
	{
		if(m_pDI->KeyPressed(DIK_ESCAPE))
		{
			m_bPaused = false;
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			return true;
		}
		if(m_pDI->KeyPressed(DIK_RETURN))
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
		if(m_pDI->KeyPressed(DIK_UP))
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
		else if(m_pDI->KeyPressed(DIK_DOWN))
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
		else if(m_pDI->MouseButtonPressed(0))
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
	}
	else
	{
		if(m_pDI->KeyPressed(DIK_ESCAPE))
		{
			m_bPaused = !m_bPaused;
		}
		if(m_pDI->KeyPressed(DIK_2))
		{
			
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),1);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_3))
		{
			CPlayer::GetInstance()->SetArmor(CPlayer::GetInstance()->GetArmor()-50);
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),2);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_4))
		{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),3);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_5))
		{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),4);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_6))
		{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),5);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyPressed(DIK_7))
		{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),6);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
		if(m_pDI->KeyDown(DIK_8))
		{
				CCreatePickupMessage* pMsg = new CCreatePickupMessage(MSG_CREATEPICKUP,CPlayer::GetInstance(),7);
				CMessageSystem::GetInstance()->SndMessage(pMsg);
				pMsg = nullptr;
			
		}
	}
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		//int emitter=m_PM->AddEmitter("resource/files/Nuke.xml");
		CEmitter* pEmi=m_PM->GetEmitter(FXNuke);
		pEmi->UpdateEmitterPos(400-Camera::GetInstance()->GetPosX(),300-Camera::GetInstance()->GetPosY());
		pEmi->ActivateEmitter();
	}

	// Enter ShopState
	if(m_pDI->KeyPressed(DIK_1))
	{
		CGame::GetInstance()->ChangeState(CShopState::GetInstance());
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
}

void CGamePlayState::Render(void)
{
	
	
	m_pD3D->Clear( 0, 255, 255 );
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
		//m_AM->Render();
		// Flush the sprites
		m_PM->RenderEverything();
		m_pD3D->GetSprite()->Draw(MiniMap, NULL, &D3DXVECTOR3(0,0,0),&D3DXVECTOR3(661,409,0), D3DCOLOR_ARGB(255,255,255,255));
		m_pGUI->Render();
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
		font->Print("Paused",(CGame::GetInstance()->GetWidth()/2)-125,CGame::GetInstance()->GetHeight()/2-100,3.0f,D3DCOLOR_XRGB(255,255,255));
		font->Print("Resume",(CGame::GetInstance()->GetWidth()/2)-48,CGame::GetInstance()->GetHeight()/2,1.0f,		fScale1);
		font->Print("Options",(CGame::GetInstance()->GetWidth()/2)-50,CGame::GetInstance()->GetHeight()/2+50,1.0f,	fScale2);
		font->Print("Exit",(CGame::GetInstance()->GetWidth()/2)-30,CGame::GetInstance()->GetHeight()/2+100,1.0f,	fScale3);
	
	}

	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
	//CBitmapFont* font = CBitmapFont::GetInstance();
	//font->Init(COptionsState::GetInstance()->GetLang());

	//_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	//font->Print(buffer,650,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	//_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	//font->Print(buffer,650,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	//_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	//font->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	//_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	//font->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));
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
								Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()-pMessage->GetFiringEntity()->GetWidth()/2+32+98*Up.fX-C->GetPosX());//+norVec.fX-30);
								Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()-pMessage->GetFiringEntity()->GetHeight()/2+64+98*Up.fY-C->GetPosY());//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
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
							Bullet->SetPosX((pMessage->GetFiringEntity()->GetPosX()+C->GetPosX())-pMessage->GetFiringEntity()->GetWidth()/2+32+98*Up.fX-C->GetPosX());//+norVec.fX-30);
							Bullet->SetPosY((pMessage->GetFiringEntity()->GetPosY()+C->GetPosY())-pMessage->GetFiringEntity()->GetHeight()/2+64+98*Up.fY-C->GetPosY());//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
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
				break;
			case BUL_ARTILLERY:
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
							Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()-pMessage->GetFiringEntity()->GetWidth()/2+32+98*Up.fX-C->GetPosX());//+norVec.fX-30);
							Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()-pMessage->GetFiringEntity()->GetHeight()/2+64+98*Up.fY-C->GetPosY());//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
							if(player->GetDoubleDamage())
									Bullet->SetDamage(5.0f*2);
								else
									Bullet->SetDamage(5.0f);
						}
						else
						{
							Bullet->SetPosX((pMessage->GetFiringEntity()->GetPosX()+C->GetPosX())-pMessage->GetFiringEntity()->GetWidth()/2+32+98*Up.fX-C->GetPosX());//+norVec.fX-30);
							Bullet->SetPosY((pMessage->GetFiringEntity()->GetPosY()+C->GetPosY())-pMessage->GetFiringEntity()->GetHeight()/2+64+98*Up.fY-C->GetPosY());//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
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
					Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()-pMessage->GetFiringEntity()->GetWidth()/2+32+98*vel.fX-C->GetPosX());
					Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()-pMessage->GetFiringEntity()->GetHeight()/2+64+98*vel.fY-C->GetPosY());
					if(player->GetDoubleDamage())
						Bullet->SetDamage(1.0f*2);
					else
						Bullet->SetDamage(1.0f);
					//Bullet->SetImageID(pSelf->m_anBulletImageIDs[BUL_SHELL]);
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
					sapper->SetExplosion(pSelf->m_PM->GetEmitter(pSelf->FXSapper_Explosion));
					pSelf->m_pOM->AddObject(sapper);
					sapper->Release();
					sapper = nullptr;
				}
				break;
			case TANK:
				{
					// TO DO: SET UP MESSAGES TO GET POSITIONS
					pSelf->m_pEnemy = pSelf->m_pOF->CreateObject("CTank");
					pSelf->m_pEnemy->SetImageID(pSelf->m_nPlayerID);
					pSelf->m_pEnemy->SetPosX(pMessage->GetPosX());
					pSelf->m_pEnemy->SetPosY(pMessage->GetPosY());	
					pSelf->m_pEnemy->SetWidth(64);
					pSelf->m_pEnemy->SetHeight(128);

					CPlayer* player = CPlayer::GetInstance();
					CTank* tank = dynamic_cast<CTank*>(pSelf->m_pEnemy);
					
					tank->SetPlayer(player);
					tank->SetRotation(0);
					tank->SetRotationRate(0.75f);
					tank->SetSight(400);
					tank->SetVelX(30);
					tank->SetVelY(30);
					tank->SetHealth(300);
					tank->SetHasATurret(true);
					pSelf->m_pOM->AddObject(tank);

					pSelf->m_pTurret = pSelf->m_pOF->CreateObject("CTurret");
					pSelf->m_pTurret->SetImageID(pSelf->m_nPlayerTurretID);					
					pSelf->m_pTurret->SetPosX(pSelf->m_pEnemy->GetPosX());
					pSelf->m_pTurret->SetPosY(pSelf->m_pEnemy->GetPosY());
					pSelf->m_pTurret->SetWidth(64);
					pSelf->m_pTurret->SetHeight(128);

					CTurret* turret = dynamic_cast<CTurret*>(pSelf->m_pTurret);
					tank->SetTurret(turret);
					turret->SetOwner(pSelf->m_pEnemy);
					turret->SetBullet(BUL_SHELL);	
					turret->SetRotationPositon(32,98);
					turret->SetUpVec(0,-1);
					turret->SetDistance(300);
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
				//	turret->SetFireRate(2.5f);
					turret->SetTarget(player);
					turret->SetRotationRate(1.0f);
					pSelf->m_pOM->AddObject(turret);
					pSelf->m_pTurret->Release();
					pSelf->m_pTurret = nullptr;
				
				}
				break;

			case RIFLE:
				{
				}
				break;
			case ROCKET:
				{
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

			int nRandNum = rand()%8;
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
			//pSelf->m_pOM->RemoveObject(dynamic_cast<CDestroyBuildingMessage*>(pMsg)->GetBuilding());
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

			pPickup->SetAliveTime(150.0f);

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
			pBullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()+(pMessage->GetFiringEntity()->GetWidth())*Up.fX);//-C->GetPosX());
			pBullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()+(pMessage->GetFiringEntity()->GetHeight())*Up.fY);//-C->GetPosY());
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
					pSelf->m_pOM->AddObject(pBullet);
					pBullet->Release();
					pBullet = nullptr;
				}
				break;
			case BUL_ROCKET:
				{
				}
				break;
			}

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

	data->SetAttribute("HeatLevel",		pPlayer->GetHealthLevel());
	data->SetAttribute("DamageLevel",	pPlayer->GetDamageLevel());
	data->SetAttribute("AmmoLevel",		pPlayer->GetAmmoLevel());
	data->SetAttribute("HealthLevel",	pPlayer->GetHealthLevel());
	data->SetAttribute("ArmorLevel",	pPlayer->GetArmorLevel());
	data->SetAttribute("SpeedLevel",	pPlayer->GetSpeedLevel());
	
	//data->SetAttribute("RocketAccess",		m_dGameData.bRocketAccess);
	//data->SetAttribute("LaserAccess",		m_dGameData.bLaserAccess);
	//data->SetAttribute("NukeAccess",		m_dGameData.bNukeAccess);
	//data->SetAttribute("EMPAccess",			m_dGameData.bEMPAccess);
	//data->SetAttribute("ArtilleryAccess",	m_dGameData.bArtilleryAccess);
	//data->SetAttribute("FlamerAccess",		m_dGameData.bFlamerAccess);
	//data->SetAttribute("AirStrikeAccess",	m_dGameData.bAirStrikeAccess);
	//data->SetAttribute("SmokeBombAccess",	m_dGameData.bSmokeBombAccess);

	
	




	TiXmlText* pText = new TiXmlText(m_dGameData.szName);
	data->LinkEndChild(pText);

	pRoot->LinkEndChild(data);

	doc.SaveFile(szFileName);

	delete(pDec);
}
