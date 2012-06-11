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
	void LoadText(void);

	float GetSFXVolume(void)const {return m_fSFXVolume;}
	float GetMusicVolume(void)const {return m_fMusicVolume;}
	int GetLang(void)const{return m_nLang;}
	void SetMusicVolume(int nMusic) { m_fMusicVolume = nMusic/100.0f;}
	void SetSFXVolume(int nSFX) { m_fSFXVolume = nSFX/100.0f;}
	void SetLang(int nLang) {m_nLang = nLang; }
	void SetWindowed(bool bWindowed) {m_bWindowed = bWindowed; }
	void SaveOptions(const char* szFileName);

private:
	COptionsState(void);
	COptionsState(const COptionsState&);
	COptionsState& operator=(const COptionsState&);
	virtual ~COptionsState(void);

	CSGD_Direct3D*			m_pD3D;
	CSGD_DirectInput*		m_pDI;
	CSGD_TextureManager*	m_pTM;
	CBitmapFont*			m_pFont;
	CSGD_XAudio2*			m_pAudio;

	static COptionsState*	m_pSelf;

	int						m_nSelected;

	int						m_nBGImageID;
	int						m_nPosition;
	int						m_nPointerID;
	int						m_nLang;
	float					m_fSFXVolume;
	float					m_fMusicVolume;
	bool					m_bWindowed;
	int						m_nButtonID;
	int						m_nButton;
	int						m_nClick;

	int m_nMouseX;
	int m_nMouseY;

	int m_nCursor;
	string m_sOptions;
	string m_sSFX;
	string m_sMusic;
	string m_sFullScreen;
	string m_sOn;
	string m_sOff;
	string m_sLanguage;
	string m_sSelected;
	string m_sBack;
};

#endif
