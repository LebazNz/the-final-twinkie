#ifndef MESSAGESYSTEM_H_
#define MESSAGESYSTEM_H_

#include <queue>
using std::queue;

class CMessage;

typedef void (*MESSAGEPROC)(CMessage*);

class CMessageSystem
{
public:
	static CMessageSystem* GetInstance(void);
	static void DeleteInstance(void);
	void InitMessageSystem(MESSAGEPROC pfnProcess);
	void SndMessage(CMessage* pMsg);
	void ProcessMessages(void);
	void ClearMessages(void);
	void ShutDownMessageSystem(void);

private:
	queue<CMessage*> m_qMessages;
	MESSAGEPROC m_pfnProcess;

	static CMessageSystem* m_pSelf;

	CMessageSystem(void) { m_pfnProcess = NULL; }
	CMessageSystem(const CMessageSystem&);
	CMessageSystem& operator=(const CMessageSystem&);
	~CMessageSystem(void){}

};

#endif MESSAGESYSTEM_H_