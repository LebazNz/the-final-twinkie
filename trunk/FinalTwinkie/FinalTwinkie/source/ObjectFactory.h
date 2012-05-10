#ifndef COBJECTFACTORY_H_
#define COBJECTFACTORY_H_

#include "Entity.h"
class CObjectFactory
{
public:
	static CObjectFactory* GetInstance(void);
	static void DeleteInstance(void);
	int RegisterClass(void* pClass);
	void UnRegisterClass(int nld);
	CEntity* CreateObject(int nld);
private:
	CObjectFactory(void);
	CObjectFactory(const CObjectFactory&);
	CObjectFactory& operator=(const CObjectFactory&);
	~CObjectFactory(void);

	static CObjectFactory* m_pInstance;
	void*	m_apClasses;
};

#endif