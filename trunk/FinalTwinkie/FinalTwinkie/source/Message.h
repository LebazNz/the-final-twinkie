#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { MSG_CREATEBULLET, MSG_DESTROYBULLET, MSG_CREATEENEMY, MSG_DESTROYENEMY };

class CMessage
{
public:
	explicit CMessage(MessageType msgID);
	virtual ~CMessage(void);
private:
	MessageType m_nMessageType;
};

#endif MESSAGE_H_