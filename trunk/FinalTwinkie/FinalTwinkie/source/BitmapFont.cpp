#include "BitmapFont.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CBitmapFont* CBitmapFont::m_pSelf = nullptr;

CBitmapFont* CBitmapFont::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CBitmapFont();
	return m_pSelf;
}

void CBitmapFont::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CBitmapFont::CBitmapFont(void)
{
}

CBitmapFont::~CBitmapFont(void)
{
}

void CBitmapFont::Print(const char* szText, int nPosX, int nPosY,float fScale, DWORD dwColor)
{
	int ColStart = nPosX;
	int nLen = strlen(szText);
	for(int i = 0; i < nLen; i++)
	{
		char ch = szText[i];
		if(ch == ' ')
		{

		}
		else if(ch == '\n')
		{

		}

		int id = ch-m_cFirstChar;

		RECT rTile = CellAlgorithm(id);

		CSGD_TextureManager::GetInstance()->Draw(m_nFontID,nPosX,nPosY,fScale,fScale, &rTile,0,0,0,dwColor);
	
		nPosX += (int)(m_nCharWidth*fScale);
	}
}

void CBitmapFont::Init(string filename, int width, int height, int rows, int cols, char character)
{
	m_nCharWidth = width;
	m_nCharHeight = height;
	m_nNumRows = rows;
	m_nNumCols = cols;

	TCHAR buffer[100];
	mbstowcs_s(nullptr,buffer,100,filename.c_str(),_TRUNCATE);

	m_nFontID = CSGD_TextureManager::GetInstance()->LoadTexture(buffer,0);
	m_cFirstChar = character;
}

RECT CBitmapFont::CellAlgorithm(int id)
{
	RECT rCell;

	rCell.left = (id%m_nNumCols)*m_nCharWidth;
	rCell.top = (id/m_nNumCols)*m_nCharHeight;
	rCell.right = rCell.left+m_nCharWidth;
	rCell.bottom = rCell.top+m_nCharHeight;

	return rCell;
}
