#include "ShopState.h"
#include "OptionsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "../GameObjects/Player.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"

CShopState* CShopState::m_pSelf = nullptr;

CShopState* CShopState::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CShopState;
	return m_pSelf;
}

void CShopState::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

CShopState::CShopState(void)
{
	m_pDI = nullptr;
	m_pD3D = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_nItemCost = 0;
	/*m_pPlayer = CPlayer::GetInstance();*/

	m_nRocketPrice = 2000;
	m_nLaserPrice = 8000;
	m_nNukePrice = 10000;
	m_nEMPPrice = 2000;
	m_nArtilleryPrice = 4000;
	m_nFlamerPrice = 9000;
	m_nAirStrikePrice = 6000;
	m_SmokeBombPrice = 1000;

	m_nHeatPrice = 100;
	m_nAmmoPrice = 100;
	m_nDamagePrice = 150;
	m_nHealthPrice = 200;
	m_nArmorPrice = 200;
	m_nSpeedPrice = 200;
	m_fPriceIncrease = 1;

	m_nSelectedCost = 0;


	m_fHeatUp = -0.1f;
	m_fDamUp = 0.1f;
	m_fAmmoUp = 0.2f;
	m_fHealthUp = 0.15f;
	m_fArmorUp = 0.1f;
	m_fSpeedUp = 0.2f;


	m_bRocket		= false;
	m_bLaser		= false;
	m_bNuke			= false;
	m_bEMP			= false;
	m_bArillery		= false;
	m_bFlamer		= false;
	m_bAirStrike	= false;
	m_bSmokeBomb	= false;
	m_bHeat			= false;
	m_bDamage		= false;
	m_bAmmo			= false;
	m_bHealth		= false;
	m_bArmor		= false;
	m_bSpeed		= false;
	m_bPurchase     = false;
	m_nHeat = 1;

}

CShopState::~CShopState(void)
{
}

void CShopState::Enter(void)
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFont = CBitmapFont::GetInstance();
	m_pPlayer = CPlayer::GetInstance();
	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
	LoadText();
}

void CShopState::Exit(void)
{
	m_pDI	= nullptr;
	m_pD3D	= nullptr;
	m_pTM	= nullptr;
	m_pFont = nullptr;

	/*m_pTM->UnloadTexture(m_nBGImageID);
	m_pTM->UnloadTexture(m_nButtonImageID);
	m_pTM->UnloadTexture(m_nCursor);*/
}

bool CShopState::Input(void)
{
	if(m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1))
	{
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		return true;
	}

	if(m_pDI->MouseButtonPressed(0) || m_pDI->JoystickButtonPressed(0))
	{
		Clicked();
	}

	return true;
}

void CShopState::Update(float fDt)
{
	SelectButtons();
	DetermineSelection();
	ColorSelected();
}

void CShopState::Render(void)
{

	m_pFont->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);


	m_pFont->Print(m_sTitle.c_str(),(int)(CGame::GetInstance()->GetWidth()/2-(m_pFont->GetCharWidthW()*14/2)),25,(float)2.0f,D3DCOLOR_ARGB(255,255,255,255));

	// BlueBox
	/*SetRect(&rSelf, 653, 638, 816, 760);
	m_pTM->Draw(m_nBGImageID,15,15,1.0f,1.0f,&rSelf,0,0,0);*/
	int y = 100;
	int y2 = 80;
	m_pTM->Draw(m_nButtonImageID,35,15 + y,0.75f,0.75f,nullptr,0,0,0,m_dwRocket);
	m_pFont->Print(m_sRocket.c_str(),75,25 + y,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,220,15 + y,0.75f,0.75f,nullptr,0,0,0,m_dwLaser);
	m_pFont->Print(m_sLaser.c_str(),265,25 + y,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,405,15 + y,0.75f,0.75f,nullptr,0,0,0,m_dwNuke);
	m_pFont->Print(m_sNuke.c_str(),455,25 + y,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,590,15 + y,0.75f,0.75f,nullptr,0,0,0,m_dwEMP);
	m_pFont->Print(m_sEmp.c_str(),655,25 + y,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,35, 100 + y2,0.75f,0.75f,nullptr,0,0,0,m_dwArillery);
	m_pFont->Print(m_sArtillery.c_str(),55,110 + y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,220,100 + y2,0.75f,0.75f,nullptr,0,0,0,m_dwFlamer);
	m_pFont->Print(m_sFlamer.c_str(),255,110 + y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,405,100 + y2,0.75f,0.75f,nullptr,0,0,0,m_dwAirStrike);
	m_pFont->Print(m_sAirStrike.c_str(),425,110 + y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,590,100 + y2,0.75f,0.75f,nullptr,0,0,0,m_dwSmokeBomb);
	m_pFont->Print(m_sSmokeBomb.c_str(),605,110 + y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	// GreyBox
	SetRect(&rSelf, 467, 638, 631, 760);
	y = y/2;
	m_pTM->Draw(m_nBGImageID,35 ,200 + y,1.2f,0.5f,&rSelf,0,0,0,m_dwHeat);
	m_pFont->Print(m_sHeat.c_str(),75 ,220 +  y,0.9f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nBGImageID,295,200 + y,1.2f,0.5f,&rSelf,0,0,0,m_dwDamage);
	m_pFont->Print(m_sDamage.c_str(),335,220 + y,0.9f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nBGImageID,555,200 + y,1.2f,0.5f,&rSelf,0,0,0,m_dwAmmo);
	m_pFont->Print(m_sAmmo.c_str(),595,220 + y,0.9f,D3DCOLOR_ARGB(255,255,255,255));
	
	y2 = 45;
	m_pTM->Draw(m_nBGImageID,35 ,300 + y2,1.2f,0.5f,&rSelf,0,0,0,m_dwHealth);
	m_pFont->Print(m_sHealth.c_str(),75, 320 + y2,0.9f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nBGImageID,295,300 + y2,1.2f,0.5f,&rSelf,0,0,0,m_dwArmor);
	m_pFont->Print(m_sArmor.c_str(),335,320 + y2,0.9f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nBGImageID,555,300 + y2,1.2f,0.5f,&rSelf,0,0,0,m_dwSpeed);
	m_pFont->Print(m_sSpeed.c_str(),595,320 + y2,0.9f,D3DCOLOR_ARGB(255,255,255,255));

	// Description bar

	m_pTM->Draw(m_nBGImageID,-5 ,400+ y2,5,0.75f,&rSelf,0,0,0);

	m_pFont->Print(m_sMonies.c_str(),CGame::GetInstance()->GetWidth()/6,440+ y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print(m_sCost.c_str(),CGame::GetInstance()->GetWidth()/4*3,440+ y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	RenderPrices(y2);
	m_pTM->Draw(m_nButtonImageID,0,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwBuy);
	m_pFont->Print(m_sBuy.c_str(),40,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwBack);
	m_pFont->Print(m_sContinue.c_str(),CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+90,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	//m_pFont->Print("Rocket",75,25 + y,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);

}

void CShopState::Highlight( DWORD* dwIndex )
{
	m_dwRocket		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwLaser		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwNuke		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwEMP			 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwArillery	 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwFlamer		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwAirStrike	 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwSmokeBomb	 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwBuy			 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwBack		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwHeat		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwDamage		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwAmmo		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwHealth		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwArmor		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwSpeed		 = D3DCOLOR_ARGB(255,255,255,255);
	if( dwIndex != nullptr)
		*dwIndex = D3DCOLOR_XRGB(177,132,0);
}

void CShopState::RenderPrices(int y2)
{
	char buffer[10];
	_itoa_s(m_pPlayer->GetMoney(),buffer,10);
	m_pFont->Print(buffer,(int)(CGame::GetInstance()->GetWidth()/6+m_pFont->GetCharWidthW()*3),440+ y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	char buffer2[10];
	_itoa_s(m_nItemCost,buffer2,10);
	m_pFont->Print(buffer2,(int)(CGame::GetInstance()->GetWidth()/4*3+m_pFont->GetCharWidthW()*2*.75),440+ y2,0.75f,D3DCOLOR_ARGB(255,255,255,255));
}

void CShopState::DetermineSelection()
{
	if(m_dwRocket			 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nRocketPrice;
	else if(m_dwLaser		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nLaserPrice;
	else if(m_dwNuke		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nNukePrice;
	else if(m_dwEMP			 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nEMPPrice;
	else if(m_dwArillery	 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nArtilleryPrice;
	else if(m_dwFlamer		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nFlamerPrice;
	else if(m_dwAirStrike	 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nAirStrikePrice;
	else if(m_dwSmokeBomb	 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_SmokeBombPrice;
	else if(m_dwBuy			 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nSelectedCost;
	else if(m_dwBack		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = m_nSelectedCost;
	else if(m_dwHeat		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nHeatPrice*m_fPriceIncrease);
	else if(m_dwDamage		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nDamagePrice*m_fPriceIncrease);
	else if(m_dwAmmo		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nAmmoPrice*m_fPriceIncrease);
	else if(m_dwHealth		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nHealthPrice*m_fPriceIncrease);
	else if(m_dwArmor		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nArmorPrice*m_fPriceIncrease);
	else if(m_dwSpeed		 ==D3DCOLOR_XRGB(177,132,0))
		m_nItemCost = (int)(m_nSpeedPrice*m_fPriceIncrease);
	else
		m_nItemCost = m_nSelectedCost;
}

void CShopState::SelectButtons()
{
	if(m_pDI->JoystickGetLStickXAmount() > 0)
		m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()+5);
	if(m_pDI->JoystickGetLStickXAmount() < 0)
		m_pDI->MouseSetPosX(m_pDI->MouseGetPosX()-5);
	if(m_pDI->JoystickGetLStickYAmount() > 0)
		m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()+5);
	if(m_pDI->JoystickGetLStickYAmount() < 0)
		m_pDI->MouseSetPosY(m_pDI->MouseGetPosY()-5);

	m_nMouseX = m_pDI->MouseGetPosX();
	m_nMouseY = m_pDI->MouseGetPosY();
	int nButtonWidth = 175;
	int nButtonHeight = 45;
	int nBoxWidth = 197;
	int nBoxHeight = 63;
	int y = 100;
	int y2 = 80;
	int BoxY = 50;
	int BoxY2 = 45;

	if(m_nMouseX >= 35 && m_nMouseX <= 35 + nButtonWidth
		&& m_nMouseY >= 15+y && m_nMouseY <= 15 + nButtonHeight+y)
	{
		// Rocket
		Highlight(&m_dwRocket);
	}
	else if(m_nMouseX >= 220 && m_nMouseX <= 220 + nButtonWidth
		&& m_nMouseY >= 15+y && m_nMouseY <= 15 + nButtonHeight+y)
	{
		// Laser
		Highlight(&m_dwLaser);
	}
	else if(m_nMouseX >= 405 && m_nMouseX <= 405 + nButtonWidth
		&& m_nMouseY >= 15+y && m_nMouseY <= 15 + nButtonHeight+y)
	{
		// Nuke
		Highlight(&m_dwNuke);
	}
	else if(m_nMouseX >= 590 && m_nMouseX <= 590 + nButtonWidth
		&& m_nMouseY >= 15+y && m_nMouseY <= 15 + nButtonHeight+y)
	{
		// EMP
		Highlight(&m_dwEMP);
	}
	else if(m_nMouseX >= 35 && m_nMouseX <= 35 + nButtonWidth
		&& m_nMouseY >= 100+y2 && m_nMouseY <= 100 + nButtonHeight+y2)
	{
		// Artillery
		Highlight(&m_dwArillery);
	}
	else if(m_nMouseX >= 220 && m_nMouseX <= 220 + nButtonWidth
		&& m_nMouseY >= 100+y2 && m_nMouseY <= 100 + nButtonHeight+y2)
	{
		// Flamer
		Highlight(&m_dwFlamer);
	}
	else if(m_nMouseX >= 405 && m_nMouseX <= 405 + nButtonWidth
		&& m_nMouseY >= 100+y2 && m_nMouseY <= 100 + nButtonHeight+y2)
	{
		// Air Strike
		Highlight(&m_dwAirStrike);
	}
	else if(m_nMouseX >= 590 && m_nMouseX <= 590 + nButtonWidth
		&& m_nMouseY >= 100+y2 && m_nMouseY <= 100 + nButtonHeight+y2)
	{
		// Smoke Bomb
		Highlight(&m_dwSmokeBomb);
	}
	else if(m_nMouseX >= 0 && m_nMouseX <= 0 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Buy
		Highlight(&m_dwBuy);
	}
	else if(m_nMouseX >= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 && m_nMouseX <= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Continue
		Highlight(&m_dwBack);
	}
	else if(m_nMouseX >= 35 && m_nMouseX <= 35 + nBoxWidth
		&& m_nMouseY >= 200+BoxY && m_nMouseY <= 200+BoxY+nBoxHeight)
	{
		// Heat
		Highlight(&m_dwHeat);
	}
	else if(m_nMouseX >= 295 && m_nMouseX <= 295 + nBoxWidth
		&& m_nMouseY >= 200+BoxY && m_nMouseY <= 200+BoxY+nBoxHeight)
	{
		// Damage
		Highlight(&m_dwDamage);
	}
	else if(m_nMouseX >= 555 && m_nMouseX <= 555 + nBoxWidth
		&& m_nMouseY >= 200+BoxY && m_nMouseY <= 200+BoxY+nBoxHeight)
	{
		// Ammo
		Highlight(&m_dwAmmo);
	}
	else if(m_nMouseX >= 35 && m_nMouseX <= 35 + nBoxWidth
		&& m_nMouseY >= 300+BoxY2 && m_nMouseY <= 300+BoxY2+nBoxHeight)
	{
		// Health
		Highlight(&m_dwHealth);
	}
	else if(m_nMouseX >= 295 && m_nMouseX <= 295 + nBoxWidth
		&& m_nMouseY >= 300+BoxY2 && m_nMouseY <= 300+BoxY2+nBoxHeight)
	{
		// Armor
		Highlight(&m_dwArmor);
	}
	else if(m_nMouseX >= 555 && m_nMouseX <= 555 + nBoxWidth
		&& m_nMouseY >= 300+BoxY2 && m_nMouseY <= 300+BoxY2+nBoxHeight)
	{
		// Speed
		Highlight(&m_dwSpeed);
	}
	else
		Highlight(nullptr);
}

void CShopState::Clicked()
{
	if(m_dwRocket			 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nRocketPrice;
		SelectThis(&m_bRocket);
	}
	else if(m_dwLaser		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nLaserPrice;
		SelectThis(&m_bLaser);

	}
	else if(m_dwNuke		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nNukePrice;
		SelectThis(&m_bNuke);
	}
	else if(m_dwEMP			 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nEMPPrice;
		SelectThis(&m_bEMP);
	}
	else if(m_dwArillery	 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nArtilleryPrice;
		SelectThis(&m_bArillery);
	}
	else if(m_dwFlamer		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nFlamerPrice;
		SelectThis(&m_bFlamer);
	}
	else if(m_dwAirStrike	 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nAirStrikePrice;
		SelectThis(&m_bAirStrike);
	}
	else if(m_dwSmokeBomb	 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_SmokeBombPrice;
		SelectThis(&m_bSmokeBomb);
	}
	else if(m_dwBuy			 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nSelectedCost;
		Purchase();
		
	}
	else if(m_dwBack		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = m_nSelectedCost;

	}
	else if(m_dwHeat		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nHeatPrice*m_fPriceIncrease);
		SelectThis(&m_bHeat);
	}
	else if(m_dwDamage		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nDamagePrice*m_fPriceIncrease);
		SelectThis(&m_bDamage);
	}
	else if(m_dwAmmo		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nAmmoPrice*m_fPriceIncrease);
		SelectThis(&m_bAmmo);
	}
	else if(m_dwHealth		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nHealthPrice*m_fPriceIncrease);
		SelectThis(&m_bHealth);
	}
	else if(m_dwArmor		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nArmorPrice*m_fPriceIncrease);
		SelectThis(&m_bArmor);
	}
	else if(m_dwSpeed		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_nSelectedCost  = (int)(m_nSpeedPrice*m_fPriceIncrease);
		SelectThis(&m_bSpeed);
	}
	else
	{
		m_nSelectedCost = m_nItemCost;
	}

}

void CShopState::ColorSelected()
{
	if(m_bRocket		== true)
	{
		m_dwRocket = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bLaser			== true)
	{
		m_dwLaser = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bNuke			== true)
	{
		m_dwNuke = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bEMP			== true)
	{
		m_dwEMP = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bArillery		== true)
	{
		m_dwArillery = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bFlamer		== true)
	{
		m_dwFlamer = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bAirStrike		== true)
	{
		m_dwAirStrike = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bSmokeBomb		== true)
	{
		m_dwSmokeBomb = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bHeat			== true)
	{
		m_dwHeat = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bDamage		== true)
	{
		m_dwDamage = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bAmmo			== true)
	{
		m_dwAmmo = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bHealth		== true)
	{
		m_dwHealth = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bArmor			== true)
	{
		m_dwArmor = D3DCOLOR_XRGB(255,100,100);
	}
	else if(m_bSpeed			== true)
	{
		m_dwSpeed = D3DCOLOR_XRGB(255,100,100);
	}
}

void CShopState::SelectThis( bool * bRhs )
{
	m_bRocket		= false;
	m_bLaser		= false;
	m_bNuke			= false;
	m_bEMP			= false;
	m_bArillery		= false;
	m_bFlamer		= false;
	m_bAirStrike	= false;
	m_bSmokeBomb	= false;
	m_bHeat			= false;
	m_bDamage		= false;
	m_bAmmo			= false;
	m_bHealth		= false;
	m_bArmor		= false;
	m_bSpeed		= false;

	*bRhs = true;
}

void CShopState::Purchase()
{
	if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
	{
		if(m_bRocket)
		{
			if(!m_pPlayer->GetRocketAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetRocketAccess(true);
					}
			}
		}
		else if(m_bLaser)
		{
			if(!m_pPlayer->GetLaserAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetLaserAccess(true);
					}
			}
		}
		else if(m_bNuke)
		{
			if(!m_pPlayer->GetNukeAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetNukeAccess(true);
					}
			}
		}
		else if(m_bEMP)
		{
			if(!m_pPlayer->GetEMPAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetEMPAccess(true);
					}
			}
		}
		else if(m_bArillery)
		{
			if(!m_pPlayer->GetArtilleryAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetArtilleryAccess(true);
						
					}
			}
		}
		else if(m_bFlamer)
		{
			if(!m_pPlayer->GetFlamerAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetFlamerAccess(true);
					}
			}
		}
		else if(m_bAirStrike)
		{
			if(!m_pPlayer->GetAirStrikeAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetAirStrikeAccess(true);
					}
			}
		}
		else if(m_bSmokeBomb)
		{
			if(!m_pPlayer->GetSmokeBombAccess())
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
					{
						m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
						m_pPlayer->SetSmokeBombAccess(true);
					}
			}
		}
		else if(m_bHeat)
		{
			if(m_pPlayer->GetHeatLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetHeatLevel(m_pPlayer->GetHeatLevel()+1);
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetHeatModifier(m_pPlayer->GetHeatModifier()+m_fHeatUp);
					
				}
			}
		}
		else if(m_bDamage)
		{
			if(m_pPlayer->GetDamageLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetDamageLevel(m_pPlayer->GetDamageLevel()+1);
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetDamageMod(m_pPlayer->GetDamageMod()+m_fDamUp);
					m_nSelectedCost *= (int)m_fPriceIncrease;
				}
			}
		}
		else if(m_bAmmo)
		{
			if(m_pPlayer->GetAmmoLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetAmmoLevel(int(m_pPlayer->GetAmmoLevel()+m_fAmmoUp));
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetAmmoMod(m_pPlayer->GetAmmoMod()+0.2f);
					m_nSelectedCost *= (int)m_fPriceIncrease;
				}
			}
		}
		else if(m_bHealth)
		{
			if(m_pPlayer->GetHealthLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetHealthLevel(m_pPlayer->GetHealthLevel()+1);
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetHealthMod(m_pPlayer->GetHealthMod()+m_fHealthUp);
					m_nSelectedCost *= (int)m_fPriceIncrease;
				}
			}
		}
		else if(m_bArmor)
		{
			if(m_pPlayer->GetArmorLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetArmorLevel(m_pPlayer->GetArmorLevel()+1);
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetArmorMod(m_pPlayer->GetArmorMod()+m_fArmorUp);
					m_nSelectedCost *= (int)m_fPriceIncrease;
				}
			}
		}
		else if(m_bSpeed)
		{
			if(m_pPlayer->GetSpeedLevel() < 5)
			{
				if(m_pPlayer->GetMoney()-m_nSelectedCost >= 0)
				{
					m_pPlayer->SetMoney(m_pPlayer->GetMoney()-m_nSelectedCost);
					m_pPlayer->SetSpeedLevel(m_pPlayer->GetSpeedLevel()+1);
					m_fPriceIncrease+=0.1f;
					m_pPlayer->SetPurchaseLevel(m_fPriceIncrease);
					m_pPlayer->SetSpeedMod(m_pPlayer->GetSpeedMod()+m_fSpeedUp);
					m_nSelectedCost *= (int)m_fPriceIncrease;
				}
			}
		}
	}


	int tempArt = -1;
	int tempRoc = -1;
	if(m_pPlayer->GetArtilleryAccess())
		tempArt = 40;
	if(m_pPlayer->GetRocketAccess())
		tempRoc = 40;

	m_pPlayer->SetMaxWeaponAmmo(40,tempArt,tempRoc);
	
}

void CShopState::LoadText(void)
{
	TiXmlDocument doc("resource/files/Text.xml");
	int LangSel=COptionsState::GetInstance()->GetLang();
	if(doc.LoadFile())
	{
		TiXmlNode* pParent = doc.RootElement();
		switch(LangSel)
		{
		case 0:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("ShopState");
				TiXmlNode* pButton = pState->FirstChild("Title");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sTitle=pText->Value();
				pButton = pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton = pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Emp");
				pText = pButton->FirstChild()->ToText();
				m_sEmp=pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton=pState->FirstChild("Flamer");
				pText = pButton->FirstChild()->ToText();
				m_sFlamer=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("SmokeBomb");
				pText = pButton->FirstChild()->ToText();
				m_sSmokeBomb=pText->Value();
				pButton=pState->FirstChild("Heat");
				pText = pButton->FirstChild()->ToText();
				m_sHeat=pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton=pState->FirstChild("Ammo");
				pText = pButton->FirstChild()->ToText();
				m_sAmmo=pText->Value();
				pButton=pState->FirstChild("Health");
				pText = pButton->FirstChild()->ToText();
				m_sHealth=pText->Value();
				pButton=pState->FirstChild("Armor");
				pText = pButton->FirstChild()->ToText();
				m_sArmor=pText->Value();
				pButton=pState->FirstChild("Speed");
				pText = pButton->FirstChild()->ToText();
				m_sSpeed=pText->Value();
				pButton=pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Cost");
				pText = pButton->FirstChild()->ToText();
				m_sCost=pText->Value();
				pButton=pState->FirstChild("Buy");
				pText = pButton->FirstChild()->ToText();
				m_sBuy=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 1:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("English");
				TiXmlNode* pState = pLanguage->FirstChild("ShopState");
				TiXmlNode* pButton = pState->FirstChild("Title");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sTitle=pText->Value();
				pButton = pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton = pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Emp");
				pText = pButton->FirstChild()->ToText();
				m_sEmp=pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton=pState->FirstChild("Flamer");
				pText = pButton->FirstChild()->ToText();
				m_sFlamer=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("SmokeBomb");
				pText = pButton->FirstChild()->ToText();
				m_sSmokeBomb=pText->Value();
				pButton=pState->FirstChild("Heat");
				pText = pButton->FirstChild()->ToText();
				m_sHeat=pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton=pState->FirstChild("Ammo");
				pText = pButton->FirstChild()->ToText();
				m_sAmmo=pText->Value();
				pButton=pState->FirstChild("Health");
				pText = pButton->FirstChild()->ToText();
				m_sHealth=pText->Value();
				pButton=pState->FirstChild("Armor");
				pText = pButton->FirstChild()->ToText();
				m_sArmor=pText->Value();
				pButton=pState->FirstChild("Speed");
				pText = pButton->FirstChild()->ToText();
				m_sSpeed=pText->Value();
				pButton=pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Cost");
				pText = pButton->FirstChild()->ToText();
				m_sCost=pText->Value();
				pButton=pState->FirstChild("Buy");
				pText = pButton->FirstChild()->ToText();
				m_sBuy=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 2:
			{
				TiXmlNode* pLanguage = pParent->FirstChild("Pirate");
				TiXmlNode* pState = pLanguage->FirstChild("ShopState");
				TiXmlNode* pButton = pState->FirstChild("Title");
				TiXmlText* pText = pButton->FirstChild()->ToText();
				m_sTitle=pText->Value();
				pButton = pState->FirstChild("Rocket");
				pText = pButton->FirstChild()->ToText();
				m_sRocket=pText->Value();
				pButton=pState->FirstChild("Laser");
				pText = pButton->FirstChild()->ToText();
				m_sLaser=pText->Value();
				pButton = pState->FirstChild("Nuke");
				pText = pButton->FirstChild()->ToText();
				m_sNuke=pText->Value();
				pButton=pState->FirstChild("Emp");
				pText = pButton->FirstChild()->ToText();
				m_sEmp=pText->Value();
				pButton=pState->FirstChild("Artillery");
				pText = pButton->FirstChild()->ToText();
				m_sArtillery=pText->Value();
				pButton=pState->FirstChild("Flamer");
				pText = pButton->FirstChild()->ToText();
				m_sFlamer=pText->Value();
				pButton=pState->FirstChild("AirStrike");
				pText = pButton->FirstChild()->ToText();
				m_sAirStrike=pText->Value();
				pButton=pState->FirstChild("SmokeBomb");
				pText = pButton->FirstChild()->ToText();
				m_sSmokeBomb=pText->Value();
				pButton=pState->FirstChild("Heat");
				pText = pButton->FirstChild()->ToText();
				m_sHeat=pText->Value();
				pButton=pState->FirstChild("Damage");
				pText = pButton->FirstChild()->ToText();
				m_sDamage=pText->Value();
				pButton=pState->FirstChild("Ammo");
				pText = pButton->FirstChild()->ToText();
				m_sAmmo=pText->Value();
				pButton=pState->FirstChild("Health");
				pText = pButton->FirstChild()->ToText();
				m_sHealth=pText->Value();
				pButton=pState->FirstChild("Armor");
				pText = pButton->FirstChild()->ToText();
				m_sArmor=pText->Value();
				pButton=pState->FirstChild("Speed");
				pText = pButton->FirstChild()->ToText();
				m_sSpeed=pText->Value();
				pButton=pState->FirstChild("Monies");
				pText = pButton->FirstChild()->ToText();
				m_sMonies=pText->Value();
				pButton=pState->FirstChild("Cost");
				pText = pButton->FirstChild()->ToText();
				m_sCost=pText->Value();
				pButton=pState->FirstChild("Buy");
				pText = pButton->FirstChild()->ToText();
				m_sBuy=pText->Value();
				pButton=pState->FirstChild("Continue");
				pText = pButton->FirstChild()->ToText();
				m_sContinue=pText->Value();
			}
			break;
		case 3:
			{
			}
			break;
		}
	}
}
