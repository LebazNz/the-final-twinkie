#include "DestroyBulletMessage.h"

#include "../GameObjects/Bullet.h"


CDestroyBulletMessage::CDestroyBulletMessage(CBullet* pBullet)
	: CMessage(MSG_DESTROYBULLET),
	  m_pBullet(pBullet)
{
	// Add ref to smart pointer
	if(m_pBullet != nullptr)
	{
		m_pBullet->AddRef();
	}
}


CDestroyBulletMessage::~CDestroyBulletMessage(void)
{
	// release ref to smart pointer
	if(m_pBullet != nullptr)
	{
		m_pBullet->Release();
	}
	m_pBullet = nullptr;
}