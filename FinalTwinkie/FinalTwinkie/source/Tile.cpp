#include "Tile.h"


CTile::CTile(void)
{
	 m_nPosX = -1;
	 m_nPosY = -1;
	 m_bHasCollision = false;
	 m_bHasSpawn = 0;
     m_bHasTrigger = false;
	 m_nIndex = -1;
}


CTile::~CTile(void)
{
}

void CTile::CreateTile( int index,int nPosY,int nPosX, int width, int height, bool bHasCollision, int bHasSpawn, bool bHasTrigger )
{
	m_nIndex = index;
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_bHasCollision = bHasCollision;
	m_bHasSpawn = bHasSpawn;
    m_bHasTrigger = bHasTrigger;

	m_rCollRect.top = nPosY;
	m_rCollRect.left = nPosX;
	m_rCollRect.bottom = nPosY + height;
	m_rCollRect.right = nPosX = width;
}
