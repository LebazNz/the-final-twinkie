#ifndef DESTROYTREEMESSAGE_H_
#define DESTROYTREEMESSAGE_H_

#include "Message.h"
class CTree;

class CDestroyTreeMessage : public CMessage
{
private:
	CTree *m_pTree;
public:
	CDestroyTreeMessage(CTree* pTree);
	virtual ~CDestroyTreeMessage(void);

	CTree* GetTree(void) { return m_pTree;}
};

#endif