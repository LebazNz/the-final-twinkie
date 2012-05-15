#include "GamePlayState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "BitmapFont.h"
#include "Bullet.h"
#include "MessageSystem.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
#include "CreateEnemyMessage.h"
#include "CreateBulletMessage.h"
#include "DestroyBulletMessage.h"
#include "DestroyEnemyMessage.h"
#include "Tile.h"
#include "Enemy.h"

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


	for(int i = 0; i < 16; ++i)
	{
		m_anEnemyIDs[i] = -1;
	}

	for(int i = 0; i < 4; ++i)
		m_anBulletImageIDs[i] = -1;

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
	//m_AM	= CAnimationManager::GetInstance();

	for(int i = 0; i < 16; ++i)
	{
		m_anEnemyIDs[i] = m_pTM->LoadTexture( _T( "resource/graphics/JF_enemy1.png"), 	0 );
	}

	
	m_anBulletImageIDs[0] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );
	m_anBulletImageIDs[1] = m_pTM->LoadTexture( _T( "resource/graphics/missile.png"), 	0 );
	m_anBulletImageIDs[2] = m_pTM->LoadTexture( _T( "resource/graphics/artillery.png"), 	0 );
	m_anBulletImageIDs[3] = m_pTM->LoadTexture( _T( "resource/graphics/shell.png"), 	0 );

	m_pMS->InitMessageSystem(&MessageProc);

	m_pOF->RegisterClassType<CEntity>("CEntity");
	m_pOF->RegisterClassType<CEnemy>("CEnemy");
	m_pOF->RegisterClassType<CBullet>("CBullet");

	/*for(int i = 0; i < 10; ++i)
	{
				
		m_pEnemys[i] = m_pOF->CreateObject("CEnemy");

		m_pEnemys[i]->SetPosX(50*(i+1));
		m_pEnemys[i]->SetPosY(50);
		m_pEnemys[i]->SetImageID(m_anEnemyIDs[i]);
		m_pEnemys[i]->SetWidth(40);
		m_pEnemys[i]->SetHeight(40);

		m_pOM->AddObject(m_pEnemys[i]);
	}*/
}

void CGamePlayState::Exit(void)
{
	m_PM->RemoveAllEmitters();
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
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		m_PM->AddEmitter("");
	}
	if(m_pDI->KeyPressed(DIK_N))
	{
		CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,SAPPER);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}

	if(m_pDI->KeyPressed(DIK_SPACE))
	{
		CCreateBulletMessage* pMsg = new CCreateBulletMessage(MSG_CREATEBULLET,BUL_SHELL,m_pEnemy);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}

	return true;
}

void CGamePlayState::Update(float fDt)
{
	m_PM->UpdateEverything(fDt);
	m_pOM->UpdateAllObjects(fDt);
	m_pOM->CheckCollisions();
	m_pMS->ProcessMessages();
}

void CGamePlayState::Render(void)
{
	m_pD3D->Clear( 0, 0, 0 );
	m_pD3D->GetSprite()->Flush();
	// Render game entities
	m_pOM->RenderAllObjects();

	
	// Flush the sprites
	//m_pD3D->GetSprite()->Flush();
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
					Bullet->SetWidth(32);
					Bullet->SetHeight(32);
					Bullet->SetWhoFired(false);
					/*if(pMessage->GetFiringEntity() != nullptr)
					{
						Bullet->SetPosX(CGame::GetInstance()->GetWidth()/2);
						Bullet->SetPosY(CGame::GetInstance()->GetHeight()/2);
					}*/

					Bullet->SetPosX(CGame::GetInstance()->GetWidth()/2);
					Bullet->SetPosY(CGame::GetInstance()->GetHeight()/2);

					float randX = float(rand()%(600-(-600)+1)+-600);
					float randY = float(rand()%(600-(-600)+1)+-600);

					Bullet->SetVelX(randX);
					Bullet->SetVelY(randY);

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

					pSelf->m_pEnemy->SetPosX(50*(i+1));
					pSelf->m_pEnemy->SetPosY(50);
					pSelf->m_pEnemy->SetImageID(pSelf->m_anEnemyIDs[i]);
					pSelf->m_pEnemy->SetWidth(40);
					pSelf->m_pEnemy->SetHeight(40);

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
			pSelf->m_pOM->RemoveObject(pEnemy);
		}
		break;
	};
}
