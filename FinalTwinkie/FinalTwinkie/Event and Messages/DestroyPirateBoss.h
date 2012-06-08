#ifndef DESTROYPIRATEBOSS_H_
#define DESTROYPIRATEBOSS_H_

#include "Message.h"
class CPirateBoss;

class CDestroyPirateBoss : public CMessage
{
public:
	CDestroyPirateBoss(CPirateBoss* pBoss);
	virtual ~CDestroyPirateBoss(void);

	CPirateBoss* GetBoss(void) const {return m_pBoss;}

private:
	CPirateBoss* m_pBoss;
};

#endif