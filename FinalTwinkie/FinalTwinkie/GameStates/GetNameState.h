#pragma once

#include "Igamestate.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

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
	bool GetSurvival() const { return m_bSurvival; }
	void SetSurvival(bool val) { m_bSurvival = val; }

private:
	CGetNameState(void);
	virtual ~CGetNameState(void);
	CGetNameState(const CGetNameState&);
	CGetNameState& operator=(const CGetNameState&);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CSGD_XAudio2*			m_pAudio;

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
	bool m_bSurvival;
	bool m_bHold;

	int m_nButton;
	int m_nClick;

	string m_sShift;
	string m_sSpace;
	string m_sBackspace;
	string m_sEnter;
	string m_sName;
};

