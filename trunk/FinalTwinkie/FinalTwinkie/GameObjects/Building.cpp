#include "Building.h"

void CBuilding::Update(float)
{
}
void CBuilding::Render(void)
{
}
RECT CBuilding::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}
bool CBuilding::CheckCollision(IEntity*)
{
	return false;
}
CBuilding::CBuilding(void)
{
}
CBuilding::~CBuilding(void)
{
}