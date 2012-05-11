#ifndef CCREDITSSTATE_H_
#define CCREDITSSTATE_H_

#include "IGameState.h"


class CCreditsState : public IGameState
{
public:
	static CCreditsState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	

private:
	CCreditsState(void);
	CCreditsState(const CCreditsState&);
	CCreditsState& operator=(const CCreditsState&);
	virtual ~CCreditsState(void);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;

	static CCreditsState*	m_pSelf;

	int								m_nBGImageID;	
};


#endif
