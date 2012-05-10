#ifndef COBJECTFACTORY_H_
#define COBJECTFACTORY_H_

//#include "Entity.h"

#include <map>
using std::map;

template <typename ClassTypeID, typename BaseClassType>

class CObjectFactory
{
public:
	static CObjectFactory<ClassTypeID, BaseClassType*> GetInstance(void) { return m_pInstance; }
	static void DeleteInstance(void);
	bool RegisterClass(ClassTypeID id);
	bool UnRegisterClass(ClassTypeID id);
	BaseClassType* CreateObject(ClassTypeID id);
	void ShutdownObjectFactory(void) { m_ObjectCreatorMap.clear(); }

private:
	CObjectFactory(void);
	CObjectFactory(const CObjectFactory&);
	CObjectFactory& operator=(const CObjectFactory&);
	~CObjectFactory(void);

	typedef BaseClassType* (*ObjectCreator)(void);

	map<ClassTypeID, ObjectCreator> m_ObjectCreatorMap;

	template<typename NewClassType>
	static BaseClassType* ConstuctObject(void) { return NewClassType; }

	static CObjectFactory<ClassTypeID, BaseClassType> m_pInstance;
	void*	m_apClasses;
};

#endif