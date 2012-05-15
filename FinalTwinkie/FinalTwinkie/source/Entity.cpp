#include "Entity.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CEntity::CEntity(void)
{
	// Position
	m_nPosX = 0;
	m_nPosY = 0;
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
}

CEntity::~CEntity(void)
{
}

void CEntity::Update(float fDt)
{
	m_nPosX += int(m_fVelX * fDt);
	m_nPosY += int(m_fVelY * fDt);
}

void CEntity::Render(void)
{
	if(m_nImageID != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, m_nPosX, m_nPosY, 1.0f, 1.0f, nullptr, 0.0f, 0.0f, 0.0f, DWORD(m_nColor)); 
	}
}

bool CEntity::CheckCollision(IEntity* pObject)
{
	RECT rOverLap = {}, rSelf = GetRect(), rOther = pObject->GetRect();

	BOOL bIsColliding = IntersectRect(&rOverLap, &rSelf, & rOther);

	if(bIsColliding == TRUE)
		return true;
	else
		return false;
}

RECT CEntity::GetRect(void)const
{
	RECT rSelf = { };
	SetRect(&rSelf, m_nPosX, m_nPosY, m_nPosX+m_nWidth, m_nPosY+m_nHeight);
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
