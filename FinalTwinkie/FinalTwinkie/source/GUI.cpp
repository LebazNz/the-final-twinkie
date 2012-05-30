#include "../Headers/GUI.h"
#include "../GameObjects/Player.h"
#include "../source/Game.h"
#include "../Headers/BitmapFont.h"

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
	RECT rect; rect.top=0; rect.left=0; rect.right=800; rect.bottom=227;
	m_pTM->Draw(m_nHudID, 0, CGame::GetInstance()->GetHeight()-227, 1,1,&rect);

	//Heat
	rect.top=290; rect.left=10; rect.right=137; rect.bottom=312;
	m_pTM->Draw(m_nHudID, 15, 544, 1,1,&rect);
	rect.top=293; rect.left=152; rect.right=152+((274-152)*m_pPlayer->GetHeat()/100); rect.bottom=309;
	m_pTM->Draw(m_nHudID, 17, 547, 1,1,&rect);
	rect.top=295; rect.left=288; rect.right=288+((410-288)*(m_pPlayer->GetHeat()/100)); rect.bottom=306;
	m_pTM->Draw(m_nHudID, 17, 549, 1,1,&rect);
	
	//Armor
	rect.top=443; rect.left=12; rect.right=176; rect.bottom=463;
	m_pTM->Draw(m_nHudID, 317, 545, 1,1,&rect);
	rect.top=447; rect.left=197; rect.right=197+((355-197)*(m_pPlayer->GetArmor()/m_pPlayer->GetMaxArmor())); rect.bottom=461;
	m_pTM->Draw(m_nHudID, 320, 548, 1,1,&rect);
	rect.top=478; rect.left=352; rect.right=352+((510-352)*(m_pPlayer->GetArmor()/m_pPlayer->GetMaxArmor())); rect.bottom=489;
	m_pTM->Draw(m_nHudID, 320, 550, 1,1,&rect);
	
	//Health
	rect.top=360; rect.left=11; rect.right=177; rect.bottom=381;
	m_pTM->Draw(m_nHudID, 317, 569, 1,1,&rect);
	rect.top=364; rect.left=194; rect.right=194+((353-194)*(m_pPlayer->GetHealth()/m_pPlayer->GetMaxHealth())); rect.bottom=378;
	m_pTM->Draw(m_nHudID, 320, 572, 1,1,&rect);
	rect.top=391; rect.left=351; rect.right=351+((509-351)*(m_pPlayer->GetHealth()/m_pPlayer->GetMaxHealth())); rect.bottom=403;
	m_pTM->Draw(m_nHudID, 320, 575, 1,1,&rect);
	
	

	//Specials
	rect.top=280; rect.left=558; rect.right=598; rect.bottom=321;
	m_pTM->Draw(m_nHudID, 172, 548, 1,1,&rect);

	m_pTM->Draw(m_nHudID, 228, 548, 1,1,&rect);

	//Money
	rect.top=360; rect.left=558; rect.right=682; rect.bottom=382;
	m_pTM->Draw(m_nHudID, 535, 570, 1,1,&rect);

	//Objectives
	rect.top=410; rect.left=556; rect.right=809; rect.bottom=432;
	m_pTM->Draw(m_nHudID, 534, 544, 1,1,&rect);


	//Shell Ammo
	rect.top=489; rect.left=51; rect.right=75; rect.bottom=534;
	m_pTM->Draw(m_nHudID, 27, 476, 1,1,&rect);

	char buffer[10];
	itoa(m_pPlayer->GetWeaponAmmoOne(), buffer, 10);
	m_pFont->Print(buffer, 30, 506, .5f, D3DCOLOR_XRGB(255,255,255));

	itoa(m_pPlayer->GetMoney(), buffer, 10);
	m_pFont->Print(buffer, 551, 575, .5f, D3DCOLOR_XRGB(255,255,255));



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
