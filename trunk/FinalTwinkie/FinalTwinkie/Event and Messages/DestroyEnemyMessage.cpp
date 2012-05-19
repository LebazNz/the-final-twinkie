#include "DestroyEnemyMessage.h"

#include "../GameObjects/Enemy.h"


CDestroyEnemyMessage::CDestroyEnemyMessage(CEnemy* pEnemy)
	: CMessage(MSG_DESTROYENEMY),
	  m_pEnemy(pEnemy)
{
	// Add ref to smart pointer
	if(m_pEnemy != nullptr)
	{
		m_pEnemy->AddRef();
	}
}


CDestroyEnemyMessage::~CDestroyEnemyMessage(void)
{
	// release ref to smart pointer
	if(m_pEnemy != nullptr)
	{
		m_pEnemy->Release();
	}
	m_pEnemy = nullptr;
}