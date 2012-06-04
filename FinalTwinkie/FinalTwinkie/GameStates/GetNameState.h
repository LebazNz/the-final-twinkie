#pragma once

#include "Igamestate.h"

class CGetNameState : public IGameState
{
public:
	static CGetNameState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);


private:
	CGetNameState(void);
	virtual ~CGetNameState(void);
	CGetNameState(const CGetNameState&);
	CGetNameState& operator=(const CGetNameState&);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;

	static CGetNameState* m_pSelf;

	int	m_nBGImageID;
	int	m_nButtonImageID;

	int m_nMouseX;
	int m_nMouseY;

	int m_nCursor;

	bool m_bLowCase;

	char szName[32];
	int m_nCount;
	int m_nPos;
};

