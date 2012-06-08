#include "Jet.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../ObjectManager and Factory/ObjectManager.h"
#include "../Headers/Camera.h"
#include "../Headers/Game.h"
#include "../Event and Messages/DestrotJetMessage.h"
#include "../Event and Messages/MessageSystem.h"

CJet::CJet(void)
{
	m_nType = OBJ_JET;
	m_nJetID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/Jet.png"));
	SetImageID(m_nJetID);
	m_bDropper = false;
}

CJet::~CJet(void)
{
	if(m_nJetID != -1)
	{
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nJetID);
		m_nJetID = -1;
	}
}

void CJet::Update(float fDt)
{
	Camera* pCam =Camera::GetInstance();
	RECT rSelf = GetRect();

	this;
	if(GetPosY()/*-pCam->GetPosY()*/ < m_rTarget.bottom && GetPosY()/*-pCam->GetPosY()*/ > m_rTarget.top 
		&& GetPosX()/*-pCam->GetPosX()*/ < m_rTarget.right && GetPosX()/*-pCam->GetPosX()*/ > m_rTarget.left )
	{
		if(m_bDropper == false)
			DropBomb();
	}

	if(GetPosY()+pCam->GetPosY() < -150)
	{
		CDestrotJetMessage* pMsg = new CDestrotJetMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
	else
	{
		SetPosY(GetPosY()+GetVelY()*fDt);
	}
	
	
}

void CJet::Render(void)
{
	CGame *pGame = CGame::GetInstance();
	Camera* pCam =Camera::GetInstance();

	if(GetPosX()+pCam->GetPosX() >= -100 && GetPosX()+pCam->GetPosX() <= CGame::GetInstance()->GetWidth()+100 && GetPosY()+pCam->GetPosY() >= -100 && GetPosY()+pCam->GetPosY() <= CGame::GetInstance()->GetHeight()+100)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetImageID(), (int)(GetPosX()-GetWidth()/2+pCam->GetPosX()), (int)(GetPosY()-GetHeight()/2+pCam->GetPosY()), 1.0f, 1.0f, nullptr, 0, 0, 0.0f);
	}
}

void CJet::DropBomb(void)
{
	Camera* pCam =Camera::GetInstance();
	m_pEmitter->UpdateEmitterPos(GetPosX(),GetPosY());
	m_pEmitter->ActivateEmitter();
	CObjectManager::GetInstance()->AreaEffect(m_vPos.fX+pCam->GetPosX(),m_vPos.fY+pCam->GetPosY(),75,150);
	m_bDropper = true;
}

void CJet::SetTargetPos(tVector2D vPos)
{
	Camera* pCam =Camera::GetInstance();
	m_vPos = vPos;
	SetPosX(m_vPos.fX);
	SetPosY(650-pCam->GetPosY());
}
