#include "EMPBlast.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../Event and Messages/DestroyEMPMessage.h"
#include "../Event and Messages/MessageSystem.h"

CEMPBlast::CEMPBlast(void)
{
	m_nType = OBJ_EMPBLAST;
	m_fTimer = 0.5f;
	m_fScale = 0.0;
	m_nOffsetX = -100;
	m_nOffsetY = -100;
	m_nEMPImageID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/EMP.png"));
	SetImageID(m_nEMPImageID);
	SetWidth(256);
	SetHeight(256);
}

CEMPBlast::~CEMPBlast(void)
{
	if(m_nEMPImageID != -1)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nEMPImageID);
		m_nEMPImageID = -1;
	}
}

void CEMPBlast::Update(float fDt)
{
	Camera* pCam =Camera::GetInstance();

	if(m_fTimer > 0.0f)
	{
		m_nOffsetX += 25;
		m_nOffsetY += 25;
		m_fTimer -= fDt;
		m_fScale += 0.25f;
	}
	else
	{
		CObjectManager::GetInstance()->AreaEffect(GetPosX()+pCam->GetPosX(),GetPosY()+pCam->GetPosY(),256,0,true);
		CDestroyEMPMessage* pMsg = new CDestroyEMPMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
	
}

void CEMPBlast::Render(void)
{
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+pCam->GetPosX())-m_nOffsetX, (int)(GetPosY()-GetHeight()/2+pCam->GetPosY())-m_nOffsetY, m_fScale, m_fScale, nullptr, 0, 0, 0.0f);
	}
}

