#pragma once
#include "message.h"
class CCreateFactoryMessage :
	public CMessage
{
public:
	CCreateFactoryMessage(float PosX, float PosY);
	virtual ~CCreateFactoryMessage(void);

	float GetPosX(void) {return m_fPosX;}
	float GetPosY(void) {return m_fPosY;}

private:
	float m_fPosY;
	float m_fPosX;
};

