#include "Layer.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../GameObjects/Enemy.h"
#include "../Event and Messages/CreateBuildingMessage.h"
#include "../Event and Messages/CreateEnemyMessage.h"
#include "../Event and Messages/CreateMineMessage.h"
#include "../Event and Messages/MessageSystem.h"
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
	CGame *pGame = CGame::GetInstance();

	for(int i = 0; i < m_nMapHeight; i++)
	{
		
		for(int j = 0; j < m_nMapWidth; j++)
		{
			
			float x = m_vTiles[i][j].GetPosX()+cam->GetPosX();
			float y = m_vTiles[i][j].GetPosY()+cam->GetPosY();
			int index = m_vTiles[i][j].GetIndex();
			RECT src = {};
			src = CellAlgorithm(index);
			
			if(x >= -10 && x <= pGame->GetWidth() && y >= -10 && y <=  pGame->GetHeight())
				m_pTM->Draw(imageID,m_vTiles[i][j].GetPosX()+(int)cam->GetPosX(),m_vTiles[i][j].GetPosY()+(int)cam->GetPosY(),1.0f,1.0f,&src);
			else
				continue;

			//if(m_vTiles[i][j].GetCollision() == true)
			//{
			//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
			//CSGD_Direct3D::GetInstance()->DrawRect(m_vTiles[i][j].GetRect(),255,0,0);
			//}
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


void CLayer::Fill(void)
{
	for(int i = 0; i < m_nMapHeight; i++)
	{
		for(int j = 0; j < m_nMapWidth; j++)
		{
			float x = (float)m_vTiles[i][j].GetPosX();
			float y = (float)m_vTiles[i][j].GetPosY();

			switch(m_vTiles[i][j].GetSpawn())
			{
			case 0:
				{
					/*   This is an empty tile */
				}
				break;

			case 1:
				{
					/*  SBASE   */
					CCreateBuildingMessage* pMsg = new CCreateBuildingMessage(MSG_CREATEBUILDING,SAPPER,x,y,true,1.5f);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;

				}
				break;
			case 2:
				{
					/*  TBASE   */
					CCreateBuildingMessage* pMsg = new CCreateBuildingMessage(MSG_CREATEBUILDING,TANK,x,y,true,1.5f);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;
			case 3:
				{
					/*  BARRICADE   */
				}
				break;
			case 4:
				{
					/*  BUILDING   */
					CCreateBuildingMessage* pMsg = new CCreateBuildingMessage(MSG_CREATEBUILDING,0,x,y,false,0.0f);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;
			case 5:
				{
					/*  SAPPER   */
					CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,SAPPER,x,y);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;
			case 6:
				{
					/*  ROCKET   */
				}
				break;
			case 7:
				{
					/*  RIFLE   */
				}
				break;
			case 8:
				{
					/*  TANK   */
					CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,TANK,x,y);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;
			case 9:
				{
					/*  TURRET   */
					CCreateEnemyMessage* pMsg = new CCreateEnemyMessage(MSG_CREATEENEMY,TURRET,x,y);
					CMessageSystem::GetInstance()->SndMessage(pMsg);
					pMsg = nullptr;
				}
				break;


			case 11:
				{
					/*  GEVENT   */
				}
				break;

			case 12:
				{
					/*  SEVENT   */
				}
				break;

			case 13:
				{
					/*  MINE   */
				}
				break;

			case 14:
				{
					/*  TREE   */
				}
				break;

			default:
				{
				}
				break;



			}
			/*if(m_vTiles[i][j].GetSpawn() > 0)
			{
				ENEMY_INFO spawn = {};

				spawn.m_nPosX = m_vTiles[i][j].GetPosX();
				spawn.m_nPosY =	m_vTiles[i][j].GetPosY();
				spawn.m_nType = m_vTiles[i][j].GetSpawn();

				m_vSpawns.push_back(spawn);
			}*/

		}
	}



}