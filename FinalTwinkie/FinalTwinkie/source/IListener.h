#ifndef ILISTENER_H_
#define ILISTENER_H_

class CEvent;

class IListener
{
public:
	IListener(void) {}
	virtual ~IListener(void) {}

	virtual void HandleEvent(CEvent* pEvent) = 0;
};

#endif ILISTENER_H_