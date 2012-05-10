#ifndef CREATEBULLETMESSAGE_H_
#define CREATEBULLETMESSAGE_H_


#include "message.h" 

class CCreateBulletMessage : public CMessage
{
public:
	CCreateBulletMessage(MessageType msgType, int nBulletType);
	virtual ~CCreateBulletMessage(void);


private:
	int m_nBulletType;
};

#endif CREATEBULLETMESSAGE_H_
