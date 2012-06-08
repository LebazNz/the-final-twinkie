#include "TileManager.h"
#include <vector>
using namespace std;
#include "Tile.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"
#include "../Event and Messages/DestroyBulletMessage.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/EventSystem.h"

#include "../GameStates/GamePlayState.h"
#include "../GameStates/TutorState.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/Bullet.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Player.h"
#include "../Headers/Camera.h"
#include "../GameStates/GamePlayState.h"
#include "../Headers/Game.h"
#include "../GameObjects/PirateBoss.h"
#include "../Event and Messages/CreateBoss.h"


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
	raised = false;
	//m_pGraphics.CreateLayer(0,0,0,0,0,0,0,tiles);
}


CTileManager::~CTileManager(void)
{
	m_pGraphics.EmptyLayer();
}


bool CTileManager::Load(string fileName)
{
	raised = false;
	
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

		int mapWidth, mapHeight, tileWidth, tileHeight, setWidth,setHeight, playerPosX, playerPosY;

			// Read the attributes (within the XML tag)
		if( pChild->Attribute( "playerx", &playerPosX ) == nullptr )
			playerPosX = 0;

		//CPlayer *pPlayer = 
		CPlayer* player = CPlayer::GetInstance();
	
		
		//player->SetPosX(playerPosX);
		Camera::GetInstance()->SetPosX(float((CGame::GetInstance()->GetWidth()/2) - playerPosX));

		if( pChild->Attribute( "playery", &playerPosY ) == nullptr )
			playerPosY = 0;

		
		//player->SetPosY(playerPosY);
		Camera::GetInstance()->SetPosY(float((CGame::GetInstance()->GetHeight()/2) - playerPosY));

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
		m_vTiles = vTiles;

		struct tempTile
		{
			int posY, posX, bSpawn,index,bTrigger;
			bool bCollision;
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
				

				if( pBaby->Attribute( "trigger", &tile.bTrigger ) == nullptr )
					tile.bTrigger = 0;
				
				
				m_vTiles[i][j].CreateTile(tile.index,tile.posY, tile.posX,tileWidth,tileHeight, tile.bCollision, tile.bSpawn, tile.bTrigger);
				if(m_vTiles[i][j].GetTrigger() == 2)
					wallTiles.push_back(&m_vTiles[i][j]);
				j++;
				pBaby = pBaby->NextSiblingElement();
			}

			i++;
			j = 0;
			pChild = pChild->NextSiblingElement("tile_row");
			
		}
		/*pChild = pRoot->FirstChildElement("file_name")->NextSiblingElement("enemy_row");

		
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

		}*/
	
		

		m_pGraphics.CreateLayer(GRAPHIC,tileWidth, tileHeight, mapWidth, mapHeight, setWidth,setHeight, m_vTiles);
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
	Camera* cam = Camera::GetInstance();
	CGame* pGame = CGame::GetInstance();

	if(m_vTiles.size() == 0 || pBase == nullptr)
		return;
	
	int height = m_pGraphics.GetMapHeight();
	int width = m_pGraphics.GetMapWidth();

	

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			int x = m_vTiles[i][j].GetPosX();
			int y = m_vTiles[i][j].GetPosY();
			
			int width = m_vTiles[i][j].GetWidth(), height = m_vTiles[i][j].GetHeight();
			
			//if(x >= -width && x <= pGame->GetWidth()+width && y >= -height && y <=  pGame->GetHeight()+height)
				//continue;
			

			if(m_vTiles[i][j].GetCollision() == false)
				continue;

			x = (int)(x+cam->GetPosX());
			y = (int)(y+cam->GetPosY());

			CEntity* pTarget =dynamic_cast<CEntity*>(pBase);
	
			RECT rOverLap = {}, rSelf = m_vTiles[i][j].GetRect(), rOther = pTarget->GetRect();

			float xPos = ((pTarget->GetPosX()+cam->GetPosX()) - ((m_vTiles[i][j].GetPosX()+cam->GetPosX())+m_vTiles[i][j].GetWidth()/2));
			float yPos = ((pTarget->GetPosY()+cam->GetPosY()) - ((m_vTiles[i][j].GetPosY()+cam->GetPosY())+m_vTiles[i][j].GetHeight()/2));
			xPos *= xPos;
			yPos *= yPos;

			float distance = sqrt(xPos+yPos);

			if(distance > 150 &&  pBase->GetType() != OBJ_PLAYER)
				continue;

			BOOL bIsColliding = IntersectRect(&rOverLap, &rSelf, &rOther);

			if(bIsColliding == TRUE)
			{
				switch(pBase->GetType())
				{
				case OBJ_BASE:
					break;
				case OBJ_PLAYER:
					{
						if(m_vTiles[i][j].GetTrigger() == 1)
						{
							RaiseWall();
							

							if(CGame::GetInstance()->isTutor == true)
								CTutorState::GetInstance()->IncrementBox();

							m_vTiles[i][j].SetCollision(false);
							break;
						}

						Camera *cam = Camera::GetInstance();
						CPlayer* pPlayer = dynamic_cast<CPlayer*>(pBase);

						//pPlayer->SetPosX(pPlayer->GetOldPos().fX);
						//pPlayer->SetPosY(pPlayer->GetOldPos().fY);
						cam->SetPosX(cam->GetOldPos().fX);
						cam->SetPosY(cam->GetOldPos().fY);
					
					}
					break;
				case OBJ_BULLET:
					{
						if(m_vTiles[i][j].GetTrigger() == 1)
						{
							break;
						}

						CBullet* pBullet =dynamic_cast<CBullet*>(pBase);
						

						CDestroyBulletMessage* pMsg = new CDestroyBulletMessage(pBullet);
						CMessageSystem::GetInstance()->SndMessage(pMsg);
						pMsg = nullptr;
					}
					break;
				case OBJ_ENEMY:
					{
						if(m_vTiles[i][j].GetTrigger() == 1)
						{
							break;
						}

						CEnemy* pEnemy =dynamic_cast<CEnemy*>(pBase);
						// USE THIS TO TEST DISTANCE FORMULA int blah = distance;
						pEnemy->SetPosX(pEnemy->GetOldPos().fX);
						pEnemy->SetPosY(pEnemy->GetOldPos().fY);
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
//vector<ENEMY_INFO> CTileManager::GetEnemyInfo(void)
//{
//	if(m_vEnemies.size() > 0)
//	{
//		vector<ENEMY_INFO> tempvec;
//		tempvec = m_vEnemies;
//		m_vEnemies.clear();
//		return tempvec;
//	}
//	return m_vEnemies;
//}
//
//vector<ENEMY_INFO> CTileManager::GetSpawnInfo(void)
//{
//	return m_pGraphics.GetSpawns();
//}

void CTileManager::RaiseWall(void)
{
	if(raised == true)
		return;
	else
		raised = true;

	int size = wallTiles.size();

	for(int i = 0; i < size; i++)
	{
		CEventSystem::GetInstance()->SendEvent("wall_raise",wallTiles[i]);
	}

	CCreateBoss* pMsg = new CCreateBoss(PIRATE,0,0);
	CMessageSystem::GetInstance()->SndMessage(pMsg);
	pMsg = nullptr;

}