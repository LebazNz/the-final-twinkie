#include "Game.h"

CGame* CGame::m_pSelf = nullptr;

CGame::CGame(void)
{
}


CGame::~CGame(void)
{
}

CGame* CGame::GetInstance(void)
{
	static CGame s_Instance;
	return &s_Instance;
}
void CGame::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}

}
void CGame::ChangeState(IGameState* pNewState)
{

}
void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int ScreenHeight, bool bWindowed)
{

}
void CGame::Shutdown(void)
{


}
bool CGame::Main(void)
{
	return true;
}
