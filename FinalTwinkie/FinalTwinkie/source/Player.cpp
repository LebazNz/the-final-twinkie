#include "Player.h"


void CPlayer::Update(float fDt)
{
}
void CPlayer::Render(void)
{
}
RECT CPlayer::GetRect(void)
{
	RECT* fred = new RECT;
	return *fred;
}
bool CPlayer::CheckCollision(IEntity* pBase)
{
	return false;
}
void CPlayer::Input(void)
{
}
CPlayer::CPlayer(void)
{
}
CPlayer::~CPlayer(void)
{
}
