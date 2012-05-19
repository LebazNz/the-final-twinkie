#ifndef DESTROYENEMYMESSAGE_H_
#define DESTROYENEMYMESSAGE_H_


#include "message.h" 
class CEnemy;

class CDestroyEnemyMessage : public CMessage
{
public:
	CDestroyEnemyMessage(CEnemy* pEnemy);
	virtual ~CDestroyEnemyMessage(void);

	CEnemy* GetEnemy(void) { return m_pEnemy; }


private:
	CEnemy* m_pEnemy;
};

#endif DESTROYENEMYMESSAGE_H_