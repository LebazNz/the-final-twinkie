#include "Entity.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../World and Tile/TileManager.h"
#include "../Headers/Camera.h"

CEntity::CEntity(void)
{
	// Position
	m_fPosX = 0;
	m_fPosY = 0;
	// Velocity
	m_fVelX = 0;
	m_fVelY = 0;
	// Size
	m_nWidth = 1;
	m_nHeight = 1;
	// Image
	m_nImageID = -1;
	m_nColor = D3DCOLOR_XRGB(255,255,255);
	// Health
	m_fHealth = 0;
	m_fMaxHealth = 0;	
	// Reference Counter
	m_nRefCount = 1;	
	// Object Type
	m_nType = OBJ_BASE;

	m_pTM = CTileManager::GetInstance();
}

CEntity::~CEntity(void)
{
}

void CEntity::Update(float fDt)
{
	m_v2OldPos.fX = GetPosX();
	m_v2OldPos.fY = GetPosY();
	m_fPosX += int(m_fVelX * fDt);
	m_fPosY += int(m_fVelY * fDt);
}

void CEntity::Render(void)
{
	if(m_nImageID != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, (int)m_fPosX, (int)m_fPosY, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, DWORD(m_nColor)); 
	}
}

bool CEntity::CheckCollision(IEntity* pObject)
{
	RECT rOverLap = {}, rSelf = GetRect(), rOther = pObject->GetRect();

	m_pTM->CheckCollision(pObject);

	BOOL bIsColliding = IntersectRect(&rOverLap, &rSelf, & rOther);

	if(bIsColliding == TRUE)
		return true;
	else
		return false;
}

RECT CEntity::GetRect(void)
{
	Camera* C=Camera::GetInstance();
	RECT rSelf = { };
	SetRect(&rSelf, (int)(m_fPosX+C->GetPosX())-m_nWidth/2, (int)(m_fPosY+C->GetPosY())-m_nHeight/2, (int)(m_fPosX+C->GetPosX())+m_nWidth/2, (int)(m_fPosY+C->GetPosY())+m_nHeight/2);
	return rSelf;
}

void CEntity::AddRef(void)
{
	m_nRefCount++;
}

void CEntity::Release(void)
{
	m_nRefCount--;

	if(m_nRefCount == 0)
		delete this;
}

void CEntity::TakeDamage(int nDamage)
{
	m_fHealth -= nDamage;
}
