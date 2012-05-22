#pragma once

#include "IGameState.h"

class CStartState : public IGameState
{
public:
	static  CStartState* GetInstance(void);
	static  void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
private:
	CStartState(void);
	virtual ~CStartState(void);
	CStartState(const CStartState&);
	CStartState& operator=(const CStartState&);

	CSGD_Direct3D*			m_pD3D;
	CSGD_TextureManager*	m_pTM;
	CSGD_DirectInput*		m_pDI;

	static CStartState*	m_pSelf;

	float m_nEndTimer;

	int m_nBG1ID;
	int m_nBG2ID;

	bool m_bSwitch;
};

