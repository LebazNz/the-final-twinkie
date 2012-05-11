#include "MainMenuState.h"

CMainMenuState* CMainMenuState::m_pSelf = nullptr;

CMainMenuState* CMainMenuState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CMainMenuState;
	return m_pSelf;
}

void CMainMenuState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CMainMenuState::CMainMenuState(void)
{
	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nSelected = 0;
	
	m_nBGImageID = -1;
}

CMainMenuState::~CMainMenuState(void)
{
}

void CMainMenuState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();

	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/Menu_Screen.png"),D3DCOLOR_XRGB(255,0,255));
}

void CMainMenuState::Exit(void)
{
	if(m_nBGImageID != -1)
	{
		m_pTM->UnloadTexture(m_nBGImageID);
		m_nBGImageID = -1;
	}

	m_pD3D = nullptr;
	m_pDI = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	
	m_nSelected = 0;
}

bool CMainMenuState::Input(void)
{
	return true;
}

void CMainMenuState::Update(float fDt)
{
}

void CMainMenuState::Render(void)
{
	m_pTM->Draw(m_nBGImageID,0,0,0.85f,0.75f,nullptr,0,0,0);
	m_pD3D->GetSprite()->Flush();
}
