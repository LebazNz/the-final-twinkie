#include "MessageSystem.h"

#include "Message.h"

CMessageSystem* CMessageSystem::GetInstance(void)
{
	static CMessageSystem instance;
	return &instance;
}

void CMessageSystem::InitMessageSystem(MESSAGEPROC pfnProcess)
{

}

void CMessageSystem::SendMessage(CMessage* pMsg)
{
}

void CMessageSystem::ProcessMessages(void)
{
}

void CMessageSystem::ClearMessages(void)
{
}

void CMessageSystem::ShutDownMessageSystem(void)
{
}