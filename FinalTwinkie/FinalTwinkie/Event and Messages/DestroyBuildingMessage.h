#ifndef DESTROYBUILDINGMESSAGE_H_
#define DESTROYBUILDINGMESSAGE_H_


#include "message.h" 
class CBuilding;

class CDestroyBuildingMessage : public CMessage
{
public:
	CDestroyBuildingMessage(CBuilding* pBuilding);
	virtual ~CDestroyBuildingMessage(void);

	CBuilding* GetBuilding(void) {return m_pBuilding; }


private:
	CBuilding* m_pBuilding;
};

#endif DESTROYBUILDINGMESSAGE_H_