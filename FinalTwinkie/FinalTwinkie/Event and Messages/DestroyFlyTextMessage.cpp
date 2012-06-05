#include "DestroyFlyTextMessage.h"
#include "../Headers/FlyText.h"

CDestroyFlyTextMessage::CDestroyFlyTextMessage(CFlyText* pFlyText)
	: CMessage(MSG_DESTROYFLYTEXT), m_pFlyText(pFlyText)
{
	if(m_pFlyText != nullptr)
		m_pFlyText->AddRef();
}


CDestroyFlyTextMessage::~CDestroyFlyTextMessage(void)
{
	if(m_pFlyText != nullptr)
		m_pFlyText->Release();
	m_pFlyText = nullptr;
}
