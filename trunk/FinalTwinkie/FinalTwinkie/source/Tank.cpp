#include "Tank.h"
CTank::CTank(void)
{
}
CTank::~CTank(void)
{
}
void CTank::Update(float fDt)
{
}
void CTank::Render(void)
{
}
bool CTank::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CTank:: GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}
