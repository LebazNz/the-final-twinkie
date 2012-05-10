#ifndef CBITMAPFONT_H_
#define CBITMAPFONT_H_

class CBitmapFont
{
public:
	static CBitmapFont* GetInstance(void);
	static void DeleteInstance(void);
	void Print(char szText, int nPosX, int nPosY,float fScaleX, float fScaleY);

private:
	CBitmapFont(void);
	CBitmapFont(const CBitmapFont&);
	CBitmapFont& operator=(const CBitmapFont&);
	~CBitmapFont(void);

	int m_nFontID;
	int m_nCharWidth;
	int m_nCharHeight;
	int m_nNumCols;
	int m_nNumRows;

	static CBitmapFont*	m_pSelf;
};


#endif
