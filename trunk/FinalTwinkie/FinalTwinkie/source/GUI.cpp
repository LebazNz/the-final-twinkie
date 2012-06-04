#include "../Headers/GUI.h"
#include "../GameObjects/Player.h"
#include "../Headers/Game.h"
#include "../Headers/BitmapFont.h"
#include "../GameObjects/Enemy.h"
#include "../PickUps and Specials/Special.h"

CGUI* CGUI::m_pSelf = nullptr;

CGUI* CGUI::GetInstance(void)
{
	if(m_pSelf == nullptr)
		m_pSelf = new CGUI();
	return m_pSelf;
}

void CGUI::DeleteInstance(void)
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void CGUI::Render(void)
{
	RECT rect; rect.top=(LONG)0; rect.left=(LONG)0; rect.right=(LONG)800; rect.bottom=(LONG)227;
	m_pTM->Draw(m_nHudID, 0, CGame::GetInstance()->GetHeight()-227, 1,1,&rect);

	//Heat
	rect.top=(LONG)290; rect.left=(LONG)10; rect.right=(LONG)137; rect.bottom=(LONG)312;
	m_pTM->Draw(m_nHudID, 15, 544, 1,1,&rect);
	rect.top=(LONG)293; rect.left=(LONG)152; rect.right=(LONG)(152+((274-152)*m_pPlayer->GetHeat()/100)); rect.bottom=(LONG)309;
	m_pTM->Draw(m_nHudID, 17, 547, 1,1,&rect);
	rect.top=(LONG)295; rect.left=(LONG)288; rect.right=(LONG)(288+((410-288)*(m_pPlayer->GetHeat()/100))); rect.bottom=(LONG)306;
	m_pTM->Draw(m_nHudID, 17, 549, 1,1,&rect);
	
	//Armor
	rect.top=(LONG)443; rect.left=(LONG)12; rect.right=(LONG)176; rect.bottom=(LONG)463;
	m_pTM->Draw(m_nHudID, 317, 545, 1,1,&rect);
	rect.top=(LONG)447; rect.left=(LONG)197; rect.right=(LONG)(197+((355-197)*(m_pPlayer->GetArmor()/m_pPlayer->GetMaxArmor()))); rect.bottom=(LONG)461;
	m_pTM->Draw(m_nHudID, 320, 548, 1,1,&rect);
	rect.top=(LONG)478; rect.left=(LONG)352; rect.right=(LONG)(352+((510-352)*(m_pPlayer->GetArmor()/m_pPlayer->GetMaxArmor()))); rect.bottom=(LONG)489;
	m_pTM->Draw(m_nHudID, 320, 550, 1,1,&rect);
	
	//Health
	rect.top=(LONG)360; rect.left=(LONG)11; rect.right=(LONG)177; rect.bottom=(LONG)381;
	m_pTM->Draw(m_nHudID, 317, 569, 1,1,&rect);
	rect.top=(LONG)364; rect.left=(LONG)194; rect.right=(LONG)(194+((353-194)*(m_pPlayer->GetHealth()/m_pPlayer->GetMaxHealth()))); rect.bottom=(LONG)378;
	m_pTM->Draw(m_nHudID, 320, 572, 1,1,&rect);
	rect.top=(LONG)391; rect.left=(LONG)351; rect.right=(LONG)(351+((509-351)*(m_pPlayer->GetHealth()/m_pPlayer->GetMaxHealth()))); rect.bottom=(LONG)403;
	m_pTM->Draw(m_nHudID, 320, 575, 1,1,&rect);

	//Money
	rect.top=(LONG)360; rect.left=(LONG)558; rect.right=(LONG)682; rect.bottom=(LONG)382;
	m_pTM->Draw(m_nHudID, 535, 570, 1,1,&rect);

	//Objectives
	rect.top=(LONG)410; rect.left=(LONG)556; rect.right=(LONG)809; rect.bottom=(LONG)432;
	m_pTM->Draw(m_nHudID, 534, 544, 1,1,&rect);


	//Shell Ammo
	rect.top=(LONG)489; rect.left=(LONG)51; rect.right=(LONG)75; rect.bottom=(LONG)534;
	m_pTM->Draw(m_nHudID, 27, 476, 1,1,&rect);

	char buffer[10];
	_itoa_s(m_pPlayer->GetWeaponAmmoShell(), buffer, 10);
	m_pFont->Print(buffer, 30, 506, .5f, D3DCOLOR_XRGB(255,255,255));
	
	//Rocket Ammo
	if(m_pPlayer->GetRocketAccess())
	{
		rect.top=(LONG)489; rect.left=(LONG)88; rect.right=(LONG)114; rect.bottom=(LONG)534;
		m_pTM->Draw(m_nHudID, 66, 476, 1,1,&rect);

		char buffer[10];
		_itoa_s(m_pPlayer->GetWeaponAmmoMissile(), buffer, 10);
		m_pFont->Print(buffer, 68, 506, .5f, D3DCOLOR_XRGB(255,255,255));
	}
	
	//Artillery Ammo
	if(m_pPlayer->GetArtilleryAccess())
	{
		rect.top=(LONG)489; rect.left=(LONG)12; rect.right=(LONG)37; rect.bottom=(LONG)534;
		m_pTM->Draw(m_nHudID, 105, 476, 1,1,&rect);

		char buffer[10];
		_itoa_s(m_pPlayer->GetWeaponAmmoArtillery(), buffer, 10);
		m_pFont->Print(buffer, 106, 506, .5f, D3DCOLOR_XRGB(255,255,255));
	}

	//Money
	_itoa_s(m_pPlayer->GetMoney(), buffer, 10);
	m_pFont->Print(buffer, 551, 575, .5f, D3DCOLOR_XRGB(255,255,255));

	//Buffs
	if(m_pPlayer->GetDoubleDamage())
	{
		rect.top=(LONG)335; rect.left=(LONG)926; rect.right=(LONG)976; rect.bottom=(LONG)385;
		m_pTM->Draw(m_nHudID, 400, 457, 1,1,&rect);
	}
	if(m_pPlayer->GetNoReload()>0)
	{
		rect.top=(LONG)470; rect.left=(LONG)926; rect.right=(LONG)976; rect.bottom=(LONG)520;
		m_pTM->Draw(m_nHudID, 297, 457, 1,1,&rect);
	}
	if(m_pPlayer->GetInfAmmo())
	{
		rect.top=(LONG)402; rect.left=(LONG)926; rect.right=(LONG)976; rect.bottom=(LONG)452;
		m_pTM->Draw(m_nHudID, 348, 457, 1,1,&rect);
	}
	if(m_pPlayer->GetInvul())
	{
		rect.top=(LONG)273; rect.left=(LONG)926; rect.right=(LONG)976; rect.bottom=(LONG)323;
		m_pTM->Draw(m_nHudID, 453, 457, 1,1,&rect);
	}

	//Special 1
	CSpecial* spec= m_pPlayer->GetSpecial1();
	if(spec)
	{
		switch(spec->GetType())
		{
		case SPECIAL:
			{
				rect.top=(LONG)280; rect.left=(LONG)558; rect.right=(LONG)598; rect.bottom=(LONG)321;
			}
			break;
		case SMOKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)718; rect.right=(LONG)758; rect.bottom=(LONG)321;
			}
			break;
		case EMP:
			{
				rect.top=(LONG)280; rect.left=(LONG)610; rect.right=(LONG)649; rect.bottom=(LONG)321;
			}
			break;
		case NUKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)664; rect.right=(LONG)705; rect.bottom=(LONG)321;
			}
			break;
		case REINFORCE:
			{
				rect.top=(LONG)280; rect.left=(LONG)774; rect.right=(LONG)813; rect.bottom=(LONG)321;
			}
			break;
		case AIRSTRIKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)830; rect.right=(LONG)871; rect.bottom=(LONG)321;
			}
			break;
		}
		m_pTM->Draw(m_nHudID, 172, 548, 1,1,&rect);
		_itoa_s(m_pPlayer->GetSpecial1Ammo(), buffer, 10);
		m_pFont->Print(buffer, 188, 575, .5f, D3DCOLOR_XRGB(255,255,255));
	}

	spec= m_pPlayer->GetSpecial2();
	if(spec)
	{
		switch(spec->GetType())
		{
		case SPECIAL:
			{
				rect.top=(LONG)280; rect.left=(LONG)558; rect.right=(LONG)598; rect.bottom=(LONG)321;
			}
			break;
		case SMOKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)718; rect.right=(LONG)758; rect.bottom=(LONG)321;
			}
			break;
		case EMP:
			{
				rect.top=(LONG)280; rect.left=(LONG)610; rect.right=(LONG)649; rect.bottom=(LONG)321;
			}
			break;
		case NUKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)664; rect.right=(LONG)705; rect.bottom=(LONG)321;
			}
			break;
		case REINFORCE:
			{
				rect.top=(LONG)280; rect.left=(LONG)774; rect.right=(LONG)813; rect.bottom=(LONG)321;
			}
			break;
		case AIRSTRIKE:
			{
				rect.top=(LONG)280; rect.left=(LONG)830; rect.right=(LONG)871; rect.bottom=(LONG)321;
			}
			break;
		}
		m_pTM->Draw(m_nHudID, 228, 548, 1,1,&rect);
		_itoa_s(m_pPlayer->GetSpecial2Ammo(), buffer, 10);
		m_pFont->Print(buffer, 243, 575, .5f, D3DCOLOR_XRGB(255,255,255));
	}
}

void CGUI::Update(float fDt)
{
}

CGUI::CGUI(void)
{
	m_pTM=CSGD_TextureManager::GetInstance();
	m_pFont=CBitmapFont::GetInstance();
}

CGUI::~CGUI(void)
{
}
