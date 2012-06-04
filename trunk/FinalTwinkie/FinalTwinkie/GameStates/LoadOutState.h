#pragma once
#include "igamestate.h"
#include "../GameObjects/Player.h"



class CLoadOutState :
	public IGameState
{
public:
	static CLoadOutState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
private:
	CLoadOutState(void);
	CLoadOutState(const CLoadOutState&);
	CLoadOutState& operator=(const CLoadOutState&);
	virtual ~CLoadOutState(void);
	
	//Pointers
	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CPlayer*				m_pPlayer;

	static CLoadOutState*	m_pSelf;
};

