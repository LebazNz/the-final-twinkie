#ifndef CREATEBUILDING_H_
#define CREATEBUILDING_H_

#include "Message.h"

class CCreateBuildingMessage : public CMessage
{
public:
	CCreateBuildingMessage(MessageType msgType, int nType, float x = 0.0f, float y = 0.0f, bool spawn = false, float time = 0.25f);
	virtual ~CCreateBuildingMessage(void);

	int GetType(void) const { return m_nType; }
	float GetPosX(void) const { return m_nPosX; }
	float GetPosY(void) const { return m_nPosY; }
	bool GetSpawn(void) const { return m_bSpawn;}
	float GetTime(void) const{ return m_fTime;}

private:
	int m_nType;
	float m_nPosX;
	float m_nPosY;
	bool m_bSpawn;
	float m_fTime;
	
};

#endif