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
	void LoadText(void);

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

	int	m_nBGImageID;
	int m_nButtonID;
	int m_nPosY;
	float m_fTimer;
	int m_nMouseX;
	int m_nMouseY;

	int m_nButton;
	int m_nClick;

	int m_nCursor;
	DWORD m_dColor;

	string m_sDAP;
	string m_sEP;
	string m_sAP;
	string m_sAL;
	string m_sBack;
	string m_sAddArt;
	string m_sAddProg;
};


#endif
