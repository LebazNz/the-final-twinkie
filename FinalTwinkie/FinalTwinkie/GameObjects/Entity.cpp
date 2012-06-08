#include "Entity.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../World and Tile/TileManager.h"
#include "../Headers/Camera.h"
//#include "../SGD Wrappers/CSGD_Direct3D.h"

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
	// Armor
	m_fArmor = 0;
	m_fMaxArmor = 0;
	// Reference Counter
	m_nRefCount = 1;	
	// Object Type
	m_nType = OBJ_BASE;

	m_pTM = CTileManager::GetInstance();

	m_bInvul = false;
	m_fInvulTimer = 0.0f;

	m_fStopTimer = 0.0f;
	m_bStop = false;
}

CEntity::~CEntity(void)
{
}

void CEntity::Update(float fDt)
{
	m_v2OldPos.fX = GetPosX();
	m_v2OldPos.fY = GetPosY();
	m_fPosX += m_fVelX * fDt;
	m_fPosY += m_fVelY * fDt;
}

void CEntity::Render(void)
{
	Camera* C = Camera::GetInstance();
	if(m_nImageID != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+C->GetPosX()), (int)(GetPosY()-GetHeight()/2+C->GetPosY()), 1.0f, 1.0f, 0, (float)GetWidth()/2, (float)GetHeight()/2);
	}
}

bool CEntity::CheckCollision(IEntity* pObject)
{
	RECT rOverLap = {}, rSelf = GetRect(), rOther = pObject->GetRect();

	//m_pTM->CheckCollision(pObject);

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
	if(m_bInvul == false)
	{
		if(m_fArmor>0)
		{
			m_fArmor-=nDamage/3;
			if( m_fArmor<0)
			m_fArmor=0;
		}
		else
		{
			m_fHealth -= nDamage;
			if(m_fHealth<0)
			m_fHealth=0;
		}
	}
}
