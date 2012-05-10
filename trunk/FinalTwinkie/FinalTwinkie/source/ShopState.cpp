#include "ShopState.h"


CShopState* CShopState::m_pSelf = nullptr;

CShopState* CShopState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CShopState();
	return m_pSelf;
}
void CShopState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}


CShopState::CShopState(void)
{
}


CShopState::~CShopState(void)
{
}


void CShopState::Enter(void)
{

}
void CShopState::Exit(void)
{

}
bool CShopState::Input(void)
{
	return true;
}
void CShopState::Update(float fDt)
{

}
void CShopState::Render(void)
{

}
