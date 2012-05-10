#include "Entity.h"
CEntity::CEntity(void)
{
}
CEntity::~CEntity(void)
{
}
void CEntity::Update(float)
{
}
void CEntity::Render(void)
{
}
bool CEntity::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CEntity::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}
void CEntity::TakeDamage(int)
{
}
void CEntity::AddRef(void)
{
}
void CEntity::Release(void)
{
}