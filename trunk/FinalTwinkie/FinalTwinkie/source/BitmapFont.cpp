#include "BitmapFont.h"

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



void CBitmapFont::Print(char szText, int nPosX, int nPosY,float fScaleX, float fScaleY)
{

}
