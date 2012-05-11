#ifndef COPTIONSSTATE_H_
#define COPTIONSSTATE_H_

#include "IGameState.h"

class COptionsState : public IGameState
{
public:
	static COptionsState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);	

private:
	COptionsState(void);
	COptionsState(const COptionsState&);
	COptionsState& operator=(const COptionsState&);
	virtual ~COptionsState(void);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;

	static COptionsState*	m_pSelf;

	int						m_nSelected;

	int						m_nBGImageID;
	int						m_nPosition;
	int						m_nPointerID;
};

#endif
