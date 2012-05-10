#include "GamePlayState.h"

CGamePlayState* CGamePlayState::m_pSelf = nullptr;

CGamePlayState* CGamePlayState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGamePlayState();
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
}


CGamePlayState::~CGamePlayState(void)
{
}



void CGamePlayState::Enter(void)
{
}
void CGamePlayState::Exit(void)
{
}
bool CGamePlayState::Input(void)
{
	return true;
}
void CGamePlayState::Update(float fDt)
{
}
void CGamePlayState::Render(void)
{
}