#include "ObjectFactory.h"


template <typename ClassTypeID, typename BaseClassType>
void CObjectFactory<ClassTypeID, BaseClassType>::DeleteInstance(void)
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

template <typename ClassTypeID, typename BaseClassType>
CObjectFactory<ClassTypeID, BaseClassType>::CObjectFactory(void)
{
}

template <typename ClassTypeID, typename BaseClassType>
CObjectFactory<ClassTypeID, BaseClassType>::~CObjectFactory(void)
{
}

template <typename ClassTypeID, typename BaseClassType>
bool CObjectFactory<ClassTypeID, BaseClassType>::RegisterClass(ClassTypeID id)
{
	std::pair<ClassTypeID, ObjectCreator> objectTypeDef;

	objectTypeDef.first = id;
	objectTypeDef.second = ConstructObject<NewClassType>;

	m_ObjectCreatorMap.insert(objectTypeDef);

	return true;
}

template <typename ClassTypeID, typename BaseClassType>
bool CObjectFactory<ClassTypeID, BaseClassType>::UnRegisterClass(ClassTypeID id)
{
	map<ClassTypeID, ObjectCreator>::iterator iter = m_ObjectCreatorMap.find(id);

	if(iter == m_ObjectCreatorMap.end())
		return false;

	m_ObjectCreatorMap.erase(iter);

	return true;
}

template <typename ClassTypeID, typename BaseClassType>
BaseClassType* CObjectFactory<ClassTypeID, BaseClassType>::CreateObject(ClassTypeID id)
{
	map<ClassTypeID, ObjectCreator>::iterator iter = m_ObjectCreatorMap.find(id);

	if(iter == m_ObjectCreatorMap.end())
		return NULL; 

	return (*iter).second();
}