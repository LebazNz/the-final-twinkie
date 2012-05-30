#ifndef DESTROYMINEMESSAGE_H_
#define DESTROYMINEMESSAGE_H_

#include "Message.h"
class CMine;

class CDestroyMineMessage : public CMessage
{
private:
	CMine* m_pMine;
public:
	CDestroyMineMessage(CMine *pMine);
	virtual ~CDestroyMineMessage(void);

	CMine* GetMine(void) { return m_pMine;}

};

#endif