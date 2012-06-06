#include "../Headers/FlyText.h"
#include "../GameStates/OptionsState.h"
#include "../Event and Messages/MessageSystem.h"
#include "../Event and Messages/DestroyFlyTextMessage.h"
#include "../Headers/Camera.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"

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
	Camera* C = Camera::GetInstance();
	CBitmapFont* font = CBitmapFont::GetInstance();
	font->Init(COptionsState::GetInstance()->GetLang());
	font->Print(m_szType.c_str(),GetPosX()+C->GetPosX(),GetPosY()+C->GetPosY(),0.75f,m_DWColor);
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
	TiXmlDocument doc("resource/files/Text.xml");
	int LangSel=COptionsState::GetInstance()->GetLang();
	doc.LoadFile();
	TiXmlNode* pParent = doc.RootElement();
	TiXmlNode* pLanguage;
	switch(LangSel)
	{
	case 0:
		pLanguage = pParent->FirstChild("English");
		break;
	case 1:
		pLanguage = pParent->FirstChild("English");
		break;
	case 2:
		pLanguage = pParent->FirstChild("Pirate");
		break;
	case 3:
		break;
	}
	TiXmlNode* pState = pLanguage->FirstChild("FlyText");
	m_fTimer = fTimer; 
	m_DWColor = dColor;  
	SetPosX(fX);
	SetPosY(fY);
	switch(nType)
	{
	case 0:
		{
			TiXmlNode* pButton = pState->FirstChild("Health");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 1:
		{
			TiXmlNode* pButton = pState->FirstChild("Ammo");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 2:
		{
			TiXmlNode* pButton = pState->FirstChild("Armor");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 3:
		{
			TiXmlNode* pButton = pState->FirstChild("DDamage");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 4:
		{
			TiXmlNode* pButton = pState->FirstChild("NoReload");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 5:
		{
			TiXmlNode* pButton = pState->FirstChild("Invulnerability");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 6:
		{
			TiXmlNode* pButton = pState->FirstChild("InfiniteAmmo");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	case 7:
		{
			TiXmlNode* pButton = pState->FirstChild("Money");
			TiXmlText* pText = pButton->FirstChild()->ToText();
			m_szType=pText->Value();
		}
		break;
	}
}
