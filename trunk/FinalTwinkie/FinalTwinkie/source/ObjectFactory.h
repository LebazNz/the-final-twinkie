#ifndef COBJECTFACTORY_H_
#define COBJECTFACTORY_H_


#include <map>
using std::map;

template <typename ClassTypeID, typename BaseClassType>
class CObjectFactory
{
private:

	static CObjectFactory<ClassTypeID, BaseClassType> m_pInstance;

	CObjectFactory(void) {}
	CObjectFactory(const CObjectFactory&);
	CObjectFactory& operator=(const CObjectFactory&);
	~CObjectFactory(void) {}

	typedef BaseClassType* (*ObjectCreator)(void);

	map<ClassTypeID, ObjectCreator> m_ObjectCreatorMap;

	template<typename NewClassType>
	static BaseClassType* ConstuctObject(void) { return new NewClassType; }

public:
	static CObjectFactory<ClassTypeID, BaseClassType>* GetInstance(void) 
	{ return &m_pInstance; }
	
	/*static void DeleteInstance(void)
	{
		if(m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}*/

	template<typename NewClassType>
	bool RegisterClass(ClassTypeID id)
	{
		std::pair<ClassTypeID, ObjectCreator> objectTypeDef;

		objectTypeDef.first = id;
		objectTypeDef.second = ConstuctObject<NewClassType>;

		m_ObjectCreatorMap.insert(objectTypeDef);

		return true;
	}

	bool UnRegisterClass(ClassTypeID id)
	{
		map<ClassTypeID, ObjectCreator>::iterator iter = m_ObjectCreatorMap.find(id);

		if(iter == m_ObjectCreatorMap.end())
			return false;

		m_ObjectCreatorMap.erase(iter);

		return true;
	}

	BaseClassType* CreateObject(ClassTypeID id)
	{
		map<ClassTypeID, ObjectCreator>::iterator iter = m_ObjectCreatorMap.find(id);

		if(iter == m_ObjectCreatorMap.end())
			return NULL; 

		return (*iter).second();
	}

	void ShutdownObjectFactory(void) { m_ObjectCreatorMap.clear(); }
	
};

template<typename ClassTypeID, typename BaseClassType>
CObjectFactory<ClassTypeID, BaseClassType>
	CObjectFactory<ClassTypeID, BaseClassType>::m_pInstance;
#endif