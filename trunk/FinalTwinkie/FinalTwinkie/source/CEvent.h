#ifndef EVENT_H_
#define EVENT_H_

#include <string>
using std::string;
typedef string EVENTID;

class CEvent
{
public:
	CEvent(EVENTID eventID, void* pParam = NULL)
	{
		m_EventID = eventID;
		m_pParam = pParam;
	}

	~CEvent(void){}

	EVENTID GetEventID(void) const { return m_EventID; }
	void* GetParam(void) const { return m_pParam; }

private:
	EVENTID m_EventID;
	void* m_pParam;
};

#endif EVENT_H_