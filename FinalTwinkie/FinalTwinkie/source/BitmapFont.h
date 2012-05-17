#ifndef CBITMAPFONT_H_
#define CBITMAPFONT_H_

#include <Windows.h>
#include <string>
using std::string;

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/SGD_Math.h"

class CBitmapFont
{
public:
	static CBitmapFont* GetInstance(void);
	static void DeleteInstance(void);
	void Print(const char* szText, int nPosX, int nPosY,float fScale, DWORD dwColor);
	void Init(string filename, int width, int height, int rows, int cols, char character);
	RECT CellAlgorithm(int id);

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
	char m_cFirstChar;

	static CBitmapFont*	m_pSelf;
};


#endif
