#include "Enemy.h"
CEnemy::CEnemy(void)
{
}
CEnemy::~CEnemy(void)
{
}
void CEnemy::Update(float fDt)
{
}
void CEnemy::Render(void)
{
}
bool CEnemy::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CEnemy::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}