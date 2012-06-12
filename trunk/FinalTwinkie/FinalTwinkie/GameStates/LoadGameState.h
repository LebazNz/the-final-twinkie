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
	void LoadText(void);
	void SetSong(int s) { m_nMusic = s;}

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
	CSGD_XAudio2*				m_pAudio;

	static CLoadGameState*	m_pSelf;

	int						m_nBGImageID;
	int						m_nPosition;
	int						m_nCount;
	int						m_nButtonImageID;
	int						m_nMusic;
	int						m_nButton;
	int						m_nClick;

	Data vSavedData[3];

	int m_nMouseX;
	int m_nMouseY;

	int m_nCursor;
	string m_sNewGame;
	string m_sLoad;
	string m_sDelete;
	string m_sName;
	string m_sLevel;
	string m_sMoney;
};

