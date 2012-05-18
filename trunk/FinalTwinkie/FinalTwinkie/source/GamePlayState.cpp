#include "GamePlayState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "BitmapFont.h"
#include "Bullet.h"
#include "MessageSystem.h"
#include "EventSystem.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
#include "CreateEnemyMessage.h"
#include "CreateBulletMessage.h"
#include "DestroyBulletMessage.h"
#include "DestroyEnemyMessage.h"
#include "Tile.h"
#include "Enemy.h"
#include "Player.h"
#include "Turret.h"
#include "Camera.h"
#include "Sapper.h"
#include "Tank.h"
#include "Emitter.h"

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

	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
}

CGamePlayState::~CGamePlayState(void)
{
}

void CGamePlayState::Enter(void)
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

	FXEnemy_Tails=m_PM->AddEmitter("resource/files/Enemy_Trail.xml");
	FXSapper_Explosion=m_PM->AddEmitter("resource/files/Explosion.xml");
	m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
	m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
	m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 0 );
	m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
	m_nPlayerID=m_pTM->LoadTexture(_T("resource/graphics/Green Base.png"));
	m_nPlayerTurretID=m_pTM->LoadTexture(_T("resource/graphics/Green Turret.png"));
	m_anEnemyIDs[1]=m_pTM->LoadTexture(_T("resource/graphics/AC_testturret.png"));

	m_nBackGround = m_pTM->LoadTexture(_T("resource/graphics/backgroundwall.png"),0);

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
	player->SetPosX(CGame::GetInstance()->GetWidth()/2);
	player->SetPosY(CGame::GetInstance()->GetHeight()/2);
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

	PlayerTurret->Release();
	PlayerTurret = nullptr;

}

void CGamePlayState::Exit(void)
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

bool CGamePlayState::Input(void)
{
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}
	if(m_pDI->KeyPressed(DIK_N))
	{
		CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,SAPPER);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
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
	Camera::GetInstance()->Update(dynamic_cast< CPlayer* >( m_pPlayer),0,0,fDt);
	m_PM->UpdateEverything(fDt);
	m_pOM->UpdateAllObjects(fDt);
	m_pOM->CheckCollisions();

	m_pES->ProcessEvents();
	m_pMS->ProcessMessages();
}

void CGamePlayState::Render(void)
{
	m_pD3D->Clear( 0, 0, 0 );
	m_pTM->Draw(m_nBackGround,Camera::GetInstance()->GetPosX(),
		Camera::GetInstance()->GetPosY(),5,5,nullptr,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
	// Render game entities
	m_pOM->RenderAllObjects();
	m_pTM->Draw(m_nPlayerID, m_pDI->MouseGetPosX(), m_pDI->MouseGetPosY(), 0.1f, 0.1f);
	m_AM->Render();
	// Flush the sprites
	m_pD3D->GetSprite()->Flush();
	m_PM->RenderEverything();
}

void CGamePlayState::MessageProc(CMessage* pMsg)
{
	CGamePlayState* pSelf = CGamePlayState::GetInstance();

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
					if(pMessage->GetFiringEntity()->GetType() == OBJ_PLAYER)
						Bullet->SetWhoFired(false);
					else
						Bullet->SetWhoFired(true);
					if(pMessage->GetFiringEntity() != nullptr)
					{
						tVector2D norVec = pMessage->GetFiringEntity()->GetLook();
						tVector2D Up={0,-1};
						Up=Vector2DRotate(Up, pMessage->GetFiringEntity()->GetRotation());
						norVec = Vector2DNormalize(norVec);
						Bullet->SetRotation(pMessage->GetFiringEntity()->GetRotation());
						Bullet->SetPosX(pMessage->GetFiringEntity()->GetPosX()-pMessage->GetFiringEntity()->GetWidth()/2+98*Up.fX);//+norVec.fX-30);
						Bullet->SetPosY(pMessage->GetFiringEntity()->GetPosY()-pMessage->GetFiringEntity()->GetHeight()/2+32+98*Up.fY);//+norVec.fY*pMessage->GetFiringEntity()->GetHeight());
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
			/*pBullet->Release();
			pBullet = nullptr;*/
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
