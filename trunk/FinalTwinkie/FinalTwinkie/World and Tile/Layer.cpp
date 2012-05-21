#include "Layer.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"

CLayer::CLayer(void)
{
}


CLayer::~CLayer(void)
{
}

void CLayer::CreateLayer(int nType, int tHeight, int tWidth, int mapWidth, int mapHeight,int tileSetWidth, int tileSetHeight, vector<vector<CTile>> vTiles)
{
	m_eType = nType;
	m_nMapWidth = mapWidth;
	m_nMapHeight = mapHeight;
	m_nTileWidth = tWidth;
	m_nTileHeight = tHeight;
	m_nTileSetWidth = tileSetWidth;
	m_nTileSetHeight = tileSetHeight;
	m_vTiles = vTiles;

	Fill();
}

void CLayer::RenderLayer(int imageID)
{
	CSGD_TextureManager *m_pTM = CSGD_TextureManager::GetInstance();
	Camera* cam = Camera::GetInstance();

	for(int i = 0; i < m_nMapHeight; i++)
	{
		
		for(int j = 0; j < m_nMapWidth; j++)
		{
			
			int x = m_vTiles[i][j].GetPosX();
			int y = m_vTiles[i][j].GetPosY();
			int index = m_vTiles[i][j].GetIndex();
			RECT src = {};
			src = CellAlgorithm(index);
			
			m_pTM->Draw(imageID,x+cam->GetPosX(),y+cam->GetPosY(),1.0f,1.0f,&src);

			if(m_vTiles[i][j].GetCollision() == true)
			{
			CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			CSGD_Direct3D::GetInstance()->DrawRect(m_vTiles[i][j].GetRect(),255,0,0);
			}
		}
	}

}

RECT CLayer::CellAlgorithm(int id)
{
	RECT rCell;

	rCell.left	= (id % m_nTileSetWidth) * m_nTileWidth;
	rCell.top	= (id / m_nTileSetWidth) * m_nTileHeight;

	rCell.right	= rCell.left + m_nTileWidth;
	rCell.bottom = rCell.top + m_nTileHeight;

	return rCell;
}

void CLayer::EmptyLayer(void)
{

	m_eType = -1;
	m_nMapWidth = 0;
	m_nMapHeight = 0;
	m_nTileWidth = 0;
	m_nTileHeight = 0;
	m_nTileSetWidth = 0;
	m_nTileSetHeight = 0;
	m_vTiles.clear();
	m_vSpawns.clear();

}

vector<ENEMY_INFO> CLayer::GetSpawns(void)
{
	if(m_vSpawns.size() > 0)
	{
		vector<ENEMY_INFO> tempvec;
		tempvec = m_vSpawns;
		m_vSpawns.clear();
		return tempvec;
	}
	
	return m_vSpawns;
}


void CLayer::Fill(void)
{
	for(int i = 0; i < m_nMapHeight; i++)
	{
		for(int j = 0; j < m_nMapWidth; j++)
		{
			
			if(m_vTiles[i][j].GetSpawn() > 0)
			{
				ENEMY_INFO spawn = {};

				spawn.m_nPosX = m_vTiles[i][j].GetPosX();
				spawn.m_nPosY =	m_vTiles[i][j].GetPosY();
				spawn.m_nType = m_vTiles[i][j].GetSpawn();

				m_vSpawns.push_back(spawn);
			}

		}
	}



}