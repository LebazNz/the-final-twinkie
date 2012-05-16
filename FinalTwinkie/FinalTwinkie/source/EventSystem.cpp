#include "EventSystem.h"

CEventSystem* CEventSystem::m_pSelf = nullptr;

CEventSystem* CEventSystem::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CEventSystem;
	return m_pSelf;
}

void CEventSystem::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CEventSystem::RegisterClient(EVENTID eventID, IListener* pClient)
{
	if(AlreadyRegistered(eventID, pClient) || !pClient)
		return;

	m_mmClientDataBase.insert(make_pair(eventID, pClient));
}

void CEventSystem::UnregisterClient(EVENTID eventID, IListener* pClient)
{
	pair<multimap<EVENTID, IListener*>::iterator,multimap<EVENTID, IListener*>::iterator> clients;

	clients = m_mmClientDataBase.equal_range(eventID);

	multimap<EVENTID, IListener*>::iterator iter;
	for(iter = clients.first; iter != clients.second; iter++)
	{
		if((*iter).second == pClient)
		{
			iter = m_mmClientDataBase.erase(iter);
			break;
		}
	}
}

void CEventSystem::UnregisterClientAll(IListener* pClient)
{
	multimap<string,IListener*>::iterator iter = m_mmClientDataBase.begin();

	while(iter != m_mmClientDataBase.end())
	{
		if((*iter).second == pClient)
			iter = m_mmClientDataBase.erase(iter);
		else
			iter++;
	}
}

bool CEventSystem::HasEventTriggered(EVENTID eventID)
{
	list<CEvent>::iterator iter;

	for(iter =  m_lCurrentEvents.begin(); iter != m_lCurrentEvents.end(); iter++)
		if((*iter).GetEventID() == eventID)
			return true;

	return false;
}

void CEventSystem::SendEvent(EVENTID eventID, void* pData)
{
	CEvent nwEvent(eventID, pData);

	m_lCurrentEvents.push_back(nwEvent);
}

void CEventSystem::SendUniqueEvent(EVENTID eventID, void* pData)
{
	if(HasEventTriggered(eventID))
		return;

	SendEvent(eventID,pData);
}

void CEventSystem::ProcessEvents(void)
{
	while(m_lCurrentEvents.size())
	{
		DispatchEvent(&m_lCurrentEvents.front());
		m_lCurrentEvents.pop_front();
	}
}

void CEventSystem::ClearEvents(void)
{
	m_lCurrentEvents.clear();
}

void CEventSystem::ShutdownEventSystem(void)
{
	m_mmClientDataBase.clear();
}

void CEventSystem::DispatchEvent(CEvent* pEvent)
{
	pair<multimap<EVENTID, IListener*>::iterator,multimap<EVENTID, IListener*>::iterator> clients;

	clients = m_mmClientDataBase.equal_range(pEvent->GetEventID());

	multimap<EVENTID, IListener*>::iterator iter;
	for(iter = clients.first; iter != clients.second; iter++)
		(*iter).second->HandleEvent(pEvent);
}

bool CEventSystem::AlreadyRegistered(EVENTID eventID, IListener* pClient)
{
	bool bIsRegistered = false;

	pair<multimap<EVENTID, IListener*>::iterator,multimap<EVENTID, IListener*>::iterator> clients;

	clients = m_mmClientDataBase.equal_range(eventID);

	multimap<EVENTID, IListener*>::iterator iter;
	for(iter = clients.first; iter != clients.second; iter++)
		if((*iter).second == pClient)
		{
			bIsRegistered = true;
			break;
		}

	return bIsRegistered;
}
