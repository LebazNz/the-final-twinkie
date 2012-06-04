#ifndef MESSAGE_H_
#define MESSAGE_H_

enum MessageType { MSG_CREATEBULLET, MSG_DESTROYBULLET, MSG_CREATEENEMY, MSG_DESTROYENEMY, MSG_DESTROYTURRET, MSG_CREATEPICKUP, MSG_DESTROYPICKUP,
	MSG_DESTROYBUILDING,MSG_CREATEBUILDING, MSG_CREATEMINE, MSG_DESTROYMINE, MSG_SOLDIERFIRE, MSG_CREATETREE, MSG_DESTROYTREE};

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