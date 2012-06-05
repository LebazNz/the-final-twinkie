#include "../Headers/FlyText.h"
#include "../GameStates/OptionsState.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyFlyTextMessage.h"

void CFlyText::Update(float fDt)
{
	if(m_fTimer > 0.0f)
	{
		m_fTimer-=fDt;
		SetPosY(GetPosY()-5);
	}
	else
	{
		CDestroyFlyTextMessage* pMsg = new CDestroyFlyTextMessage(this);
		CMessageSystem::GetInstance()->SndMessage(pMsg);
		pMsg = nullptr;
	}
}

void CFlyText::Render(void)
{
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	font->Print(m_szType.c_str(),GetPosX(),GetPosY(),0.75f,m_DWColor);
}

CFlyText::CFlyText(void)
{
	m_nType = OBJ_FLYTEXT;
	m_szType = "blah";
	m_fTimer = 1.0f;
	m_DWColor = D3DCOLOR_XRGB(0,255,0);
}

CFlyText::~CFlyText(void)
{
}

void CFlyText::SetFlyText(int nType, float fTimer, DWORD dColor, float fX, float fY)
{  
	m_fTimer = fTimer; 
	m_DWColor = dColor;  
	SetPosX(fX);
	SetPosY(fY);
	switch(nType)
	{
	case 0:
		m_szType = "HEALTH";
		break;
	case 1:
		m_szType = "AMMO";
		break;
	case 2:
		m_szType = "ARMOR";
		break;
	case 3:
		m_szType = "DOUBLE DAMAGE";
		break;
	case 4:
		m_szType = "NO RELOAD";
		break;
	case 5:
		m_szType = "INVULNERABILITY";
		break;
	case 6:
		m_szType = "INFINITE AMMO";
		break;
	case 7:
		m_szType = "MONEY";
		break;
	}
}
