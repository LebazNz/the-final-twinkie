#ifndef TILE_H
#define TILE_H
#include <Windows.h>


#include "../Event and Messages/IListener.h"

class CTile : public IListener
{
	int m_nPosX;
	int m_nPosY;
	int m_nWidth;
	int m_nHeight;
	int m_nIndex;
	RECT m_rCollRect;
	bool m_bHasCollision;
	int m_bHasSpawn;
    int m_bHasTrigger;
public:
	CTile(void);
	~CTile(void);

	void CreateTile(int index, int nPosY, int nPosX, int width, int height, bool bHasCollision = false, 
	int bHasSpawn = 0, int nHasTrigger = 0);
	
	//Getters
	int GetPosX(void) { return m_nPosX; }
	int GetPosY(void) { return m_nPosY; }
	int GetWidth(void) { return m_nWidth;}
	int GetHeight(void) { return m_nHeight;}
	int GetIndex(void) { return m_nIndex;}
	RECT GetRect(void);

	void SetCollision(bool c) { m_bHasCollision = c;}
	bool GetCollision(void) { return m_bHasCollision; }
	int GetSpawn(void) { return m_bHasSpawn; }
	int GetTrigger(void) { return m_bHasTrigger; }
	void ClearTrigger(void) { m_bHasTrigger = 0;}
	 void HandleEvent(CEvent *pEvent);
	

};

#endif