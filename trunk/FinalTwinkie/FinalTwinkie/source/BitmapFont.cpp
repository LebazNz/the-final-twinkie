#include "../Headers/BitmapFont.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
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
	//m_nX = nPosY;
	m_fScale = fScale;
	int ColStart = nPosX;
	int nLen = strlen(szText);
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	for(int i = 0; i < nLen; i++)
	{
		char ch = szText[i];

		SetOffset(ch);

		if(ch == ' ')
		{
			nPosX += int(m_nCharWidth*m_fScale)-(int)(m_fOffset*m_fScale);
			continue;
		}
		else if(ch == '\n')
		{
			nPosY += int(m_nCharHeight*m_fScale);
			nPosX = ColStart;
			continue;
		}

		int id = ch-m_cFirstChar;

		RECT rTile = CellAlgorithm(id);

		if(m_nType == 2)
			m_fScale = fScale+0.45f;
		else if(m_nType == 1)
			m_fScale = fScale-0.15f;

		CSGD_TextureManager::GetInstance()->Draw(m_nFontID,nPosX,nPosY+m_nX,m_fScale,m_fScale, &rTile,0,0,0,dwColor);
	
		nPosX += int((m_nCharWidth*m_fScale)-(m_fOffset*m_fScale));

		m_fScale = fScale;
		//m_nX = nPosY;
	}
}

void CBitmapFont::Init(int nType)
{
	if(nType == 0 || nType == 1 || nType == 2 || nType == 3)
		m_nType = nType;
	else
		m_nType = 0;

	switch(m_nType)
	{
	case 3:
		{
			m_nCharWidth = 43;
			m_nCharHeight = 43;
			m_nNumRows = 9;
			m_nNumCols = 11;

			m_nFontID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/WantedFonttest.png"));
			m_cFirstChar = 32;
		}
		break;
	
	case 1:
		{
			m_nCharWidth = 32;
			m_nCharHeight = 32;
			m_nNumRows = 14;
			m_nNumCols = 16;

			m_nFontID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/AurebeshFont.png"),D3DCOLOR_XRGB(255,255,255));
			m_cFirstChar = 32;
		}
		break;
	case 2:
		{
			m_nCharWidth = 32;
			m_nCharHeight = 32;
			m_nNumRows = 14;
			m_nNumCols = 16;
			
			m_nFontID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/SchwabacherFont.png"),D3DCOLOR_XRGB(255,255,255));
			m_cFirstChar = 32;
		}
		break;
	case 0:
		{
			m_nCharWidth = 43;
			m_nCharHeight = 43;
			m_nNumRows = 11;
			m_nNumCols = 11;
			
			m_nFontID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("resource/graphics/GermanBlackLetter.png"),D3DCOLOR_XRGB(255,255,255));
			m_cFirstChar = 32;
		}
		break;
	}
}

RECT CBitmapFont::CellAlgorithm(int id)
{
	RECT rCell;

	rCell.left = LONG((id%m_nNumCols)*m_nCharWidth);
	rCell.top = LONG((id/m_nNumCols)*m_nCharHeight);
	rCell.right = LONG(rCell.left+m_nCharWidth);
	rCell.bottom = LONG(rCell.top+m_nCharHeight);

	return rCell;
}

void CBitmapFont::SetOffset(int ch)
{
	float fScale = 0.25f;//0.25f
	int nY = 6;//6
	m_nX = 0;
	switch(m_nType)
	{
	case 3:
		{
			switch(ch)
			{
			case 32:
				m_fOffset = m_nCharWidth-8;
				break;
			case 33:
				m_fOffset = m_nCharWidth-10;
				break;
			case 34:
				m_fOffset = m_nCharWidth-10;
				break;
			case 35:
				m_fOffset = m_nCharWidth-20;
				break;
			case 36:
				m_fOffset = m_nCharWidth-15;
				break;
			case 37:
				m_fOffset = m_nCharWidth-24;
				break;
			case 38:
				m_fOffset = m_nCharWidth-25;
				break;
			case 39:
				m_fOffset = m_nCharWidth-5;
				break;
			case 40:
				m_fOffset = m_nCharWidth-11;
				break;
			case 41:
				m_fOffset = m_nCharWidth-11;
				break;
			case 42:
				m_fOffset = m_nCharWidth-15;
				break;
			case 43:
				m_fOffset = m_nCharWidth-15;
				break;
			case 44:
				m_fOffset = m_nCharWidth-8;
				break;
			case 45:
				m_fOffset = m_nCharWidth-14;
				break;
			case 46:
				m_fOffset = m_nCharWidth-8;
				break;
			case 47:
				m_fOffset = m_nCharWidth-9;
				break;
			case 48:
				m_fOffset = m_nCharWidth-18;
				break;
			case 49:
				m_fOffset = m_nCharWidth-12;
				break;
			case 50:
				m_fOffset = m_nCharWidth-18;
				break;
			case 51:
				m_fOffset = m_nCharWidth-18;
				break;
			case 52:
				m_fOffset = m_nCharWidth-20;
				break;
			case 53:
				m_fOffset = m_nCharWidth-18;
				break;
			case 54:
				m_fOffset = m_nCharWidth-18;
				break;
			case 55:
				m_fOffset = m_nCharWidth-18;
				break;
			case 56:
				m_fOffset = m_nCharWidth-18;
				break;
			case 57:
				m_fOffset = m_nCharWidth-18;
				break;
			case 58:
				m_fOffset = m_nCharWidth-8;
				break;
			case 59:
				m_fOffset = m_nCharWidth-8;
				break;
			case 60:
				m_fOffset = m_nCharWidth-15;
				break;
			case 61:
				m_fOffset = m_nCharWidth-15;
				break;
			case 62:
				m_fOffset = m_nCharWidth-15;
				break;
			case 63:
				m_fOffset = m_nCharWidth-11;
				break;
			case 64:
				m_fOffset = m_nCharWidth-30;
				break;
			case 65:
				m_fOffset = m_nCharWidth-23;
				break;
			case 66:
				m_fOffset = m_nCharWidth-19;
				break;
			case 67:
				m_fOffset = m_nCharWidth-18;
				break;
			case 68:
				m_fOffset = m_nCharWidth-19;
				break;
			case 69:
				m_fOffset = m_nCharWidth-19;
				break;
			case 70:
				m_fOffset = m_nCharWidth-19;
				break;
			case 71:
				m_fOffset = m_nCharWidth-18;
				break;
			case 72:
				m_fOffset = m_nCharWidth-22;
				break;
			case 73:
				m_fOffset = m_nCharWidth-12;
				break;
			case 74:
				m_fOffset = m_nCharWidth-19;
				break;
			case 75:
				m_fOffset = m_nCharWidth-23;
				break;
			case 76:
				m_fOffset = m_nCharWidth-19;
				break;
			case 77:
				m_fOffset = m_nCharWidth-25;
				break;		
			case 78:		
				m_fOffset = m_nCharWidth-23;
				break;		
			case 79:		
				m_fOffset = m_nCharWidth-18;
				break;		
			case 80:		
				m_fOffset = m_nCharWidth-19;
				break;		
			case 81:		
				m_fOffset = m_nCharWidth-18;
				break;		
			case 82:		
				m_fOffset = m_nCharWidth-20;
				break;		
			case 83:		
				m_fOffset = m_nCharWidth-18;
				break;		
			case 84:		
				m_fOffset = m_nCharWidth-21;
				break;		
			case 85:		
				m_fOffset = m_nCharWidth-20;
				break;		
			case 86:		
				m_fOffset = m_nCharWidth-23;
				break;		
			case 87:		
				m_fOffset = m_nCharWidth-31;
				break;		
			case 88:		
				m_fOffset = m_nCharWidth-23;
				break;		
			case 89:		
				m_fOffset = m_nCharWidth-23;
				break;		
			case 90:		
				m_fOffset = m_nCharWidth-19;
				break;		
			case 91:		
				m_fOffset = m_nCharWidth-11;
				break;		
			case 92:		
				m_fOffset = m_nCharWidth-9;
				break;		
			case 93:		
				m_fOffset = m_nCharWidth-11;
				break;		
			case 94:		
				m_fOffset = m_nCharWidth-15;
				break;		
			case 95:		
				m_fOffset = m_nCharWidth-15;
				break;		
			case 96:		
				m_fOffset = m_nCharWidth-15;
				break;		
			case 97:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 98:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 99:		
				m_fOffset = m_nCharWidth-18;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 100:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 101:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 102:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 103:		
				m_fOffset = m_nCharWidth-18;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 104:		
				m_fOffset = m_nCharWidth-22;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 105:		
				m_fOffset = m_nCharWidth-12;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 106:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 107:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 108:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 109:		
				m_fOffset = m_nCharWidth-25;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 110:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 111:		
				m_fOffset = m_nCharWidth-18;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 112:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 113:		
				m_fOffset = m_nCharWidth-18;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 114:		
				m_fOffset = m_nCharWidth-20;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 115:		
				m_fOffset = m_nCharWidth-18;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 116:		
				m_fOffset = m_nCharWidth-21;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 117:		
				m_fOffset = m_nCharWidth-20;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 118:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;
			case 119:		
				m_fOffset = m_nCharWidth-31;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 120:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;		
			case 121:		
				m_fOffset = m_nCharWidth-23;
				m_fScale-=fScale;
				m_nX+=nY;
				break;
			case 122:		
				m_fOffset = m_nCharWidth-19;
				m_fScale-=fScale;
				m_nX+=nY;
				break;
			}
			break;
		case 1:
			{
				int nY = 6;//6
				m_nX = 0;
				m_nX+=nY;
				switch(ch)
				{
				case 32:
					m_fOffset = m_nCharWidth-12;
					break;
				case 33:
					m_fOffset = m_nCharWidth-7;
					break;
				case 34:
					m_fOffset = m_nCharWidth-14;
					break;
				case 35:
					m_fOffset = m_nCharWidth-12;
					break;
				case 36:
					m_fOffset = m_nCharWidth-25;
					break;
				case 37:
					m_fOffset = m_nCharWidth-12;
					break;
				case 38:
					m_fOffset = m_nCharWidth-12;
					break;
				case 39:
					m_fOffset = m_nCharWidth-8;
					break;
				case 40:
					m_fOffset = m_nCharWidth-9;
					break;
				case 41:
					m_fOffset = m_nCharWidth-9;
					break;
				case 42:
					m_fOffset = m_nCharWidth-12;
					break;
				case 43:
					m_fOffset = m_nCharWidth-12;
					break;
				case 44:
					m_fOffset = m_nCharWidth-6;
					break;
				case 45:
					m_fOffset = m_nCharWidth-12;
					break;
				case 46:
					m_fOffset = m_nCharWidth-11;
					break;
				case 47:
					m_fOffset = m_nCharWidth-9;
					break;
				case 48:
					m_fOffset = m_nCharWidth-23;
					break;
				case 49:
					m_fOffset = m_nCharWidth-8;
					break;
				case 50:
					m_fOffset = m_nCharWidth-23;
					break;
				case 51:
					m_fOffset = m_nCharWidth-23;
					break;
				case 52:
					m_fOffset = m_nCharWidth-23;
					break;
				case 53:
					m_fOffset = m_nCharWidth-23;
					break;
				case 54:
					m_fOffset = m_nCharWidth-23;
					break;
				case 55:
					m_fOffset = m_nCharWidth-22;
					break;
				case 56:
					m_fOffset = m_nCharWidth-23;
					break;
				case 57:
					m_fOffset = m_nCharWidth-23;
					break;
				case 58:
					m_fOffset = m_nCharWidth-10;
					break;
				case 59:
					m_fOffset = m_nCharWidth-6;
					break;
				case 60:
					m_fOffset = m_nCharWidth-12;
					break;
				case 61:
					m_fOffset = m_nCharWidth-12;
					break;
				case 62:
					m_fOffset = m_nCharWidth-12;
					break;
				case 63:
					m_fOffset = m_nCharWidth-11;
					break;
				case 64:
					m_fOffset = m_nCharWidth-12;
					break;
				case 65:
					m_fOffset = m_nCharWidth-26;
					break;
				case 66:
					m_fOffset = m_nCharWidth-27;
					break;
				case 67:
					m_fOffset = m_nCharWidth-15;
					break;
				case 68:
					m_fOffset = m_nCharWidth-19;
					break;
				case 69:
					m_fOffset = m_nCharWidth-25;
					break;
				case 70:
					m_fOffset = m_nCharWidth-26;
					break;
				case 71:
					m_fOffset = m_nCharWidth-24;
					break;
				case 72:
					m_fOffset = m_nCharWidth-26;
					break;
				case 73:
					m_fOffset = m_nCharWidth-11;
					break;
				case 74:
					m_fOffset = m_nCharWidth-23;
					break;
				case 75:
					m_fOffset = m_nCharWidth-26;
					break;
				case 76:
					m_fOffset = m_nCharWidth-18;
					break;
				case 77:
					m_fOffset = m_nCharWidth-15;
					break;		
				case 78:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 79:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 80:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 81:		
					m_fOffset = m_nCharWidth-21;
					break;		
				case 82:		
					m_fOffset = m_nCharWidth-19;
					break;		
				case 83:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 84:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 85:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 86:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 87:		
					m_fOffset = m_nCharWidth-27;
					break;		
				case 88:		
					m_fOffset = m_nCharWidth-21;
					break;		
				case 89:		
					m_fOffset = m_nCharWidth-21;
					break;		
				case 90:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 91:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 92:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 93:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 94:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 95:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 96:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 97:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 98:		
					m_fOffset = m_nCharWidth-27;
					break;		
				case 99:		
					m_fOffset = m_nCharWidth-15;
					break;		
				case 100:		
					m_fOffset = m_nCharWidth-19;
					break;		
				case 101:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 102:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 103:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 104:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 105:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 106:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 107:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 108:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 109:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 110:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 111:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 112:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 113:		
					m_fOffset = m_nCharWidth-21;
					break;		
				case 114:		
					m_fOffset = m_nCharWidth-19;
					break;		
				case 115:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 116:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 117:		
					m_fOffset = m_nCharWidth-25;
					break;		
				case 118:		
					m_fOffset = m_nCharWidth-17;
					break;
				case 119:		
					m_fOffset = m_nCharWidth-27;
					break;		
				case 120:		
					m_fOffset = m_nCharWidth-20;
					break;		
				case 121:		
					m_fOffset = m_nCharWidth-21;
					break;
				case 122:		
					m_fOffset = m_nCharWidth-23;
					break;
				}
			}
			break;
		case 2:
			{
				int nY = 6;//6
				m_nX = 0;
				m_nX-=nY;
				switch(ch)
				{
				case 32:
					m_fOffset = m_nCharWidth-7;
					break;
				case 33:
					m_fOffset = m_nCharWidth-5;
					break;
				case 34:
					m_fOffset = m_nCharWidth-11;
					break;
				case 35:
					m_fOffset = m_nCharWidth-6;
					break;
				case 36:
					m_fOffset = m_nCharWidth-11;
					break;
				case 37:
					m_fOffset = m_nCharWidth-10;
					break;
				case 38:
					m_fOffset = m_nCharWidth-15;
					break;
				case 39:
					m_fOffset = m_nCharWidth-11;
					break;
				case 40:
					m_fOffset = m_nCharWidth-6;
					break;
				case 41:
					m_fOffset = m_nCharWidth-6;
					break;
				case 42:
					m_fOffset = m_nCharWidth-9;
					break;
				case 43:
					m_fOffset = m_nCharWidth-11;
					break;
				case 44:
					m_fOffset = m_nCharWidth-5;
					break;
				case 45:
					m_fOffset = m_nCharWidth-3;
					break;
				case 46:
					m_fOffset = m_nCharWidth-5;
					break;
				case 47:
					m_fOffset = m_nCharWidth-7;
					break;
				case 48:
					m_fOffset = m_nCharWidth-11;
					break;
				case 49:
					m_fOffset = m_nCharWidth-11;
					break;
				case 50:
					m_fOffset = m_nCharWidth-11;
					break;
				case 51:
					m_fOffset = m_nCharWidth-11;
					break;
				case 52:
					m_fOffset = m_nCharWidth-11;
					break;
				case 53:
					m_fOffset = m_nCharWidth-11;
					break;
				case 54:
					m_fOffset = m_nCharWidth-11;
					break;
				case 55:
					m_fOffset = m_nCharWidth-11;
					break;
				case 56:
					m_fOffset = m_nCharWidth-11;
					break;
				case 57:
					m_fOffset = m_nCharWidth-11;
					break;
				case 58:
					m_fOffset = m_nCharWidth-5;
					break;
				case 59:
					m_fOffset = m_nCharWidth-5;
					break;
				case 60:
					m_fOffset = m_nCharWidth-13;
					break;
				case 61:
					m_fOffset = m_nCharWidth-11;
					break;
				case 62:
					m_fOffset = m_nCharWidth-11;
					break;
				case 63:
					m_fOffset = m_nCharWidth-9;
					break;
				case 64:
					m_fOffset = m_nCharWidth-16;
					break;
				case 65:
					m_fOffset = m_nCharWidth-13;
					break;
				case 66:
					m_fOffset = m_nCharWidth-19;
					break;
				case 67:
					m_fOffset = m_nCharWidth-15;
					break;
				case 68:
					m_fOffset = m_nCharWidth-21;
					break;
				case 69:
					m_fOffset = m_nCharWidth-17;
					break;
				case 70:
					m_fOffset = m_nCharWidth-17;
					break;
				case 71:
					m_fOffset = m_nCharWidth-17;
					break;
				case 72:
					m_fOffset = m_nCharWidth-15;
					break;
				case 73:
					m_fOffset = m_nCharWidth-17;
					break;
				case 74:
					m_fOffset = m_nCharWidth-17;
					break;
				case 75:
					m_fOffset = m_nCharWidth-13;
					break;
				case 76:
					m_fOffset = m_nCharWidth-13;
					break;
				case 77:
					m_fOffset = m_nCharWidth-23;
					break;		
				case 78:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 79:		
					m_fOffset = m_nCharWidth-16;
					break;		
				case 80:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 81:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 82:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 83:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 84:		
					m_fOffset = m_nCharWidth-15;
					break;		
				case 85:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 86:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 87:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 88:		
					m_fOffset = m_nCharWidth-13;
					break;		
				case 89:		
					m_fOffset = m_nCharWidth-16;
					break;		
				case 90:		
					m_fOffset = m_nCharWidth-13;
					break;		
				case 91:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 92:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 93:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 94:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 95:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 96:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 97:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 98:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 99:		
					m_fOffset = m_nCharWidth-7;
					break;		
				case 100:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 101:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 102:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 103:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 104:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 105:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 106:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 107:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 108:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 109:		
					m_fOffset = m_nCharWidth-14;
					break;		
				case 110:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 111:		
					m_fOffset = m_nCharWidth-7;
					break;		
				case 112:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 113:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 114:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 115:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 116:		
					m_fOffset = m_nCharWidth-6;
					break;		
				case 117:		
					m_fOffset = m_nCharWidth-10;
					break;		
				case 118:		
					m_fOffset = m_nCharWidth-9;
					break;
				case 119:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 120:		
					m_fOffset = m_nCharWidth-8;
					break;		
				case 121:		
					m_fOffset = m_nCharWidth-9;
					break;
				case 122:		
					m_fOffset = m_nCharWidth-6;
					break;
			}
			}
			break;

		case 0:
			{
				int nY = 3;//6
				m_nX = 0;
				m_nX+=nY;
				switch(ch)
				{
				case 32:
					m_fOffset = m_nCharWidth-12;
					break;
				case 33:
					m_fOffset = m_nCharWidth-24;
					break;
				case 34:
					m_fOffset = m_nCharWidth-9;
					break;
				case 35:
					m_fOffset = m_nCharWidth-24;
					break;
				case 36:
					m_fOffset = m_nCharWidth-24;
					break;
				case 37:
					m_fOffset = m_nCharWidth-24;
					break;
				case 38:
					m_fOffset = m_nCharWidth-24;
					break;
				case 39:
					m_fOffset = m_nCharWidth-5;
					break;
				case 40:
					m_fOffset = m_nCharWidth-24;
					break;
				case 41:
					m_fOffset = m_nCharWidth-24;
					break;
				case 42:
					m_fOffset = m_nCharWidth-26;
					break;
				case 43:
					m_fOffset = m_nCharWidth-24;
					break;
				case 44:
					m_fOffset = m_nCharWidth-5;
					break;
				case 45:
					m_fOffset = m_nCharWidth-13;
					break;
				case 46:
					m_fOffset = m_nCharWidth-5;
					break;
				case 47:
					m_fOffset = m_nCharWidth-24;
					break;
				case 48:
					m_fOffset = m_nCharWidth-12;
					break;
				case 49:
					m_fOffset = m_nCharWidth-10;
					break;
				case 50:
					m_fOffset = m_nCharWidth-18;
					break;
				case 51:
					m_fOffset = m_nCharWidth-9;
					break;
				case 52:
					m_fOffset = m_nCharWidth-19;
					break;
				case 53:
					m_fOffset = m_nCharWidth-16;
					break;
				case 54:
					m_fOffset = m_nCharWidth-12;
					break;
				case 55:
					m_fOffset = m_nCharWidth-11;
					break;
				case 56:
					m_fOffset = m_nCharWidth-10;
					break;
				case 57:
					m_fOffset = m_nCharWidth-12;
					break;
				case 58:
					m_fOffset = m_nCharWidth-5;
					break;
				case 59:
					m_fOffset = m_nCharWidth-5;
					break;
				case 60:
					m_fOffset = m_nCharWidth-24;
					break;
				case 61:
					m_fOffset = m_nCharWidth-24;
					break;
				case 62:
					m_fOffset = m_nCharWidth-24;
					break;
				case 63:
					m_fOffset = m_nCharWidth-23;
					break;
				case 64:
					m_fOffset = m_nCharWidth-24;
					break;
				case 65:
					m_fOffset = m_nCharWidth-26;
					break;
				case 66:
					m_fOffset = m_nCharWidth-24;
					break;
				case 67:
					m_fOffset = m_nCharWidth-23;
					break;
				case 68:
					m_fOffset = m_nCharWidth-25;
					break;
				case 69:
					m_fOffset = m_nCharWidth-21;
					break;
				case 70:
					m_fOffset = m_nCharWidth-22;
					break;
				case 71:
					m_fOffset = m_nCharWidth-24;
					break;
				case 72:
					m_fOffset = m_nCharWidth-24;
					break;
				case 73:
					m_fOffset = m_nCharWidth-18;
					break;
				case 74:
					m_fOffset = m_nCharWidth-21;
					break;
				case 75:
					m_fOffset = m_nCharWidth-22;
					break;
				case 76:
					m_fOffset = m_nCharWidth-27;
					break;
				case 77:
					m_fOffset = m_nCharWidth-31;
					break;		
				case 78:		
					m_fOffset = m_nCharWidth-27;
					break;		
				case 79:		
					m_fOffset = m_nCharWidth-20;
					break;		
				case 80:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 81:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 82:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 83:		
					m_fOffset = m_nCharWidth-19;
					break;		
				case 84:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 85:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 86:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 87:		
					m_fOffset = m_nCharWidth-30;
					break;		
				case 88:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 89:		
					m_fOffset = m_nCharWidth-23;
					break;		
				case 90:		
					m_fOffset = m_nCharWidth-26;
					break;		
				case 91:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 92:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 93:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 94:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 95:		
					m_fOffset = m_nCharWidth-24;
					break;		
				case 96:		
					m_fOffset = m_nCharWidth-5;
					break;		
				case 97:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 98:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 99:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 100:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 101:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 102:		
					m_fOffset = m_nCharWidth-10;
					break;		
				case 103:		
					m_fOffset = m_nCharWidth-14;
					break;		
				case 104:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 105:		
					m_fOffset = m_nCharWidth-7;
					break;		
				case 106:		
					m_fOffset = m_nCharWidth-7;
					break;		
				case 107:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 108:		
					m_fOffset = m_nCharWidth-9;
					break;		
				case 109:		
					m_fOffset = m_nCharWidth-18;
					break;		
				case 110:		
					m_fOffset = m_nCharWidth-13;
					break;		
				case 111:		
					m_fOffset = m_nCharWidth-10;
					break;		
				case 112:		
					m_fOffset = m_nCharWidth-14;
					break;		
				case 113:		
					m_fOffset = m_nCharWidth-12;
					break;		
				case 114:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 115:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 116:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 117:		
					m_fOffset = m_nCharWidth-10;
					break;		
				case 118:		
					m_fOffset = m_nCharWidth-11;
					break;
				case 119:		
					m_fOffset = m_nCharWidth-17;
					break;		
				case 120:		
					m_fOffset = m_nCharWidth-11;
					break;		
				case 121:		
					m_fOffset = m_nCharWidth-12;
					break;
				case 122:		
					m_fOffset = m_nCharWidth-8;
					break;
			}
			break;
			}
		}
	}	
}
