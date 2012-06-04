#include "LoadOutState.h"

CLoadOutState* CLoadOutState::m_pSelf = nullptr;
CLoadOutState::CLoadOutState(void)
{
}


CLoadOutState::~CLoadOutState(void)
{
}

CLoadOutState* CLoadOutState::GetInstance( void )
{
	if(!m_pSelf)
		m_pSelf = new CLoadOutState;
	return m_pSelf;
}

void CLoadOutState::DeleteInstance( void )
{
	if(m_pSelf)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CLoadOutState::Enter( void )
{

}

void CLoadOutState::Exit( void )
{

}

bool CLoadOutState::Input( void )
{
	return true;
}

void CLoadOutState::Update( float fDt )
{

}

void CLoadOutState::Render( void )
{

}
