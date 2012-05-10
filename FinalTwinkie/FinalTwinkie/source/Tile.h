#ifndef TILE_H
#define TILE_H

class CTile
{
	int m_nPosX;
	int m_nPosY;
	bool m_bHasCollision;
	bool m_bHasSpawn;
    bool m_bHasTrigger;
public:
	CTile(void);
	~CTile(void);

	void CreateTile(int nPosX, int nPosY, bool bHasCollision, 
		bool bHasSpawn, bool bHasTrigger);
};

#endif