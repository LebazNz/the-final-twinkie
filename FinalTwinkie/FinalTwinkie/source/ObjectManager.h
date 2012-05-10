#ifndef COBJECTMANAGER_H_
#define COBJECTMANAGER_H_

class IEntity;
#include <vector>
using std::vector;

class CObjectManager
{
public:
	static CObjectManager* GetInstance(void);
	static void DeleteInstance(void);
	void UpdateAllObjects(float fDt);
	void AddObjects(IEntity* pObjects);
	void RemoveObject(IEntity* pObject);
	void RemoveAllObjects(void);
	void CheckCollisions(void);
private:
	CObjectManager(void);
	CObjectManager(const CObjectManager&);
	CObjectManager& operator=(const CObjectManager&);
	~CObjectManager(void);

	static CObjectManager* m_pInstance;
	vector<IEntity*>	m_vObjectList;
};

#endif