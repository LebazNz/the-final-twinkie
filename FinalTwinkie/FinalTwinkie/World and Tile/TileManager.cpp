#include "TileManager.h"
#include <vector>
using namespace std;
#include "Tile.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "../Event and Messages/DestroyBulletMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../GameStates/GamePlayState.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Bullet.h"


CTileManager* CTileManager::m_pSelf = nullptr;

CTileManager* CTileManager::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CTileManager;
	return m_pSelf;
}
void CTileManager::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}


CTileManager::CTileManager(void)
{
	m_pTM = CSGD_TextureManager::GetInstance();
	m_nTileImageID = -1;
	vector<vector<CTile>> tiles;
	m_pGraphics.CreateLayer(0,0,0,0,0,0,0,tiles);
}


CTileManager::~CTileManager(void)
{
}


bool CTileManager::Load(string fileName)
{
	
	
	TiXmlDocument doc(fileName.c_str());
	if(doc.LoadFile())
	{
	
		// Access the root node (graphic_layer) in the document
		TiXmlElement* pRoot = doc.RootElement();
		if( pRoot == nullptr )
			return false;

		//Get file name and map info
		const char* pText = pRoot->FirstChildElement("file_name")->GetText();
		string picture="resource/graphics/";

		if(pText != nullptr)
		{
			picture += pText;
			TCHAR buffer[100];
			mbstowcs_s(nullptr,buffer, 100, picture.c_str(), _TRUNCATE);
			m_nTileImageID = CSGD_TextureManager::GetInstance()->LoadTexture(buffer);
		}


		// Iterate through the root's children nodes (map_info)
		TiXmlElement* pChild = pRoot->FirstChildElement();
		pChild = pChild->NextSiblingElement("map_info");

		int mapWidth, mapHeight, tileWidth, tileHeight, setWidth,setHeight;

			// Read the attributes (within the XML tag)
		if( pChild->Attribute( "mapwidth", &mapWidth ) == nullptr )
			mapWidth = 1;

		if( pChild->Attribute( "mapheight", &mapHeight ) == nullptr )
			mapHeight = 1;

		if( pChild->Attribute( "tilewidth", &tileWidth ) == nullptr )
			tileWidth = 1;

		if( pChild->Attribute( "tileheight", &tileHeight ) == nullptr )
			tileHeight = 1;

		if( pChild->Attribute( "setwidth", &setWidth ) == nullptr )
			setWidth = 1;

		if( pChild->Attribute( "setheight", &setHeight ) == nullptr )
			setHeight = 1;

		pChild = pChild->NextSiblingElement("tile_row");
		TiXmlElement* pBaby;

		vector<vector<CTile>> vTiles (mapHeight , vector<CTile> (mapWidth) );

		struct tempTile
		{
			int posY, posX, bSpawn,index;
			bool bCollision, bTrigger;
		};

		int i = 0, j = 0;
		while(pChild != nullptr)
		{
			pBaby = pChild->FirstChildElement("tile_info");
			while(pBaby != nullptr)
			{
				
				tempTile tile;

				if( pBaby->Attribute( "index", &tile.index ) == nullptr )
					tile.index = -1;

				if( pBaby->Attribute( "posy", &tile.posY ) == nullptr )
					tile.posY = 0;


				if( pBaby->Attribute( "posx", &tile.posX ) == nullptr )
					tile.posX = 0;

				int b;

				if( pBaby->Attribute( "collision", &b ) == nullptr )
					b = 1;
				if(b == 1)
					tile.bCollision = true;
				else
					tile.bCollision = false;

				if( pBaby->Attribute( "spawn", &tile.bSpawn ) == nullptr )
					tile.bSpawn = 0;
				

				if( pBaby->Attribute( "trigger", &b ) == nullptr )
					b = 1;
				if(b == 1)
					tile.bTrigger = true;
				else
					tile.bTrigger = false;

				vTiles[i][j].CreateTile(tile.index,tile.posY, tile.posX,tileWidth,tileHeight, tile.bCollision, tile.bSpawn, tile.bTrigger);
				j++;
				pBaby = pBaby->NextSiblingElement();
			}

			i++;
			j = 0;
			pChild = pChild->NextSiblingElement("tile_row");
			
		}

		pChild = pRoot->FirstChildElement("file_name")->NextSiblingElement("enemy_row");

		
		if(pChild != nullptr)
		{
			TiXmlElement* pEnemy = pChild->FirstChildElement( "enemy_spawn" );
			while(pEnemy != nullptr)
			{
				ENEMY_INFO spawn = {};

				if( pEnemy->Attribute( "posx", &spawn.m_nPosX ) == nullptr )
					spawn.m_nPosX = -1;

				if( pEnemy->Attribute( "posy", &spawn.m_nPosY ) == nullptr )
					spawn.m_nPosY = -1;

				if( pEnemy->Attribute( "type", &spawn.m_nType ) == nullptr )
					spawn.m_nType = -1;
				
				m_vEnemies.push_back(spawn);

				pEnemy = pEnemy->NextSiblingElement("enemy_spawn");
			}

		}
	
		m_pGraphics.CreateLayer(GRAPHIC,tileWidth, tileHeight, mapWidth, mapHeight, setWidth,setHeight, vTiles);
	}
	else
	{
		// Failed.
		TCHAR szBuffer[256] = {0};
		_stprintf_s(szBuffer, _countof( szBuffer ), _T("Failed to Create XML File - %s"), fileName); 
		MessageBox(0, szBuffer, _T("TileManager Error"), MB_OK);
		return false;	
	}
		
	return true;
}

void CTileManager::Unload()
{
	m_pGraphics.EmptyLayer();
	m_vEnemies.clear();
}
void CTileManager::Render()
{
	m_pGraphics.RenderLayer(m_nTileImageID);
}
void CTileManager::CheckCollision(IEntity* pBase)
{
	
	int height = m_pGraphics.GetMapHeight();
	int width = m_pGraphics.GetMapWidth();

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(m_vTiles[i][j].GetCollision() == false)
				continue;

			RECT rOverLap = {}, rSelf = m_vTiles[i][j].GetRect(), rOther = pBase->GetRect();

			CEntity* m_pTarget =dynamic_cast<CEntity*>(pBase);


		int xPos = m_vTiles[i][j].GetPosX() - m_pTarget->GetPosX();
		int yPos = m_vTiles[i][j].GetPosY() - m_pTarget->GetPosY();
		xPos *= xPos;
		yPos *= yPos;

		float distance = sqrt(float(xPos+yPos));

		if(distance > (m_vTiles[i][j].GetWidth() + 5) || distance > (m_vTiles[i][j].GetHeight() + 5))
			continue;

			BOOL bIsColliding = IntersectRect(&rOverLap, &rSelf, & rOther);

		if(bIsColliding == TRUE)
		{
			//TRUE
			switch(pBase->GetType())
			{
			case OBJ_BASE:
				break;
			case OBJ_PLAYER:
				{
				
					CEntity* pPlayer =dynamic_cast<CEntity*>(pBase);
					int rightSide = pPlayer->GetPosX() - pPlayer->GetHeight()/2;
					int leftSide = pPlayer->GetPosX() + pPlayer->GetHeight()/2;
					int topSide = pPlayer->GetPosY() - pPlayer->GetHeight()/2;
					int botSide = pPlayer->GetPosY() + pPlayer->GetHeight()/2;
					int halfHeight = pPlayer->GetHeight()/2;


					if(leftSide > rSelf.left)
					{
						pPlayer->SetPosX(rSelf.left - halfHeight);
					}
					else if(rightSide < rSelf.right)
					{
						pPlayer->SetPosX(rSelf.right + halfHeight);
					}
					else if(topSide < rSelf.top)
					{
						pPlayer->SetPosY(rSelf.top - halfHeight);
					}
					else if(botSide > rSelf.bottom)
					{
						pPlayer->SetPosY(rSelf.bottom + halfHeight);
					}
				}
				break;
			case OBJ_BULLET:
				{
					CBullet* pBullet = dynamic_cast<CBullet*>(pBase);
					CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(pBullet);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;
			case OBJ_ENEMY:
				{
					CEntity* pEnemy =dynamic_cast<CEntity*>(pBase);
					int rightSide = pEnemy->GetPosX() - pEnemy->GetHeight()/2;
					int leftSide = pEnemy->GetPosX() + pEnemy->GetHeight()/2;
					int topSide = pEnemy->GetPosY() - pEnemy->GetHeight()/2;
					int botSide = pEnemy->GetPosY() + pEnemy->GetHeight()/2;
					int halfHeight = pEnemy->GetHeight()/2;


					if(leftSide > rSelf.left)
					{
						pEnemy->SetPosX(rSelf.left - halfHeight);
					}
					else if(rightSide < rSelf.right)
					{
						pEnemy->SetPosX(rSelf.right + halfHeight);
					}
					else if(topSide < rSelf.top)
					{
						pEnemy->SetPosY(rSelf.top - halfHeight);
					}
					else if(botSide > rSelf.bottom)
					{
						pEnemy->SetPosY(rSelf.bottom + halfHeight);
					}
				}
				break;
			}

		}

		}

	}
}

/*
	If m_vEnemies has info in it,then after this method it will be empty
	in order to free up as much as i can out of the tile manager while a level is running.
*/
vector<ENEMY_INFO> CTileManager::GetEnemyInfo(void)
{
	if(m_vEnemies.size() > 0)
	{
		vector<ENEMY_INFO> tempvec;
		tempvec = m_vEnemies;
		m_vEnemies.clear();
		return tempvec;
	}
	return m_vEnemies;
}

vector<ENEMY_INFO> CTileManager::GetSpawnInfo(void)
{
	return m_pGraphics.GetSpawns();
}