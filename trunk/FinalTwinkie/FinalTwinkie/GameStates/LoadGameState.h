#pragma once
#include "Igamestate.h"

#include <string>
using std::string;

#include <vector>
using std::vector;


class CLoadGameState : public IGameState
{
public:
	static CLoadGameState* GetInstance(void);
	static void DeleteInstance(void);
	virtual void Enter(void);
	virtual void Exit(void);
	virtual bool Input(void);
	virtual void Update(float fDt);
	virtual void Render(void);

	bool LoadSavedGame(const char* szFileName, int nGameData);


private:
	CLoadGameState(void);
	virtual ~CLoadGameState(void);
	CLoadGameState(const CLoadGameState&);
	CLoadGameState& operator = (const CLoadGameState&);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;

	static CLoadGameState*	m_pSelf;

	int						m_nBGImageID;
	int						m_nPosition;
	int						m_nCount;

	Data vSavedData[3];
};

