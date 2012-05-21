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
	float GetSFXVolume(void)const {return m_fSFXVolume;}
	float GetMusicVolume(void)const {return m_fMusicVolume;}
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

	static COptionsState*	m_pSelf;

	int						m_nSelected;

	int						m_nBGImageID;
	int						m_nPosition;
	int						m_nPointerID;
	int						m_nLang;
	float					m_fSFXVolume;
	float					m_fMusicVolume;
	bool					m_bWindowed;

	int m_nMouseX;
	int m_nMouseY;

	int m_nCursor;
};

#endif
