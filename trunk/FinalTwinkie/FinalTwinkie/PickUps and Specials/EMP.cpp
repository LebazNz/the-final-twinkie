#include "EMP.h"
#include "../GameObjects/Player.h"
#include "../Headers/Camera.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CEMP::CEMP(void)
{
	m_fScale = 0.15f;
	m_nAmmo = 3;
	m_nEMPID=CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/EMP.png"));
	
	//CObjectManager::GetInstance()->AddObject
}

CEMP::~CEMP(void)
{
	if(m_nEMPID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nEMPID);
	m_nEMPID = -1;
}

void CEMP::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nEMPID,CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_fScale,m_fScale,nullptr,0.0f,0.0f,0.0f);
}

void CEMP::Update(float fDt)
{
	if(m_fDuration > 0.0f)
	{
		m_fDuration -= fDt;
		m_fScale += 0.15f;
	}
	else
	{
		m_fScale = 100.0f;
	}
}

void CEMP::ActivateSpecial(void)
{
	if(m_nAmmo != 0)
	{
		m_fScale = 0.15f;
		Camera* c = Camera::GetInstance();
		CObjectManager::GetInstance()->AreaEffect(CPlayer::GetInstance()->GetPosX(),CPlayer::GetInstance()->GetPosY(),m_nRadius,0);
		m_nAmmo--;
	}	
}
