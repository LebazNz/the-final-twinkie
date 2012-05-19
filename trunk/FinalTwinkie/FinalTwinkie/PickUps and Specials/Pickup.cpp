#include "Pickup.h"
void CPickup::Update(float fDt)
{
}
void CPickup::Render(void)
{
}
bool CPickup::CheckColision(IEntity* pBase)
{
	return false;
}
RECT CPickup::GetRect(void)
{
	RECT *fred = new RECT;
	return *fred;
}
CPickup::CPickup(void)
{
}
CPickup::~CPickup(void)
{
}