#include "CreateFactoryMessage.h"


CCreateFactoryMessage::CCreateFactoryMessage(float PosX, float PosY):CMessage(MSG_CREATEFACTORY)
{
	m_fPosY=PosY;
	m_fPosX=PosX;
}


CCreateFactoryMessage::~CCreateFactoryMessage(void)
{
}
