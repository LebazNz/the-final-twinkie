#pragma once
#include "message.h"
#include "../GameObjects/Factory.h"
class CDestroyFactoryMessage :
	public CMessage
{
public:
	CDestroyFactoryMessage(Factory* pFac);
	virtual ~CDestroyFactoryMessage(void);

	Factory* GetFactory(void) {return m_pFac;}
private:
	Factory* m_pFac;
};

