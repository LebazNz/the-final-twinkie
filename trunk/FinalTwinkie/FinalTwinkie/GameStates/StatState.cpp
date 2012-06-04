#include "StatState.h"
#include "OptionsState.h"
#include "../Headers/Game.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "../GameObjects/Player.h"

StatState* StatState::m_pSelf = nullptr;
StatState::StatState(void)
{
	m_pDI = nullptr;
	m_pD3D = nullptr;
	m_pTM = nullptr;
	m_pFont = nullptr;
	m_bStats = true;
}

StatState::~StatState(void)
{
}

StatState* StatState::GetInstance( void )
{
	if(m_pSelf == nullptr)
		m_pSelf = new StatState;
	return m_pSelf;
}

void StatState::DeleteInstance( void )
{
	if(m_pSelf != nullptr)
	{
		delete m_pSelf;
		m_pSelf = nullptr;
	}
}

void StatState::Enter( void )
{
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFont = CBitmapFont::GetInstance();
	m_pPlayer = CPlayer::GetInstance();
	m_nBGImageID = m_pTM->LoadTexture(_T("resource/graphics/bg_loadMenu_&_sprites.png"),D3DCOLOR_XRGB(255,255,255));
	m_nButtonImageID = m_pTM->LoadTexture(_T("resource/graphics/Button.png"));
	m_nCursor = m_pTM->LoadTexture(_T("resource/graphics/cursor.png"),0);
}

void StatState::Exit( void )
{
	m_pDI	= nullptr;
	m_pD3D	= nullptr;
	m_pTM	= nullptr;
	m_pFont = nullptr;

//	m_pTM->UnloadTexture(m_nBGImageID);
}

bool StatState::Input( void )
{
	if(m_pDI->KeyPressed(DIK_ESCAPE))
	{
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		return true;
	}

	if(m_pDI->MouseButtonPressed(0))
	{
		Clicked();
	}

	return true;
}

void StatState::Update( float fDt )
{
	SelectButtons();
}

void StatState::Render( void )
{
	m_pFont->Init(COptionsState::GetInstance()->GetLang());
	RECT rSelf = { };
	SetRect(&rSelf, 0, 0, 800, 600);
	m_pTM->Draw(m_nBGImageID,0,0,1.0f,1.0f,&rSelf,0,0,0);

	if(m_bStats)
		RenderStats();
	else
		RenderAchievements();

	m_pTM->Draw(m_nButtonImageID,0,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwBack);
	m_pFont->Print("Stats",40,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pTM->Draw(m_nButtonImageID,CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+85,CGame::GetInstance()->GetHeight()-40,0.75f,0.75f,nullptr,0,0,0,m_dwNext);
	m_pTM->Draw(m_nCursor, m_pDI->MouseGetPosX()-16, m_pDI->MouseGetPosY()-16, 1.0f, 1.0f);
	m_pFont->Print("Achievements",CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+110,CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Press esc to exit",(int)(CGame::GetInstance()->GetWidth()/2-100),CGame::GetInstance()->GetHeight()-30,0.75f,D3DCOLOR_ARGB(255,255,255,255));

	char buffer[10];
	_itoa_s(m_pDI->MouseGetPosX(),buffer,10);
	m_pFont->Print(buffer,600,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosX()-16,buffer,10);
	m_pFont->Print(buffer,600,50,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY(),buffer,10);
	m_pFont->Print(buffer,700,25,0.75f,D3DCOLOR_XRGB(255,255,255));
	_itoa_s(m_pDI->MouseGetPosY()-16,buffer,10);
	m_pFont->Print(buffer,700,50,0.75f,D3DCOLOR_XRGB(255,255,255));

	m_dwNaziBoss = D3DCOLOR_XRGB(140,140,140);	
	m_dwAlienBoss = D3DCOLOR_XRGB(140,140,140);	
	m_dwRobotBoss = D3DCOLOR_XRGB(140,140,140);
	m_dwSparta = D3DCOLOR_XRGB(140,140,140);
	m_dwSapperAbsorb = D3DCOLOR_XRGB(140,140,140);
	m_dwNukem = D3DCOLOR_XRGB(140,140,140);
	m_dwIamBoss = D3DCOLOR_XRGB(140,140,140);
	m_dwAllUpgrades = D3DCOLOR_XRGB(140,140,140);


	if(CPlayer::GetInstance()->GetNaziBoss())
		m_dwNaziBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetAlienBoss())
		m_dwAlienBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetRobotBoss())
		m_dwRobotBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetSparta())
		m_dwSparta = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetSapperAbsorb())
		m_dwSapperAbsorb = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetNukem())
		m_dwNukem = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetIamBoss())
		m_dwIamBoss = D3DCOLOR_XRGB(255,255,255);
	if(CPlayer::GetInstance()->GetAllUpgrades())	
		m_dwAllUpgrades = D3DCOLOR_XRGB(255,255,255);


}

void StatState::Highlight( DWORD* dwIndex )
{
	m_dwBack		 = D3DCOLOR_ARGB(255,255,255,255);
	m_dwNext		 = D3DCOLOR_ARGB(255,255,255,255);
	
	if( dwIndex != nullptr)
		*dwIndex = D3DCOLOR_XRGB(177,132,0);
}

void StatState::SelectButtons()
{
	int m_nMouseX = m_pDI->MouseGetPosX();
	int m_nMouseY = m_pDI->MouseGetPosY();
	int nButtonWidth = 175;
	int nButtonHeight = 45;
	if(m_nMouseX >= 0 && m_nMouseX <= 0 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Buy
		Highlight(&m_dwBack);
	}
	else if(m_nMouseX >= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 && m_nMouseX <= CGame::GetInstance()->GetWidth()-m_pTM->GetTextureWidth(m_nButtonImageID)+80 + nButtonWidth
		&& m_nMouseY >= CGame::GetInstance()->GetHeight()-40 && m_nMouseY <= CGame::GetInstance()->GetHeight()-40 + nButtonHeight)
	{
		// Continue
		Highlight(&m_dwNext);
	}
	else
		Highlight(nullptr);
}

void StatState::Clicked()
{
	if(m_dwNext			 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_bStats = false;
	}
	else if(m_dwBack		 ==D3DCOLOR_XRGB(177,132,0))
	{
		m_bStats = true;
	}
}

void StatState::RenderStats()
{

	m_pFont->Print("Statistics",(int)(CGame::GetInstance()->GetWidth()/2-(m_pFont->GetCharWidthW()*10/2)),25,(float)2.0f,D3DCOLOR_ARGB(255,255,255,255));

	RECT rSelf = { };
	SetRect(&rSelf, 653, 638, 816, 759);
	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(255,255,255,255));
	

	
	
	m_pFont->Print("Score"				,65,115,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Shots Fired"		,65,165,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Nukes Blasted"		,65,215,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Damage Tanked"		,65,265,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Monies Collected"	,65,315,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Enemies Decimated"	,65,365,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	m_pFont->Print("Sappers Absorbed"	,65,415,1.2f,D3DCOLOR_ARGB(255,255,255,255));


	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetScore(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,115,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetShotsFired(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,165,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetNukesBlasted(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,215,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetDamageTaken(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,265,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetTotalMoneyEarned(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,315,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetUnitsKilled(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,365,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}
	{
		char buffer[10];
		_itoa_s(m_pPlayer->GetSappersExploded(),buffer,10);
		m_pFont->Print(buffer	,CGame::GetInstance()->GetWidth()-150,415,1.2f,D3DCOLOR_ARGB(255,255,255,255));
	}

	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(100,255,255,255));

	

}

void StatState::RenderAchievements()
{
	m_pFont->Print("Achievements",(int)(CGame::GetInstance()->GetWidth()/2-(m_pFont->GetCharWidthW()*10/2)),25,(float)2.0f,D3DCOLOR_ARGB(255,255,255,255));

	RECT rSelf = { };
	SetRect(&rSelf, 653, 638, 816, 759);
	m_pTM->Draw(m_nBGImageID,45,95,4.25f,3.5f,&rSelf,0,0,0,D3DCOLOR_ARGB(255,255,255,255));

	
	m_pFont->Print("ALL YOUR REICH ARE BELONG TO ME",65,115,1,m_dwNaziBoss);	
	m_pFont->Print("OH NO ALIENZ"					,65,165,1,m_dwAlienBoss);	
	m_pFont->Print("GREASED"						,65,215,1,m_dwRobotBoss);	
	m_pFont->Print("WE ARE NOT IN SPARTA ANYMORE"	,65,265,1,m_dwSparta);	
	m_pFont->Print("WTF IS DAMAGE"					,65,315,1,m_dwSapperAbsorb);
	m_pFont->Print("NUKE DUKEM"						,65,365,1,m_dwNukem);	
	m_pFont->Print("MAX PAIN"						,65,415,1,m_dwIamBoss);	
	m_pFont->Print("I OWN IT ALL"					,65,465,1,m_dwAllUpgrades);
	
}
