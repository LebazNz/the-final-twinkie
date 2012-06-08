#ifndef CGUI_H_
#define CGUI_H_

class CPlayer;
class CBitmapFont;
#include "../SGD Wrappers/CSGD_TextureManager.h"

class CGUI
{
public:
	static CGUI* GetInstance(void);
	static void DeleteInstance(void);
	void Render(void);
	void Update(float fDt);

	void SetHudID(int ID){m_nHudID=ID;}
	void SetSelect(int ID) {m_nSpecialSel=ID;}
	void SetGunSel(int ID) {m_nGunSel=ID;}
	void SetPlayer(CPlayer* pPlayer){m_pPlayer=pPlayer;}
	void SetGunSelected(int Sel) {m_nGunSelected=Sel;}
	
private:
	CGUI(void);
	CGUI(const CGUI&);
	CGUI& operator=(const CGUI&);
	~CGUI(void);

	CBitmapFont*		m_pFont;
	static CGUI*		m_pSelf;
	CSGD_TextureManager* m_pTM;
	int					m_nHudID;
	int					m_nSpecialSel;
	int					m_nGunSel;
	int					m_nGunSelected;
	CPlayer*			m_pPlayer;
};

#endif