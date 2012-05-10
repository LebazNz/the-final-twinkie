#include "ObjectFactory.h"

CObjectFactory* CObjectFactory::m_pInstance = nullptr;

CObjectFactory* CObjectFactory::GetInstance(void)
{
	if(m_pInstance == nullptr)
		m_pInstance = new CObjectFactory();
	return m_pInstance;
}
void CObjectFactory::DeleteInstance(void)
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}


CObjectFactory::CObjectFactory(void)
{
}


CObjectFactory::~CObjectFactory(void)
{
}



int CObjectFactory::RegisterClass(void* pClass)
{
	return 0;
}
void CObjectFactory::UnRegisterClass(int nld)
{

}
CEntity* CObjectFactory::CreateObject(int nld)
{
	CEntity fred = new CEntity();

	return fred;
}