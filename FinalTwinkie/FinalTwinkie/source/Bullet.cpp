#include "Bullet.h"


void CBullet::Update(float fDT)
{
}
void CBullet::Render(void)
{
}
bool CBullet::CheckCollision(IEntity* pBase)
{
	return false;
}
RECT CBullet::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}

CBullet::CBullet(void)
{
}


CBullet::~CBullet(void)
{
}
