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
	void LoadText(void);
	bool LoadOptions(const char* szFileName);
	int GetMusicVolume(void)const{return m_nCurVolume;}
	int GetSFXVolume(void) const { return m_nSFXVolume;}
	bool GetWindowed(void)const { return m_bWindowed;}
	void PlayHighlight(DWORD dwPlayColor);
	void SetSong(int s) { m_nMenuMusicID = s;}

private:
	CMainMenuState(void);
	CMainMenuState(const CMainMenuState&);
	CMainMenuState& operator=(const CMainMenuState&);
	virtual ~CMainMenuState(void);

	CSGD_Direct3D*					m_pD3D;
	CSGD_DirectInput*				m_pDI;
	CSGD_TextureManager*			m_pTM;
	CBitmapFont*					m_pFont;
	CSGD_XAudio2*					m_pAudio;

	static CMainMenuState*			m_pSelf;

	int								m_nSelected;

	int								m_nBGImageID;
	int								m_nNameImageID;
	int								m_nButtonImageID;
	int								m_nPosition;
	int								m_nPointerID;
	int								m_nSFXVolume;
	int								m_nCurVolume;
	int								m_nLang;
	bool							m_bWindowed;
	int								m_nPos2;
	int								m_nMouseX;
	int								m_nMouseY;
	int								m_nMenuMusicID;
	int								m_nButton;
	int								m_nClick;
	bool							m_bPlayedSound;

	int m_nCursor;

	string m_sPlay;
	string m_sOptions;
	string m_sCredits;
	string m_sExit;
	string m_sCampaign;
	string m_sSurvival;
	string m_sTutor;
	
};


#endif
