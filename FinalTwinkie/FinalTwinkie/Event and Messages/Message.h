#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { MSG_CREATEBULLET, MSG_DESTROYBULLET, MSG_CREATEENEMY, MSG_DESTROYENEMY, MSG_DESTROYTURRET };

class CMessage
{
public:
	explicit CMessage(MessageType msgID);
	virtual ~CMessage(void);

	MessageType GetMessageID(void) const { return m_nMessageType; }

private:
	MessageType m_nMessageType;
};

#endif MESSAGE_H_