#ifndef TILE_H
#define TILE_H
#include <Windows.h>

class CTile
{
	int m_nPosX;
	int m_nPosY;
	int m_nWidth;
	int m_nHeight;
	int m_nIndex;
	RECT m_rCollRect;
	bool m_bHasCollision;
	int m_bHasSpawn;
    bool m_bHasTrigger;
public:
	CTile(void);
	~CTile(void);

	void CreateTile(int index, int nPosY, int nPosX, int width, int height, bool bHasCollision = false, 
	int bHasSpawn = 0, bool bHasTrigger = false);
	
	//Getters
	int GetPosX(void) { return m_nPosX; }
	int GetPosY(void) { return m_nPosY; }
	int GetWidth(void) { return m_nWidth;}
	int GetHeight(void) { return m_nHeight;}
	int GetIndex(void) { return m_nIndex;}
	RECT GetRect(void) { return m_rCollRect;}

	bool GetCollision(void) { return m_bHasCollision; }
	int GetSpawn(void) { return m_bHasSpawn; }
	bool GetTrigger(void) { return m_bHasTrigger; }
	

};

#endif