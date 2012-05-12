#include "Enemy.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CEnemy::CEnemy(void)
{
	m_nType = OBJ_ENEMY;
	m_fMaxDist = 0;
	m_fMinDist = 0;
	m_nMainBulletType = BUL_SHELL;
	m_nMachineGunBulletType = BUL_MACHINEGUN;
	m_fFireRate = 0;
	m_nRefCount = 0;
}

CEnemy::~CEnemy(void)
{
}

void CEnemy::Update(float fDt)
{
	int nY = GetPosY();
	nY++;
	SetPosY(nY);
}

void CEnemy::Render(void)
{
	if(GetImageID() != -1)
	{
		CSGD_TextureManager::GetInstance()->Draw( GetImageID(), 
					int(GetPosX()), int(GetPosY()), 1.0f, 1.0f, nullptr, 
					GetWidth()/2.0f, GetHeight()/2.0f, 0, 
					DWORD(GetColor()) );
	}
}

bool CEnemy::CheckCollision(IEntity* pBase)
{
	return false;
}

RECT CEnemy::GetRect(void) const
{
	return CEntity::GetRect();
}

void CEnemy::AddRef(void)
{
	m_nRefCount++;
}

void CEnemy::Release(void)
{
	m_nRefCount--;

	if(m_nRefCount == 0)
		delete this;
}