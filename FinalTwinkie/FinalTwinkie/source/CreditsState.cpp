#include "CreditsState.h"

CCreditsState* CCreditsState::m_pSelf = nullptr;

CCreditsState* CCreditsState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CCreditsState();
	return m_pSelf;
}
void CCreditsState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}


CCreditsState::CCreditsState(void)
{
}


CCreditsState::~CCreditsState(void)
{
}


void CCreditsState::Enter(void)
{

}
void CCreditsState::Exit(void)
{

}
bool CCreditsState::Input(void)
{
	return true;
}
void CCreditsState::Update(float fDt)
{

}
void CCreditsState::Render(void)
{

}
