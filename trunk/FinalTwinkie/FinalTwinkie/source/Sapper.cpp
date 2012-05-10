#include "Sapper.h"
CSapper::CSapper(void)
{
}
CSapper::~CSapper(void)
{
}
void CSapper::Update(float fDt)
{
}
void CSapper::Render(void)
{
}
bool CSapper::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CSapper::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}