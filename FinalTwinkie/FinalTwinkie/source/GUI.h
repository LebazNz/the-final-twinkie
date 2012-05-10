#ifndef CGUI_H_
#define CGUI_H_

class CPlayer;
class CBitmapFont;

class CGUI
{
public:
	static CGUI* GetInstance(void);
	static void DeleteInstance(void);
	void Render(CPlayer* pPlayer);
	
private:
	CGUI(void);
	CGUI(const CGUI&);
	CGUI& operator=(const CGUI&);
	~CGUI(void);

	CBitmapFont*		m_pFont;
	static CGUI*		m_pSelf;
};

#endif