#include "GamePlayState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "BitmapFont.h"
//#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "AnimationManager.h"
#include "Tile.h"

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
	//m_pOM	= CObjectManager::GetInstance();;
	//m_pOF	= CObjectFactory::GetInstance();
	//m_PM	= CParticleManager::GetInstance();
	//m_pMS	= CMessageSystem::GetInstance();
	//m_pTile = CTileManager::GetInstance();
	//m_AM	= CAnimationManager::GetInstance();
}

void CGamePlayState::Exit(void)
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
}

bool CGamePlayState::Input(void)
{
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		return true;
	}

	return true;
}

void CGamePlayState::Update(float fDt)
{
}

void CGamePlayState::Render(void)
{
	m_pD3D->Clear( 0, 0, 255 );
}
