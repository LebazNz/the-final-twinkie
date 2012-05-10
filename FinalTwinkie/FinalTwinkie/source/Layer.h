#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "Tile.h"
class CLayer
{
	int m_nHeight;
	int m_nWidth;
	std::vector<CTile*> m_vTiles;
	int m_nType;
public:
	CLayer(void);
	~CLayer(void);
	
	void CreateLayer(int nType, int nHeight, int nWidth);

};

#endif