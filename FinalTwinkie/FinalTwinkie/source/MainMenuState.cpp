#include "MainMenuState.h"

CMainMenuState* CMainMenuState::m_pSelf = nullptr;

CMainMenuState* CMainMenuState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CMainMenuState();
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
}


CMainMenuState::~CMainMenuState(void)
{
}



void CMainMenuState::Enter(void)
{
}
void CMainMenuState::Exit(void)
{
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
}