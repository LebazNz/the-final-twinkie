#ifndef CGAME_H_
#define CGAME_H_

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

class IGameState;

class CGame
{
public:
	static CGame* GetInstance(void);
	static void DeleteInstance(void);
	void ChangeState(IGameState* pNewState);
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int ScreenHeight, bool bWindowed);
	void Shutdown(void);
	bool Main(void);

private:
	CGame(void);
	CGame(const CGame&);
	CGame& operator=(const CGame&);
	~CGame(void);


	int						 m_nScreenWidth;
	int						 m_nScreenHeight;
	bool					 m_bWindowed;
	float					 m_fTime;
	IGameState*				 m_pCurState;
	CSGD_Direct3D*			 m_pD3D;
	CSGD_DirectInput*		 m_pDI;
	CSGD_TextureManager*	 m_pTM;
	static CGame*			 m_pSelf;
};

#endif
