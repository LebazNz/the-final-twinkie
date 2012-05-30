#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include "../GameObjects/Entity.h"
#include "Layer.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include <string>
using std::string;


class CTileManager
{
	CLayer m_pGraphics;
	static CTileManager*	m_pSelf;
	int m_nTileImageID;
	CSGD_TextureManager* m_pTM;
	vector<ENEMY_INFO> m_vEnemies;
	vector<vector<CTile>> m_vTiles;
	vector<CTile*> wallTiles;

	void RaiseWall(void);
	void CreateObjects(void);
	
	CTileManager(void);
	CTileManager(const CTileManager&);
	CTileManager& operator=(const CTileManager&);
	virtual ~CTileManager(void);
public:
	
	static CTileManager* GetInstance(void);
	static void DeleteInstance(void);
	
	bool Load(string fileName);
	void Unload(void);
	void Render(void);
	void CheckCollision(IEntity* pBase);
	

	// Getters
	//vector<ENEMY_INFO> GetEnemyInfo(void); // You can only call this once after that the data will be gone
	//vector<ENEMY_INFO> GetSpawnInfo(void); 

};
#endif
