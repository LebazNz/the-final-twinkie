#include "OptionsState.h"

COptionsState* COptionsState::m_pSelf = nullptr;

COptionsState* COptionsState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new COptionsState;
	return m_pSelf;
}
void COptionsState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}


COptionsState::COptionsState(void)
{
}


COptionsState::~COptionsState(void)
{
}



void COptionsState::Enter(void)
{
}
void COptionsState::Exit(void)
{
}
bool COptionsState::Input(void)
{
	return true;
}
void COptionsState::Update(float fDt)
{
}
void COptionsState::Render(void)
{
}