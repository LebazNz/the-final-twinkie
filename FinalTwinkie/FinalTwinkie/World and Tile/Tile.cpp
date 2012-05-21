#include "Tile.h"

#include "../Headers/Camera.h"

CTile::CTile(void)
{
	CEventSystem::GetInstance()->RegisterClient("arena",this);
	 m_nPosX = -1;
	 m_nPosY = -1;
	 m_bHasCollision = false;
	 m_bHasSpawn = 0;
     m_bHasTrigger = false;
	 m_nIndex = -1;
	 m_nWidth = -1;
	 m_nHeight = -1;
}


CTile::~CTile(void)
{
	//CEventSystem::GetInstance()->UnregisterClient("arena",this);
}

void CTile::CreateTile( int index,int nPosY,int nPosX, int width, int height, bool bHasCollision, int bHasSpawn, int bHasTrigger )
{
	m_nIndex = index;
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = width;
	m_nHeight = height;
	m_bHasCollision = bHasCollision;
	m_bHasSpawn = bHasSpawn;
    m_bHasTrigger = bHasTrigger;

	m_rCollRect.top = nPosY;
	m_rCollRect.left = nPosX;
	m_rCollRect.bottom = nPosY + height;
	m_rCollRect.right = nPosX + width;
}

RECT CTile::GetRect(void)
{
	Camera *cam = Camera::GetInstance();

	m_rCollRect.top = long(m_nPosY + cam->GetPosY());
	m_rCollRect.left = long(m_nPosX + cam->GetPosX());
	m_rCollRect.bottom = long((m_nPosY+ cam->GetPosY()) + m_nHeight);
	m_rCollRect.right = long((m_nPosX+ cam->GetPosX()) + m_nWidth);

	return m_rCollRect;
}

void CTile::HandleEvent(CEvent* pEvent)
{
	if(GetTrigger() == 1)
		return;

	if(pEvent->GetParam() != this)
		return;

	if(pEvent->GetEventID() == "arena")
	{
		SetCollision(true);
	}

}