#include "GamePlayState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "BitmapFont.h"
#include "MessageSystem.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
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

	m_pPlayer = nullptr;
	for(int i = 0; i < 16; ++i)
	{
		m_pEnemys[i] = nullptr;
	}
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

	m_pOF->RegisterClass<CEntity>("CEntity");
	m_pOF->RegisterClass<CEnemy>("CEnemy");

	for(int i = 0; i < 16; ++i)
	{
				
		m_pEnemys[i] = m_pOF->CreateObject("CEnemy");

		m_pEnemys[i]->SetPosX(50*(i+1));
		m_pEnemys[i]->SetPosY(50);
		m_pEnemys[i]->SetImageID(m_anEnemyIDs[i]);
		m_pEnemys[i]->SetWidth(40);
		m_pEnemys[i]->SetHeight(40);

		m_pOM->AddObject(m_pEnemys[i]);
	}}

void CGamePlayState::Exit(void)
{
	m_PM->RemoveAllEmitters();
	m_PM->DeleteInstance();if(m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	/*for(int i = 0; i < 16; ++i)
	{
		m_pEnemys[i]->Release();
		m_pEnemys[i] = nullptr;
	}*/

	for(int i = 0; i < 16; ++i)
	{
		if(m_anEnemyIDs[i] != -1)
		{
			m_pTM->UnloadTexture(m_anEnemyIDs[i]);
			m_anEnemyIDs[i] = -1;
		}
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

	return true;
}

void CGamePlayState::Update(float fDt)
{
	m_PM->UpdateEverything(fDt);
	m_pOM->UpdateAllObjects(fDt)}

void CGamePlayState::Render(void)
{
	m_pD3D->Clear( 255, 0, 0 );
	// Render game entities
	m_pOM->RenderAllObjects();

	
	// Flush the sprites
	//m_pD3D->GetSprite()->Flush();
	m_PM->RenderEverything();
}
