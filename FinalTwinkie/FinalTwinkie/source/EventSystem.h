#ifndef EVENTSYSTEM_H_
#define EVENTSYSTEM_H_

#include <list>
#include <map>
using namespace std;

#include "CEvent.h"
#include "IListener.h"

class CEventSystem
{
public:
	static CEventSystem* GetInstance(void);
	static void DeleteInstance(void);

	void RegisterClient(EVENTID eventID, IListener* pClient);
	void UnregisterClient(EVENTID eventID, IListener* pClient);
	void UnregisterClientAll(IListener* pClient);
	bool HasEventTriggered(EVENTID eventID);
	void SendEvent(EVENTID eventID, void* pData = NULL);
	void SendUniqueEvent(EVENTID eventID, void* pData = NULL);
	void ProcessEvents(void);
	void ClearEvents(void);
	void ShutdownEventSystem(void);

private:
	CEventSystem(void) {}
	~CEventSystem(void) {}
	CEventSystem(const CEventSystem&);
	CEventSystem& operator=(const CEventSystem&);

	multimap<EVENTID, IListener*> m_mmClientDataBase;
	list<CEvent> m_lCurrentEvents;
	static CEventSystem* m_pSelf;

	void DispatchEvent(CEvent* pEvent);
	bool AlreadyRegistered(EVENTID eventID, IListener* pClient);
};

#endif EVENTSYSTEM_H_
