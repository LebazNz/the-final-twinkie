#ifndef LAYER_H
#define LAYER_H

#include <vector>
using std::vector;
#include "Tile.h"
#include <Windows.h>

struct ENEMY_INFO
{
	int m_nPosX;
	int m_nPosY;
	int m_nType;
};

enum LAYER_TYPE { GRAPHIC, COLLISION, DATA, EMPTY };
class CLayer
{
	int m_nMapWidth;
	int m_nMapHeight;
	int m_nTileWidth;
	int m_nTileHeight;
	int m_nTileSetWidth;
	int m_nTileSetHeight;
	vector<vector<CTile>> m_vTiles;
	vector<ENEMY_INFO> m_vSpawns;
	
	int m_eType;

	RECT CellAlgorithm(int id);
	void Fill(void);   // this fills the collision and spawn vectors

public:
	CLayer(void);
	~CLayer(void);
	
	void CreateLayer(int nType, int tHeight, int tWidth, int mapWidth, int mapHeight,int tileSetWidth, int tileSetHeight, vector<vector<CTile>> vTiles);
	void RenderLayer(int imageID);	
	void EmptyLayer(void);
	
	//Setters
	void SetType(int type) { m_eType = type;}

	//Getters
	int GetType(void) { return m_eType;}
	int GetMapWidth(void) { return m_nMapWidth;}
	int GetMapHeight(void) { return m_nMapHeight;}
	int GetTileWidth(void) { return m_nTileWidth;}
	int GetTileHeight(void) { return m_nTileHeight;}
	void SetTiles(vector<vector<CTile>> tiles) { m_vTiles = tiles;}
	vector<vector<CTile>> GetTiles(void) {return m_vTiles;}
	vector<ENEMY_INFO> GetSpawns(void);
};

#endif