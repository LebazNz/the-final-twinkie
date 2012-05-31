#ifndef COBJECTMANAGER_H_
#define COBJECTMANAGER_H_

class IEntity;
#include <vector>
using std::vector;
class CTileManager;
class CObjectManager
{
public:
	static CObjectManager* GetInstance(void);
	static void DeleteInstance(void);
	void UpdateAllObjects(float fDt);
	void AddObject(IEntity* pObject);
	void RemoveObject(IEntity* pObject);
	void RemoveAllObjects(void);
	void CheckCollisions(void);
	void RenderAllObjects(void);

	void AreaEffect(int x, int y, int radius, int damage, bool arc = false);

private:
	CObjectManager(void);
	CObjectManager(const CObjectManager&);
	CObjectManager& operator=(const CObjectManager&);
	~CObjectManager(void);

	static CObjectManager* m_pInstance;
	vector<IEntity*>	m_vObjectList;

	CTileManager*	m_pTile;
};

#endif