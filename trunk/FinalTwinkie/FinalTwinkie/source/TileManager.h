#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include "Entity.h"
#include "Layer.h"
class CTileManager
{
	CLayer* m_pGraphics;
	CLayer* m_pPassibility;
	CLayer* m_pData;
public:
	CTileManager(void);
	~CTileManager(void);

	void Load();
	void Update();
	void Unload();
	void Render();
	void CheckCollision(IEntity* pBase);

};
#endif
