#include "MessageSystem.h"

#include "Message.h"

CMessageSystem* CMessageSystem::m_pSelf = nullptr;

CMessageSystem* CMessageSystem::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CMessageSystem;
	return m_pSelf;
}

void CMessageSystem::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CMessageSystem::InitMessageSystem(MESSAGEPROC pfnProcess)
{
	if(!pfnProcess)
		return;
	m_pfnProcess = pfnProcess;
}

void CMessageSystem::SndMessage(CMessage* pMsg)
{
	if(!pMsg)
		return;
	m_qMessages.push(pMsg);
}

void CMessageSystem::ProcessMessages(void)
{
	if(!m_pfnProcess)
		return;
	while(!m_qMessages.empty())
	{
		m_pfnProcess(m_qMessages.front());
		delete m_qMessages.front();
		m_qMessages.pop();
	}
}

void CMessageSystem::ClearMessages(void)
{
	while(!m_qMessages.empty())
	{
		delete m_qMessages.front();
		m_qMessages.pop();
	}
}

void CMessageSystem::ShutDownMessageSystem(void)
{
	ClearMessages();
	m_pfnProcess = NULL;
}