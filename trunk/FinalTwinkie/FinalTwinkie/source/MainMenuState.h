#ifndef CMAINMENUSTATE_H_
#define CMAINMENUSTATE_H_

#include "IGameState.h"

class CMainMenuState : public IGameState
{
public:
	static CMainMenuState* GetInstance(void);
	virtual void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);
	

private:
	CMainMenuState(void);
	CMainMenuState(const CMainMenuState&);
	CMainMenuState& operator=(const CMainMenuState&);
	virtual ~CMainMenuState(void);

	CSGD_Direct3D*					m_pD3D;
	CSGD_DirectInput*				m_pDI;
	CSGD_TextureManager*			m_pTM;
	CBitmapFont*					m_pFont;

	static CMainMenuState*			m_pSelf;

	int								m_nSelected;

	int								m_nBGImageID;

	
};


#endif
