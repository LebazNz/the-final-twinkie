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
#include "../World and Tile/Tile.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Turret.h"
#include "../Headers/Camera.h"
#include "../GameObjects/Sapper.h"
#include "../GameObjects/Tank.h"
#include "../Particle/Emitter.h"

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
}

CGamePlayState::~CGamePlayState(void)
{
}

void CGamePlayState::Enter(void)
{
	/*Data dGameData = {"Herp Derp",1,0,0,1,500,1,0,1,0,1,0,1,0,1,1,0,1,0,1,"savedGame3.xml"};

	m_dGameData = dGameData;*/

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
		//m_pTile = CTileManager::GetInstance();
		m_AM	= CAnimationManager::GetInstance();
		m_pES = CEventSystem::GetInstance();

		for(int i = 0; i < 16; ++i)
		{
			m_anEnemyIDs[i] = m_pTM->LoadTexture( _T( "resource/graphics/JF_enemy1.png"), 	0 );
		}

		m_AM->Load("AnimationInfo.xml");
		//m_AM->Save("AnimationInfo.xml");
		m_pOF->RegisterClassType<CEntity>("CEntity");
		m_pOF->RegisterClassType<CEnemy>("CEnemy");

		m_nBackGround = m_pTM->LoadTexture(_T("resource/graphics/backgroundwall.png"));

		FXEnemy_Tails=m_PM->AddEmitter("resource/files/Enemy_Trail.xml");
		FXSapper_Explosion=m_PM->AddEmitter("resource/files/Explosion.xml");
		m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
		m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 0 );
		m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
		m_nPlayerID=m_pTM->LoadTexture(_T("resource/graphics/Green Base.png"));
		m_nPlayerTurretID=m_pTM->LoadTexture(_T("resource/graphics/Green Turret.png"));
		m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/AC_testturret.png"));

		m_pMS->InitMessageSystem(&MessageProc);

		m_pOF->RegisterClassType<CEntity>("CEntity");
		m_pOF->RegisterClassType<CEnemy>("CEnemy");
		m_pOF->RegisterClassType<CBullet>("CBullet");
		m_pOF->RegisterClassType<CPlayer>("CPlayer");
		m_pOF->RegisterClassType<CTurret>("CTurret");
		m_pOF->RegisterClassType<CTank>("CTank");
		m_pOF->RegisterClassType<CSapper>("CSapper");
	
		m_pPlayer=m_pOF->CreateObject("CPlayer");
		CPlayer* player=dynamic_cast<CPlayer*>(m_pPlayer);
		player->SetImageID(m_nPlayerID);
		player->SetPosX(float(CGame::GetInstance()->GetWidth()/2));
		player->SetPosY(float(CGame::GetInstance()->GetHeight()/2));
		player->SetRotation(0);
		player->SetWidth(64);
		player->SetHeight(128);
		player->SetVelX(180);
		player->SetVelY(180);
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
		m_pOM->AddObject(PlayerTurret);
		PlayerTurret->Release();
		//player->Release();

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
		pTurret->SetTarget(player);
		m_pOM->AddObject(pTurret);
		pTurret->Release();
		pTank->Release();
		m_nPosition = 0;
		m_bPaused = false;

		m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	}
}

void CGamePlayState::Exit(void)
{
	SaveGame(m_dGameData.szFileName);

	if(m_bPaused == false)
	{
		m_PM->RemoveAllBaseEmitters();
		m_PM->DeleteInstance();
	
		if(m_pPlayer != nullptr)
		{
			m_pPlayer->Release();
			m_pPlayer = nullptr;
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
		m_pTile = nullptr;
		m_AM	= nullptr;
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
	}
	else
	{
		if(m_pDI->KeyPressed(DIK_ESCAPE))
		{
			m_bPaused = !m_bPaused;
		}
		if(m_pDI->KeyPressed(DIK_N))
		{
			CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,SAPPER);
			CMessageSystem::GetInstance()->SndMessage(pMsg);
			pMsg = nullptr;
		}
	}
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		int emitter=m_PM->AddEmitter("resource/files/Box.xml");
		CEmitter* pEmi=m_PM->GetEmitter(emitter);
		pEmi->UpdateEmitterPos(400,300);
		pEmi->ActivateEmitter();
	}
	return true;
}

void CGamePlayState::Update(float fDt)
{
	Camera::GetInstance()->Update(dynamic_cast<CPlayer*>(m_pPlayer),0,0,fDt);
	if(!m_bPaused)
	{
		m_PM->UpdateEverything(fDt);
		m_pOM->UpdateAllObjects(fDt);
		m_pOM->CheckCollisions();

		m_pES->ProcessEvents();
		m_pMS->ProcessMessages();

	}
}

void CGamePlayState::Render(void)
{
	m_pD3D->Clear( 0, 255, 255 );
	m_pTM->Draw(m_nBackGround,int(Camera::GetInstance()->GetPosX()),
		int(Camera::GetInstance()->GetPosY()),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
	// Render game entities
	m_pOM->RenderAllObjects();
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX(), m_pDI->MouseGetPosY(), 1.0f, 1.0f);
	m_AM->Render();
	// Flush the sprites
	m_pD3D->GetSprite()->Flush();	
	m_PM->RenderEverything();

	if(m_bPaused)
	{
		CBitmapFont* font = CBitmapFont::GetInstance();
		font->Init("resource/graphics/Font.png",43,32,9,11,20,' ');


		float fScale1, fScale2, fScale3;
		switch(m_nPosition)
		{
		case 0:
			fScale1 = 1.0f;
			fScale2 = 0.75f;
			fScale3 = 0.75f;
			
			break;
		case 1:
			fScale1 = 0.75f;
			fScale2 = 1.0f;
			fScale3 = 0.75f;
			
			break;
		case 2:
			fScale1 = 0.75f;
			fScale2 = 0.75f;
			fScale3 = 1.0f;
			
			break;
		}

		m_pD3D->GetSprite()->Flush();
		font->Print("Paused",(CGame::GetInstance()->GetWidth()/2)-125,CGame::GetInstance()->GetHeight()/2-100,1.5f,D3DCOLOR_XRGB(255,255,255));
		font->Print("Resume",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2,fScale1,D3DCOLOR_XRGB(255,255,255));
		font->Print("Options",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2+50,fScale2,D3DCOLOR_XRGB(255,255,255));
		font->Print("Exit",(CGame::GetInstance()->GetWidth()/2)-70,CGame::GetInstance()->GetHeight()/2+100,fScale3,D3DCOLOR_XRGB(255,255,255));
	
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
			switch(pMessage->GetBulletType())
			{
			case BUL_SHELL:
				{
					CEventSystem::GetInstance()->SendEvent("play_explode",Bullet);

					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
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
						Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()-pMessage->GetFiringEntity()->GetWidth()/2+32+98*Up.fX-C->GetPosX());//+norVec.fX-30);
						Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()-pMessage->GetFiringEntity()->GetHeight()/2+64+98*Up.fY-C->GetPosY());//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
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
				break;
			case BUL_LASER:
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
					int i = rand()%10;
					pSelf->m_pEnemy = pSelf->m_pOF->CreateObject("CEnemy");

					pSelf->m_pEnemy->SetPosX((float)(50*(i+1)));
					pSelf->m_pEnemy->SetPosY(50);
					pSelf->m_pEnemy->SetImageID(pSelf->m_anEnemyIDs[0]);
					pSelf->m_pEnemy->SetWidth(40);
					pSelf->m_pEnemy->SetHeight(40);
					CEnemy* enemy=dynamic_cast<CEnemy*>(pSelf->m_pEnemy);
					enemy->SetTail(pSelf->m_PM->GetEmitter(pSelf->FXEnemy_Tails));
					enemy->GetTail()->ActivateEmitter();

					pSelf->m_pOM->AddObject(pSelf->m_pEnemy);

					pSelf->m_pEnemy->Release();
					pSelf->m_pEnemy = nullptr;
				}
				break;
			case TANK:
				{
				}
				break;
			case TURRET:
				{
				}
				break;
			};
		}
		break;
	case MSG_DESTROYENEMY:
		{
			CEnemy* pEnemy = dynamic_cast<CDestroyEnemyMessage*>(pMsg)->GetEnemy();
			pSelf->m_PM->RemoveAttachedEmitter(pEnemy->GetTail());
			pSelf->m_pOM->RemoveObject(pEnemy);
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
	TiXmlDocument doc;

	TiXmlDeclaration* pDec = new TiXmlDeclaration("1.0", "utf-8", "");

	TiXmlElement* pRoot = new TiXmlElement("Save_game_data");

	doc.LinkEndChild(pRoot);

	TiXmlElement* data = new TiXmlElement("game_data");

	data->SetAttribute("level",			m_dGameData.nLevel);
	data->SetAttribute("money",			m_dGameData.nMoney);
	data->SetAttribute("hp",			m_dGameData.nHp);
	data->SetAttribute("armor",			m_dGameData.nArmor);
	data->SetAttribute("ammo",			m_dGameData.nAmmo);
	data->SetAttribute("speed",			m_dGameData.nSpeed);
	data->SetAttribute("shellammo",		m_dGameData.nShellAmmo);
	data->SetAttribute("missileammo",	m_dGameData.nMissileAmmo);
	data->SetAttribute("artilleryammo", m_dGameData.nArtilleryAmmo);
	data->SetAttribute("shell",			m_dGameData.bShell);
	data->SetAttribute("missile",		m_dGameData.bMissile);
	data->SetAttribute("artillery",		m_dGameData.bArtillery);
	data->SetAttribute("airstrike",		m_dGameData.bAirStrike);
	data->SetAttribute("emp",			m_dGameData.bEMP);
	data->SetAttribute("nuke",			m_dGameData.bNuke);
	data->SetAttribute("reinforce",		m_dGameData.bReinforce);
	data->SetAttribute("smoke",			m_dGameData.bSmoke);
	data->SetAttribute("laser",			m_dGameData.nLaser);
	data->SetAttribute("machinegun",	m_dGameData.nMachineGun);
	data->SetAttribute("filename",		m_dGameData.szFileName);

	TiXmlText* pText = new TiXmlText(m_dGameData.szName);
	data->LinkEndChild(pText);

	pRoot->LinkEndChild(data);

	doc.SaveFile(szFileName);
}
